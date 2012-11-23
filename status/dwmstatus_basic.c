/* 
** Basic dwm status with just time HH:MM and battery
** Compile with:
** gcc -Wall -pedantic -std=c99 -lX11 status.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define _XOPEN_SOURCE 1
#define _GNU_SOURCE

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
getbattery() {
	FILE *fd;
	int energy_now, energy_full, voltage_now;

	fd = fopen("/sys/class/power_supply/BAT0/energy_now", "r");
	if(fd == NULL) {
		fprintf(stderr, "Error opening energy_now.\n");
		return -1;
	}
	fscanf(fd, "%d", &energy_now);
	fclose(fd);


	fd = fopen("/sys/class/power_supply/BAT0/energy_full", "r");
	if(fd == NULL) {
		fprintf(stderr, "Error opening energy_full.\n");
		return -1;
	}
	fscanf(fd, "%d", &energy_full);
	fclose(fd);


	fd = fopen("/sys/class/power_supply/BAT0/voltage_now", "r");
	if(fd == NULL) {
		fprintf(stderr, "Error opening voltage_now.\n");
		return -1;
	}
	fscanf(fd, "%d", &voltage_now);
	fclose(fd);


	return ((float)energy_now * 1000 / (float)voltage_now) * 100 / ((float)energy_full * 1000 / (float)voltage_now);
}

int
main(int cn, char** cv) {
	char *status;
	char *datetime;
	int bat0;
	int count = 0;


	if (!(dpy = XOpenDisplay(NULL))) {
		fprintf(stderr, "Cannot open display.\n");
		return 1;
	}

	if((status = malloc(200)) == NULL)
		exit(1);
	

	for (;;count++) {
		datetime = gettime_basic();
		if ( count % 12 == 0 ){
			bat0 = getbattery();
		}
		snprintf(status, 14, "%d%% | %s", bat0, datetime);

		free(datetime);
		setstatus(status);
		
		sleep (1);
	}

	free(status);
	XCloseDisplay(dpy);

	return 0;
}

