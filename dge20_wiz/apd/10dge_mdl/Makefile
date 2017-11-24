################################################################################
## Compiler = g++

# TARGET PLATFORM
tpf = wiz

TARGET_F  = dge_mdl.gpe


L_SRCS = \
	AppDge.cpp \
	Main.cpp \
	dge.cpp

########################################################################

SOURCES = $(L_SRCS)
OBJECTS = $(L_SRCS:.cpp=.o)

INCS    =
LIBS    =
LIBRARY = -ldgx20 -ldge20 -lopenalut11 -lopenal11

COMPILER= arm-linux-g++
CFLAGS  = -fPIC -c -Os -Wall

TARGET  =
TARGET_DIR= ./../bin

########################################################################
# For WIZ
ifeq ($(tpf), wiz)

	LIBRARY = -ldgx20w -ldge20w -lopenalut11w -lopenal11w

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

	TOOL_DIR= /opt/cross-eabi
	GPH_HOME= /opt/GPH_SDK
	DGE_GSH = /N35_work/dge20
	PREFIX  = arm-gph-linux-gnueabi

	INCS  = -I$(TOOL_DIR)/$(PREFIX)/sys-root/usr/include
	INCS += -I$(GPH_HOME)/DGE/include
	INCS += -I$(GPH_HOME)/include
	INCS += -I$(DGE_GSH)/include

	LIBS  = -L$(TOOL_DIR)/$(PREFIX)/sys-root/usr/lib
	LIBS += -L$(SDK_HOME)/DGE/lib/target
	LIBS += -L$(SDK_HOME)/lib/target
	LIBS += -L$(DGE_GSH)/lib

	COMPILER= $(TOOL_DIR)/bin/$(PREFIX)-g++
	CFLAGS += -g -fno-common -march=armv5te -mtune=arm9tdmi -mapcs -msoft-float

endif

########################################################################


LIBRARY+= -lglport -lopengles_lite -lpng -lfreetype -lz -lts -lm -lc -s -lpthread


TARGET = $(TARGET_DIR)/$(TARGET_F)


g:
	$(COMPILER) $(CFLAGS)	 $(SOURCES) $(INCS)
	$(COMPILER) -o $(TARGET) $(OBJECTS) $(LIBRARY) $(LIBS)
	rm $(OBJECTS)

################################################################################

