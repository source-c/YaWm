#!/bin/sh 
if [ $# -eq 0 ]; then
	. /etc/X11/xinit/xinitrc
else
	unset LD_LIBRARY_PATH
	if [ ${1} = "yawm" ];then
		export PATH=${HOME}/.yawm/bin:${PATH}
		yawmstatus &
		clipit &
	else
		xxkb&
	fi
	xrdb -load $HOME/.Xresourses&
	WLPDIR=${HOME}/.yawm/wallpapers
	if [ -d "${WLPDIR}" ]; then
		wpsetters=feh fbsetbg -a ${WLPDIR}/`ls -1 ${WLPDIR}|sort -R|head -1` &
	else
		wpsetters=feh fbsetbg -b -solid black&
	fi
	exec $@ 
fi

