/* 
** Basic yawm status with just time HH:MM and battery
** but it knows how to poll a network interface status
**        Usage: yawmstatus [options]
**                -i network interface name
**                -b battery class name
**                -t time interval between updates = 1-60 sec
**                -B battery subsystem prefix (i.e. 'power' or 'energy')
*/
#define _GNU_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <getopt.h>
#include <time.h>
#include <X11/Xlib.h>


static Display *dpy;

void
setstatus(char *str) {
	XStoreName(dpy, DefaultRootWindow(dpy), str);
	XSync(dpy, False);
}

char*
gettime_basic(void){
	char *buf;
	time_t mytime;
	struct tm *t = NULL;
	int tlen = 6;
	
	mytime = time(NULL);
	
	if ((t = (struct tm*)malloc(sizeof(struct tm))) == NULL) {
		fprintf(stderr, "Error getting localtime.\n");
		exit(1);
	}
	
	if ((buf = (char*)calloc(tlen,sizeof(char))) == NULL) {
		fprintf(stderr, "Cannot allocate memory for buf.\n");
		exit(1);
	}
	localtime_r(&mytime,t);
	snprintf(buf,tlen,"%02d:%02d", t->tm_hour, t->tm_min);
	
	free(t);
	
	return buf;
}


int
getbattery(const char *batn, const char *bsubs) {
#ifndef DEF_BNAME
#define DEF_BNAME "BAT0"
#endif

#ifndef DEF_BSUBS
#define DEF_BSUBS "energy"
#endif
	FILE *fd;
	int energy_now, energy_full, voltage_now;
	char *filename;
	const char* bsubsys = (bsubs) ? bsubs : DEF_BSUBS;
	char *quick;

	if (asprintf(&quick, "/sys/class/power_supply/%s/capacity",
		(batn)?batn:DEF_BNAME) == -1)
		return -1;
	// get a quick capacity value if available
	fd = fopen(quick, "r");
	if (fd == NULL){
		free(quick);
	} else {
		fscanf(fd, "%d", &energy_now);
		fclose(fd);
		free(quick);
		return energy_now;
	}

	if (asprintf(&filename, "/sys/class/power_supply/%s/%s_now",
			(batn)?batn:DEF_BNAME, bsubsys ) == -1)
		return -1;

	fd = fopen(filename, "r");
	if(fd == NULL) {
		fprintf(stderr, "Error opening %s_now.\n", bsubsys);
		free(filename);
		return -1;
	}
	fscanf(fd, "%d", &energy_now);
	fclose(fd);
	free(filename);

	if (asprintf(&filename, "/sys/class/power_supply/%s/%s_full",
			(batn)?batn:DEF_BNAME, bsubsys ) == -1)
		return -1;

	fd = fopen(filename, "r");
	if(fd == NULL) {
		fprintf(stderr, "Error opening %s_full.\n", bsubsys);
		free(filename);
		return -1;
	}
	fscanf(fd, "%d", &energy_full);
	fclose(fd);
	free(filename);

	if (asprintf(&filename, "/sys/class/power_supply/%s/voltage_now",
			(batn)?batn:DEF_BNAME ) == -1)
		return -1;

	fd = fopen(filename, "r");
	if(fd == NULL) {
		fprintf(stderr, "Error opening voltage_now.\n");
		free(filename);
		return -1;
	}
	fscanf(fd, "%d", &voltage_now);
	fclose(fd);
	free(filename);

	return ((float)energy_now * 1000 / (float)voltage_now) * 100 / ((float)energy_full * 1000 / (float)voltage_now);
}

char*
get_iface_state(const char* ifname){
#ifndef DEF_IFNAME
#define DEF_IFNAME "wlan0"
#endif
  FILE *fd;
  char state[5] = {0};
  char *ret , *filename;

  if (NULL == ifname)
	ifname = DEF_IFNAME;

  if (asprintf(&filename, "/sys/class/net/%s/operstate", ifname) == -1)
			return NULL;

  fd = fopen(filename, "r");
  if(fd == NULL) {
	fprintf(stderr, "Error opening interface state.\n");
	free(filename);
	return NULL;
  }

  fscanf(fd, "%4s", state);
  fclose(fd);
  free(filename);

  if (strncmp(state,"up",2) == 0){
	asprintf(&ret, "(%s)", (strncmp(ifname,"wlan",4))?"E":"W");
  } else if (strncmp(state,"down",4) == 0) {
	asprintf(&ret, "(%s)", "-");
  } else {
	asprintf(&ret, "(%s)", "?");
  }
  return ret;
}

int
main(int cn, char** cv) {
	char *status;
	char *datetime;
	int bat0 = 0;
	int count = 0;
	int interval = 0;
	
	char *iface = NULL, *ifstate = NULL;
	char *batn = NULL, *bats = NULL;
	int ch;
	
	while ((ch = getopt (cn, cv, "i:b:B:t:h")) > 0){
		switch(ch){
			case 'i': /* interface name */
				iface = optarg;
				break;
			case 't': /* timeout */
				interval = atoi(optarg);
				break;
			case 'h': /* print usage */
				printf("\tUsage: %s [options]\n"
					"\t\t-i network interface name (default is 'wlan0')\n"
					"\t\t-b battery class name (default is 'BAT0')\n"
					"\t\t-t time interval between updates = 1-60 sec (default is 12)\n"
					"\t\t-B battery subsystem prefix (i.e. 'power' or 'energy', default is 'energy')\n"
					, cv[0]);
				return 0;
				break;
			case 'b': /* battery class name */
				batn = optarg;
				break;
			case 'B': /* battery class name */
				bats = optarg;
				break;
			default:
				return 0;
		}
	}

	if (interval < 1 || interval > 60)
		interval = 12;

	if (!(dpy = XOpenDisplay(NULL))) {
		fprintf(stderr, "Cannot open display.\n");
		return 1;
	}

	if((status = malloc(200)) == NULL)
		exit(1);

	
	for (;;count++) {
		datetime = gettime_basic();
		if ( count % interval == 0 ){
			bat0 = getbattery(batn, bats);
			if (ifstate) free(ifstate);
			ifstate = get_iface_state(iface);
		}
		snprintf(status, 15, "%d%% %s %s", bat0, ifstate,datetime);

		free(datetime);
		setstatus(status);
		
		sleep (1);
	}

	if (ifstate) free(ifstate);

	free(status);
	XCloseDisplay(dpy);

	return 0;
}

