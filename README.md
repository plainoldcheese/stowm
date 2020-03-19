# SLOWM

slightly less opinionated window manager

this window manager is inspired by sowm and uses tinywm as a code base.

the intent is to stay under 150 lines of code with the following goals.

1. leave most if not all keyboard shortcuts to an external tool such as sxhkd.
2. make configuration a little easier (althoug the use of a ``config.h`` will probably still be the case)
3. make insterfacing with other programs such as polybar a little easier.

the feautures i most want are

1. super + tab to cycle windows
2. focus follows mouse and window under mouse is raised
3. Toggling of full-screen and window centering
4. virtual desktops that are aware of windows inside them

in essence this will be a reimplementation of sowm following tinywm as an example and borrowing less code from other projects. This window manager serves as an excercise in C programming with the XLib libraries for me.
