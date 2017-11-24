################################################################################
## Compiler = g++
## TARGET PLATFORM
tpf = n35
TARGET_F  = ap7gravity.gpe

L_SRCS = \
	main.cpp

L_OBJS = \
	main.o


########################################################

SOURCES = $(L_SRCS)
OBJECTS = $(L_OBJS)

INCS    =
LIBS    =

LIBRARY = -ldgx20 -ldge20 -lopenalut11 -lopenal11
LIBRARY+= -lglport -lopengles_lite -lpng -lfreetype -lz -lts -lm -lc -s -lpthread

COMPILER=
CFLAGS  = -fPIC -c -Os -Wall

TARGET  =
TARGET_DIR= ./../bin


########################################################
# For WIZ
ifeq ($(tpf), wiz)

	GPH_HOME= D:/_GPH_SDK10_02
	DGE_GSH = D:/_cygwin/home/Administrator/dge20

	INCS  = -I$(GPH_HOME)/DGE/include
	INCS += -I$(GPH_HOME)/include
	INCS += -I$(GPH_HOME)/include/freetype2
	INCS += -I$(DGE_GSH)/include

	LIBS  = -L$(GPH_HOME)/DGE/lib/target
	LIBS += -L$(GPH_HOME)/lib/target
	LIBS += -L$(DGE_GSH)/lib

	COMPILER= arm-linux-g++

########################################################
# For N35
else

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
########################################################


TARGET = $(TARGET_DIR)/$(TARGET_F)


g:
	$(COMPILER) $(CFLAGS)	 $(SOURCES) $(INCS)
	$(COMPILER) -o $(TARGET) $(OBJECTS) $(LIBRARY) $(LIBS)
	rm $(OBJECTS)

################################################################################
