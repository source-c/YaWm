#!/bin/sh

YAWMDIR=${HOME}/.yawm

if [ $# -eq 0 ]; then
	. /etc/X11/xinit/xinitrc
else
	[ -n ${LD_LIBRARY_PATH} ] && unset LD_LIBRARY_PATH
	if [ "${1}"x = "yawm"x ];then
		[ -d "${YAWMDIR}/bin" ] && export PATH=${YAWMDIR}/bin:${PATH}
		[ -d "${YAWMDIR}/share/man" ] && export MANPATH=${YAWMDIR}/share/man:${MANPATH}
		[ -x "$(which yawmstatus)" ] && yawmstatus &
		[ -x "$(which clipit)" ] && clipit &
		export _JAVA_AWT_WM_NONREPARENTING=1
	else
		[ -x "$(which xxkb)" ] && xxkb&
	fi
	[ -r ${HOME}/.Xresources ] && xrdb -load ${HOME}/.Xresources&
	WLPDIR=${HOME}/.yawm/wallpapers
	if [ -d "${WLPDIR}" ]; then
		wpsetters=feh fbsetbg -a ${WLPDIR}/`ls -1 ${WLPDIR}|sort -R|head -1` &
	else
		wpsetters=feh fbsetbg -b -solid black&
	fi
	exec $@
fi

