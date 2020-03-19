#include <X11/Xlib.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))
// set Modifierkey to Left Super Key
#define MOD Mod2Mask 

static Display * dpy;
static int screenWidth, screenHeight, screen = 0;

int main(void){

	XWindowAttributes attr;
	XButtonEvent start;
	XEvent ev;

	screen = DefaultScreen(dpy);
	screenWidth = XDisplayWidth(dpy, screen);
    screenHeight = XDisplayHeight(dpy, screen);

	if(!(dpy = XOpenDisplay(0x0))) return 1;

	XGrabKey(dpy, XKeysymToKeycode(dpy, XStringToKeysym("Tab")), MOD, DefaultRootWindow(dpy), True, GrabModeAsync, GrabModeAsync);

//	XGrabKey(dpy, XKeysymToKeycode(dpy, XStringToKeysym("q")), MOD, DefaultRootWindow(dpy), True, GrabModeAsync, GrabModeAsync);
//
//	XGrabKey(dpy, XKeysymToKeycode(dpy, XStringToKeysym("c")), MOD, DefaultRootWindow(dpy), True, GrabModeAsync, GrabModeAsync);
//
//	XGrabKey(dpy, XKeysymToKeycode(dpy, XStringToKeysym("f")), MOD, DefaultRootWindow(dpy), True, GrabModeAsync, GrabModeAsync);

	XGrabButton(dpy, 1, MOD, DefaultRootWindow(dpy), True, ButtonPressMask|ButtonReleaseMask|PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None);

	XGrabButton(dpy, 3, MOD, DefaultRootWindow(dpy), True, ButtonPressMask|ButtonReleaseMask|PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None);

	start.subwindow = None;

	for(;;){
		XNextEvent(dpy, &ev);

		/*
		// keyboard stuff
		if (ev.type == KeyPress)
		{
			XGetWindowAttributes(dpy, PointerWindow, &attr);

			// kill window with pointer in it on keypress "q"
			if (ev.xkey.keycode == XKeysymToKeycode(dpy, XStringToKeysym("q")))
				 XDestroyWindow(dpy, PointerWindow);

			// tab to switch through windows
			if (ev.xkey.keycode == XKeysymToKeycode(dpy, XStringToKeysym("Tab")))
				XRaiseWindow(dpy, ev.xkey.subwindow);

			// toggle fullscreen windows with "f"
			if (ev.xkey.keycode == XKeysymToKeycode(dpy, XStringToKeysym("f")))
			{
				if (attr.width >= screenWidth || attr.height >= screenHeight)
				{
					;
				}
				else
				{
					XMoveResizeWindow(dpy, PointerWindow, 0, 0, screenWidth, screenHeight);
				}
			}
			//centre windows with "c"
			if (ev.xkey.keycode == XKeysymToKeycode(dpy, XStringToKeysym("c")))
			{
							XMoveWindow(dpy, PointerWindow, (screenWidth - attr.width)/2, (screenHeight - attr.height)/2);
			}
		}
		*/

		// testing this
		if (ev.type == KeyPress && ev.xkey.subwindow != None)
		{
			XRaiseWindow(dpy, ev.xkey.subwindow);
		}
		// mouse stuff
		// moving window with mouse
		else if (ev.type == ButtonPress && ev.xbutton.subwindow != None)
		{
			XGetWindowAttributes(dpy, ev.xbutton.subwindow, &attr);
			start = ev.xbutton;
		}
		// resizing window
		else if (ev.type == MotionNotify && start.subwindow !=None)
		{
			int xdiff = ev.xbutton.x_root - start.x_root;
			int ydiff = ev.xbutton.y_root - start.y_root;
			XMoveResizeWindow(dpy, start.subwindow,
					attr.x + (start.button==1 ? xdiff :0),
					attr.y + (start.button==1 ? ydiff :0),
					MAX(1, attr.width + (start.button==3 ? xdiff :0)),
					MAX(1, attr.height + (start.button==3 ? ydiff :0)));
		}
		// letting go of mouse to stop actions
		else if (ev.type == ButtonRelease)
		{
			start.subwindow = None;
		}
	}
}
