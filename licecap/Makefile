APPNAME=Licecap

WDL_PATH = ../WDL
vpath swell%.cpp $(WDL_PATH)/swell		# FOR MAKE: specify paths for missing pre-requisites
vpath lice%.cpp $(WDL_PATH)/lice
vpath png%.c $(WDL_PATH)/libpng
vpath %.c $(WDL_PATH)/zlib
vpath %.cpp $(WDL_PATH)/wingui $(WDL_PATH)/ $(WDL_PATH)/jnetlib/
vpath %.c $(WDL_PATH)/giflib $(WDL_PATH)/



###### Objects and resources (probably too many for now)
SWELL_OBJS = swell.o swell-ini.o swell-miscdlg-generic.o swell-wnd-generic.o \
             swell-menu-generic.o swell-kb-generic.o swell-dlg-generic.o \
             swell-gdi-generic.o swell-misc-generic.o swell-gdi-lice.o \
             swell-generic-headless.o swell-generic-gdk.o \
             swell-appstub-generic.o swell-modstub-generic.o

LICE_OBJS = lice.o  lice_arc.o lice_colorspace.o lice_line.o lice_text.o \
            lice_textnew.o lice_ico.o lice_bmp.o lice_lcf.o lice_gif_write.o \
            lice_png_write.o lice_palette.o lice_gif.o lice_png.o
            
GIF_OBJS = dgif_lib.o egif_lib.o gif_hash.o gifalloc.o
#CFLAGS += -DHAVE_CONFIG_H	#used by giflib

PNG_OBJS = png.o pngerror.o pngget.o pngmem.o pngpread.o pngread.o \
           pngrio.o pngrtran.o pngrutil.o pngset.o pngtrans.o pngwio.o \
           pngwrite.o pngwtran.o pngwutil.o
           
ZLIB_OBJS = adler32.o compress.o crc32.o deflate.o infback.o inffast.o inflate.o \
            inftrees.o trees.o uncompr.o zutil.o
            
OTHER_OBJS = wndsize.o filebrowse.o

RESFILES = licecap.rc_mac_dlg licecap.rc_mac_menu

OBJS += main.o licecap_ui.o capturewindow.o $(SWELL_OBJS) $(GIF_OBJS) $(PNG_OBJS) $(ZLIB_OBJS) $(LICE_OBJS) $(OTHER_OBJS)



CFLAGS += -pipe -fvisibility=hidden -fno-math-errno -fPIC -DPIC -Wall -Wshadow -Wno-unused-function -Wno-multichar -Wno-unused-result

ifndef ALLOW_WARNINGS
#  CFLAGS += -Werror
endif
ifndef DEPRECATED_WARNINGS
  CFLAGS +=  -Wno-deprecated-declarations
endif

ifdef DEBUG
	CFLAGS += -O0 -g -D_DEBUG
else
	CFLAGS += -O2 -DNDEBUG
endif
CFLAGS += -DSWELL_LICE_GDI -DPNG_WRITE_SUPPORTED
LFLAGS = -lpthread -ldl -lX11 -lXi


###### GDK
CFLAGS += -DSWELL_TARGET_GDK=3 $(shell pkg-config --cflags gdk-3.0)
LFLAGS += $(shell pkg-config --libs gdk-3.0)


###### Freetype
CFLAGS += -DSWELL_FREETYPE $(shell freetype-config --cflags)
LFLAGS += $(shell freetype-config --libs)



CXXFLAGS = $(CFLAGS)
default: $(APPNAME)

.PHONY: clean run

$(RESFILES): licecap.rc
	php $(WDL_PATH)/swell/mac_resgen.php $^
	
$(APPNAME): $(RESFILES) $(OBJS)
	$(CXX) -o $@ $(CFLAGS) $(OBJS) $(LFLAGS)

run: $(APPNAME)
	./$^

clean:
	-rm $(OBJS) $(APPNAME) $(RESFILES)