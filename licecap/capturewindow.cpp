#include "../../WDL/WDL/swell/swell.h"
#include "../../WDL/WDL/swell/swell-internal.h"
#include "../../WDL/WDL/lice/lice.h"
#include <gdk/gdk.h>

bool GetScreenData(int xpos, int ypos, LICE_IBitmap *bmOut)
{
  printf("Getting screen data failed\n");
	return false;
}

void DoMouseCursor(LICE_IBitmap *bmOut, int xoffs, int yoffs)
{
  printf("fail cursor\n");
}

void DrawTransparentRectInCurrentContext(RECT r)
{
  printf("Drawing transparent rect failed \n");
}

void RefreshWindowShadows(HWND h)
{
  printf("Refreshing window shadows failed\n");
}

void SWELL_SetWindowResizeable(HWND h, bool allow)
{
  printf("Un-/Setting window resizable failed\n");
}
