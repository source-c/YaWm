YaWm
====

`YaWm` is just Yet Another Window Manager which is used by me from early 2012. Another meaning of the name is al-yawm [the day] (YaWm/wiki):

Originaly inspired by suckless's dwm. Reworked, patched, polished for my needs.
Have not pretensions to be compatible with the original anymore.

The main project's goal is to build comfortable X environment for myself in true unix way:
simple, flexible and strictly functional binary code that should help user to work
with his tasks with a maximal performance and to bring a high usability.
Not more But not less.

Minimal toolset (also partialy covered by this repo):
- yawm
- yawmstatus
- tinyterm (but `xterm` is pretty fine too)
- slock (has fallback to `xscreensaver`)
- dmenu

Other stuff for a minimal comfort:
- clipit
- volumeicon-alsa

In order to run the WM `xinit` and base X stuff are required.

Happy hacking!

Disclamer
=========

Despite the fact there are no active commits for a long time - the project is still active and maintained. The main binary is rock-stable and thus not requires changes. At least for author's needs.
Feel free to contact me if you're interested in and/or have any issues regarding the project.

Known issues
============

After a long period of inactivity the project became currently actual again.

As for now there're a lot of small (but terrible) issues in WM controls caused by a changes of related libraries.

- manual change of window geometry may work with bugs
- windows list is ugly and not usable
- window focus may change the windows stack position
- applications with full-screen mode behave strange and may sporadicaly not able for roll out on the full screen
- `slock` is not so compatible anymore with powersave mode of the screen as previously
