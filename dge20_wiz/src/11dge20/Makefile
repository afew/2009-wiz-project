################################################################################
## Compiler = g++

# TARGET PLATFORM
tpf = wiz

TARGET_S	= libdge20.a
TARGET_F	= libdge20.so
T_VERSION	= .2.0.1


ifeq ($(tpf), wiz)
	L_SRCS = DGE_Input10.c

else
	L_SRCS = DGE_Input20.c

endif

L_SRCS += \
	DGE_Haptic.c \
	DGE_Gsensor.c \
	te9_tf9_hybrid_driver.c \
	DGE_Time.c \
	ImgBmp.c \
	ImgTga.c \
	ImgPng.c \
	ImgGpt.c

	
L_SRCS2 = \
	DGE_System.cpp \
	DGE_Util.cpp \
	DGE10_Log.cpp \
	DGE10_File.cpp \
	DGE_Math.cpp \
	DGE_Device.cpp \
	DGE_Sprite.cpp \
	DGE_Image.cpp \
	DGE_Texture.cpp \
	DGE_vbo.cpp

########################################################################

SOURCES = $(L_SRCS)
OBJECTS = $(L_SRCS:.c=.o)

SOURCES += $(L_SRCS2)
OBJECTS += $(L_SRCS2:.cpp=.o)

INCS    =
LIBS    =
LIBRARY =

COMPILER= arm-linux-g++
CFLAGS  = -fPIC -c -Os -Wall

TARGET  =
TARGET_DIR =

########################################################################
# For WIZ
ifeq ($(tpf), wiz)

	TARGET_S	= libdge20w.a
	TARGET_F	= libdge20w.so

	TARGET_DIR= ../../lib

	GPH_HOME= D:/_GPH_SDK10_02
	DGE_GSH = D:/_cygwin/home/Administrator/dge20_wiz

	INCS  = -I$(GPH_HOME)/DGE/include
	INCS += -I$(GPH_HOME)/include
	INCS += -I$(GPH_HOME)/include/freetype2
	INCS += -I$(DGE_GSH)/include

	LIBS  = -L$(GPH_HOME)/DGE/lib/target
	LIBS += -L$(GPH_HOME)/lib/target
	LIBS += -L$(DGE_GSH)/lib

######################################
# For N35
else

	TARGET_DIR= /N35_work/dge20/lib

	TOOL_DIR= /opt/cross-eabi
	GPH_HOME= /opt/GPH_SDK
	DGE_GSH = /N35_work/dge20
	PREFIX  = arm-gph-linux-gnueabi

	INCS  = -I$(TOOL_DIR)/$(PREFIX)/sys-root/usr/include
	INCS += -I$(GPH_HOME)/DGE/include
	INCS += -I$(GPH_HOME)/include
	INCS += -I$(DGE_GSH)/include

	LIBS  = -L$(TOOL_DIR)/$(PREFIX)/sys-root/usr/lib
	LIBS += -L$(DGE_GSH)/lib
	LIBS += -L$(GPH_HOME)/lib/target
	LIBS += -L$(GPH_HOME)/DGE/lib/target

	COMPILER= $(TOOL_DIR)/bin/$(PREFIX)-g++
	CFLAGS += -g -fno-common -march=armv5te -mtune=arm9tdmi -mapcs -msoft-float

endif

########################################################################


LIBRARY+= -lglport -lopengles_lite -lpng -lfreetype -lz -lts -lm -lc -s -lpthread


TARGET = $(TARGET_F)$(T_VERSION)
TARGET_A= $(TARGET_DIR)/$(TARGET_S)


t:
	$(COMPILER) $(SOURCES) $(INCS) $(CFLAGS)

#ifeq ($(tpf), wiz)
#	ar rcvs $(TARGET_A) $(OBJECTS)
#endif

	$(COMPILER) -shared -Wall -o $(TARGET) $(OBJECTS) $(LIBRARY) $(LIBS)

	rm -f $(OBJECTS) $(TARGET_F)
	rm -f $(TARGET_DIR)/$(TARGET_F)
	rm -f $(TARGET_DIR)/$(TARGET)

	ln -s $(TARGET) $(TARGET_F)


	cp $(TARGET) $(TARGET_DIR)
	cp $(TARGET_F) $(TARGET_DIR)


	rm -f $(TARGET) $(TARGET_F)

################################################################################

