#!/bin/sh 
if [ $# -eq 0 ]; then
	. /etc/X11/xinit/xinitrc
else
	unset LD_LIBRARY_PATH
	if [ ${1} = "dwm" ];then
		export PATH=${HOME}/.dwm/bin:${PATH}
#		osd_clock -F "%A %d-%b-%Y %H:%M (%Z)" -c gray -f "-*-terminus-medium-r-*-*-16-*-*-*-*-*-*-*" -i 2 -d 2 &
#		tdc -f "%H:%M" &
		~/__devel/__main/xkb_state
		dwmstatus_basic&
#		fbpanel &
		clipit &
	else
		xxkb&
	fi
	xrdb -load $HOME/.Xresourses&
	wpsetters=feh fbsetbg -b -solid black&
	exec $@ 
fi

