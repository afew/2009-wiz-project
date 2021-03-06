################################################################################
## Compiler = gcc

# TARGET PLATFORM
tpf = wiz

TARGET_S	= libopenalut11.a
TARGET_F	= libopenalut11.so
T_VERSION	= .2.0.1


L_SRCS = \
	alutBufferData.c	\
	alutCodec.c		\
	alutError.c		\
	alutInit.c		\
	alutInputStream.c	\
	alutLoader.c		\
	alutOutputStream.c	\
	alutUtil.c		\
	alutVersion.c		\
	alutWaveform.c

########################################################################

SOURCES = $(L_SRCS)
OBJECTS = $(L_SRCS:.c=.o)

INCS    =
LIBS    =
LIBRARY =

COMPILER= arm-linux-gcc
CFLAGS  = -fPIC -c -Os -Wall

TARGET  =
TARGET_DIR =

########################################################################
# For WIZ
ifeq ($(tpf), wiz)

	TARGET_S	= libopenalut11w.a
	TARGET_F	= libopenalut11w.so

	TARGET_DIR= ../../lib

	GPH_HOME= D:/_GPH_SDK10_02
	DGE_GSH = D:/_cygwin/home/Administrator/dge20_wiz

	INCS  = -I$(GPH_HOME)/DGE/include
	INCS += -I$(GPH_HOME)/include
	INCS += -I$(GPH_HOME)/include/freetype2
	INCS += -I$(DGE_GSH)/include
	INCS += -I./

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
	INCS += -I./

	LIBS  = -L$(TOOL_DIR)/$(PREFIX)/sys-root/usr/lib
	LIBS += -L$(DGE_GSH)/lib
	LIBS += -L$(GPH_HOME)/lib/target
	LIBS += -L$(GPH_HOME)/DGE/lib/target

	COMPILER= $(TOOL_DIR)/bin/$(PREFIX)-gcc
	CFLAGS += -g -fno-common -march=armv5te -mtune=arm9tdmi -mapcs -msoft-float

endif

########################################################################


LIBRARY+= -lz -lts -lm -lc


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

