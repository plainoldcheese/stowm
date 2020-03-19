#include <X11/Xlib.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))
// set Modifierkey to Left Super Key
#define MOD Mod4Mask 

static Display    *dpy;

int main(void){

	Window root;
	XWindowAttributes attr;
	XButtonEvent start;
	XEvent ev;

	if(!(dpy = XOpenDisplay(0x0))) return 1;

	root = DefaultRootWindow(dpy);
	int screen = DefaultScreen(dpy);
	int screenWidth = XDisplayWidth(dpy, screen);
	int screenHeight = XDisplayHeight(dpy, screen);


	XGrabKey(dpy, XKeysymToKeycode(dpy, XStringToKeysym("Tab")), MOD, DefaultRootWindow(dpy), True, GrabModeAsync, GrabModeAsync);

	XGrabKey(dpy, XKeysymToKeycode(dpy, XStringToKeysym("q")), MOD, DefaultRootWindow(dpy), True, GrabModeAsync, GrabModeAsync);

	XGrabKey(dpy, XKeysymToKeycode(dpy, XStringToKeysym("c")), MOD, DefaultRootWindow(dpy), True, GrabModeAsync, GrabModeAsync);

	XGrabKey(dpy, XKeysymToKeycode(dpy, XStringToKeysym("f")), MOD, DefaultRootWindow(dpy), True, GrabModeAsync, GrabModeAsync);

	XGrabButton(dpy, 1, MOD, DefaultRootWindow(dpy), True, ButtonPressMask|ButtonReleaseMask|PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None);

	XGrabButton(dpy, 3, MOD, DefaultRootWindow(dpy), True, ButtonPressMask|ButtonReleaseMask|PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None);

	XGrabButton(dpy, AnyButton, EnterWindowMask, DefaultRootWindow(dpy), True, ButtonPressMask|ButtonReleaseMask|PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None);

	//XGrabPointer(dpy, DefaultRootWindow(dpy), True, EnterWindowMask|PointerMotionMask|FocusChangeMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime);

	start.subwindow = None;

	for(;;){
		XNextEvent(dpy, &ev);


		// keyboard stuff
		if (ev.type == KeyPress && ev.xkey.subwindow != None)
		{
			// raise window whenever an action occurs on a window
			XRaiseWindow(dpy, ev.xkey.subwindow);

			// tab to switch through windows
			if (ev.xkey.keycode == XKeysymToKeycode(dpy, XStringToKeysym("Tab")))
				XRaiseWindow(dpy, ev.xkey.subwindow);

			// kill window with pointer in it on keypress "q"
			if (ev.xkey.keycode == XKeysymToKeycode(dpy, XStringToKeysym("q")))
				XKillClient(dpy, ev.xkey.subwindow);

			//centre windows with "c"
			if (ev.xkey.keycode == XKeysymToKeycode(dpy, XStringToKeysym("c")))
			{
				XMoveWindow(dpy, ev.xkey.subwindow, ((screenWidth - attr.width)/2), ((screenHeight - attr.height)/2));
			}

			// toggle fullscreen windows with "f"
			if (ev.xkey.keycode == XKeysymToKeycode(dpy, XStringToKeysym("f")))
			{
				XGetWindowAttributes(dpy, ev.xkey.subwindow, &attr);
				if (attr.width >= screenWidth || attr.height >= screenHeight)
				{
					// if window already fulscrean resize to 1/2 of screen resolution and centre
					XMoveResizeWindow(dpy, ev.xkey.subwindow, ((screenWidth - attr.width)/2), ((screenHeight - attr.height)/2), screenWidth/2, screenHeight/2);
				}
				else
				{
					XMoveResizeWindow(dpy, ev.xkey.subwindow, 0, 0, screenWidth, screenHeight);
				}
			}
		}

		// mouse stuff
		// moving window with mouse
		else if (ev.type == ButtonPress && ev.xbutton.subwindow != None)
		{
			XGetWindowAttributes(dpy, ev.xbutton.subwindow, &attr);
			start = ev.xbutton;
			// raise on click
			XRaiseWindow(dpy, ev.xkey.subwindow);
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
		// focus on mose hover

		
		else if (ev.type == ButtonPress && ev.xcrossing.subwindow != None)
		{
			XGetWindowAttributes(dpy, ev.xcrossing.subwindow, &attr);
			XSetInputFocus(dpy, ev.xcrossing.subwindow, RevertToPointerRoot, CurrentTime);
			XRaiseWindow(dpy, ev.xcrossing.subwindow);
		}

	}
}
