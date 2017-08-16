TARGET = packslide
OBJS = core.o ximage.o ft_gl.o libpuyo.o orzpcm.o

INCDIR = 
CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = PackSlide
PSP_EBOOT_ICON = icon1.png
PSP_EBOOT_PIC1 = back.png

PSPSDK=$(shell psp-config --pspsdk-path)
PSPBIN = $(PSPSDK)/../bin
CFLAGS += $(shell $(PSPBIN)/sdl-config --cflags)
LIBS += $(shell $(PSPBIN)/sdl-config --libs)
LIBS += -lfreetype
include $(PSPSDK)/lib/build.mak
