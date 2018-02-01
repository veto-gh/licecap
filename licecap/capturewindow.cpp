#include "../../WDL/WDL/swell/swell.h"
#include "../../WDL/WDL/swell/swell-internal.h"
#include "../../WDL/WDL/lice/lice.h"
#include <gdk/gdk.h>
#include <gdk/gdkx.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xfixes.h>
#include <X11/extensions/shape.h>

bool GetScreenData(int xpos, int ypos, LICE_IBitmap *bmOut)
{ 
  // https://git.xfce.org/apps/xfce4-screenshooter/tree/lib/screenshooter-capture.c#n325
  GdkWindow *root = gdk_get_default_root_window ();
  GdkPixbuf *sshot = gdk_pixbuf_get_from_window (root, xpos, ypos, bmOut->getWidth(), bmOut->getHeight());
  GdkPixbuf *sshota = gdk_pixbuf_add_alpha(sshot, FALSE, 0, 0, 0);
  guchar *pixels = gdk_pixbuf_get_pixels(sshota);
    
  LICE_IBitmap* tmpBm = new LICE_WrapperBitmap((LICE_pixel*)pixels, gdk_pixbuf_get_width(sshota), 
                                               gdk_pixbuf_get_height(sshota), 
                                               gdk_pixbuf_get_rowstride(sshota)/4, true);
  LICE_Copy(bmOut, tmpBm);
  delete tmpBm;
	return true;
}

void DoMouseCursor(LICE_IBitmap *bmOut, int xoffs, int yoffs)
{
  printf("fail cursor\n");
}

void DrawTransparentRectInCurrentContext(RECT r)
{
  
}

void RefreshWindowShadows(HWND h)
{
  printf("Refreshing window shadows failed\n");
}

void SWELL_SetWindowResizeable(HWND h, bool allow)
{
  printf("Un-/Setting window resizable failed\n");
}

void SetGdkWindowPassThrough(HWND h, RECT r)
{
  // https://stackoverflow.com/questions/4326534/x11-xlib-create-glasspane-window
  if (h==NULL || h->m_oswindow==NULL) return;
  Window w = GDK_WINDOW_XID(h->m_oswindow);
  Display *d=GDK_DISPLAY_XDISPLAY(gdk_display_get_default());

  XRectangle rect1 = {(short)r.left, (short)r.top, 
      (unsigned short)(r.right-r.left), (unsigned short)(r.bottom-r.top)};
  XserverRegion region1 = XFixesCreateRegion (d, &rect1, 1);
  RECT r2;
  GetClientRect(h,&r2);
  XRectangle rect2 = {(short)r2.left, (short)r2.top, 
      (unsigned short)(r2.right-r2.left), (unsigned short)(r2.bottom-r2.top)};
  XserverRegion region2 = XFixesCreateRegion (d, &rect2, 1);
  XserverRegion region3 = XFixesCreateRegion (d, NULL, 0);
  XFixesSubtractRegion (d, region3, region2, region1);
  
  XFixesSetWindowShapeRegion (d, w, ShapeBounding, 0, 0, 0);
  XFixesSetWindowShapeRegion (d, w, ShapeInput, 0, 0, region3);

  XFixesDestroyRegion (d, region1);
  XFixesDestroyRegion (d, region2);
  XFixesDestroyRegion (d, region3);
  
  // gdk_window_set_pass_through(Gdkwindow,passThrough); // Gdk 3.18
}

