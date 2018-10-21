/*
    LICEcap
    Copyright (C) 2010 Cockos Incorporated

    LICEcap is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    LICEcap is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with LICEcap; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef __APPLE__
#include "../WDL/swell/swell.h"
#include "../WDL/swell/swell-internal.h"


int main(int argc, char **argv)
{
  extern HWND g_hwnd;

  SWELL_initargs(&argc,&argv);
  SWELL_Internal_PostMessage_Init();
  SWELL_ExtendedAPI("APPNAME",(void*)"LICEcap");
  SWELLAppMain(SWELLAPP_ONLOAD,0,0);
  SWELLAppMain(SWELLAPP_LOADED,0,0);
  while (g_hwnd && !g_hwnd->m_hashaddestroy) {
    SWELL_RunMessageLoop();
    Sleep(10);
  }
  SWELLAppMain(SWELLAPP_DESTROY,0,0);
  return 0;
}
#endif
