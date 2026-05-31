# Keyboard input

My initial goal was getting user input like a game engine does, detecting if key
was pressed/released.

I checked that it don't work in Linux terminal, because it needs administrative
privileges (a.k.a. sudo) to access the keyboard driver, and (as long as I
checked) there is no API to deal with that.

In the end, I used the X11 library to deal with keyboard input. X11 has access
to the driver and provides an API to indirectly access it, so my binary now
doesn't need administrative privileges to run.

The counterpoint is that it won't work in other window servers. Maybe the
correct way to do that was using Qt or something like that, but it still being a
starting point.

Another counterpoint is that console games in Linux still not possible without a
window as long as I know. I was trying to find something in Linux like
GetAsyncKeyState in Windows.

**Obs**: To be clear, ncurses and alternatives don't work the way I expect
because it cannot detect key releases. Real game engines don't work that way.

**Obs 2**: If you have a better alternative, please create a new issue to tell
me.

## Compiling and Running

```bash
$ gcc main.c -lX11
$ ./a.out
```
