################################################################################
##

# TARGET PLATFORM
tpf=n35

TARGET_S = liblua503.a
TARGET_D = liblua503.so
TARGET_V = .2.0.1


L_SRCS=	\
	lapi.cpp \
	lcode.cpp \
	luadbg.cpp \
	ldo.cpp \
	ldump.cpp \
	lfunc.cpp \
	lgc.cpp \
	llex.cpp \
	lmem.cpp \
	lobject.cpp \
	lopcodes.cpp \
	lparser.cpp \
	lstate.cpp \
	lstring.cpp \
	ltable.cpp \
	ltests.cpp \
	ltm.cpp \
	lundump.cpp \
	lvm.cpp \
	lzio.cpp \
	lauxlib.cpp \
	lbaselib.cpp \
	ldblib.cpp \
	liolib.cpp \
	lmathlib.cpp \
	ltablib.cpp \
	lstrlib.cpp \
	loadlib.cpp

########################################################################

SOURCES = $(L_SRCS)
OBJECTS = $(L_SRCS:.cpp=.o)

INCS    =
LIBS    =
LIBRARY =

COMPILER= arm-linux-g++
CFLAGS  = -fPIC -Wall -Os -c
LFLAGS  = -shared -Wall -o

TARGET  =
TARGET_DIR =

########################################################################
# For WIZ
ifeq ($(tpf), wiz)

	TARGET_S = liblua503w.a
	TARGET_D = liblua503w.so

	TARGET_DIR= ../../lib

	GPH_HOME= D:/_GPH_SDK10_02
	DGE_GSH = D:/_cygwin/home/Administrator/dge20_wiz

	INCS  = -I$(GPH_HOME)/DGE/include
	INCS += -I$(GPH_HOME)/include
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

	COMPILER= $(TOOL_DIR)/bin/$(PREFIX)-g++
	CFLAGS += -g -fno-common -march=armv5te -mtune=arm9tdmi -mapcs -msoft-float

endif

########################################################################


LIBRARY+= -lz -lts -lm -lc


TARGET = $(TARGET_D)$(TARGET_V)
TARGET_A= $(TARGET_DIR)/$(TARGET_S)


t:
	$(COMPILER) $(CFLAGS) $(SOURCES) $(INCS)

#ifeq ($(tpf), wiz)
#	ar crvs $(TARGET_A) $(OBJECTS)
#endif

	$(COMPILER) $(LFLAGS) $(TARGET) $(OBJECTS) $(LIBS) $(LIBRARY)

	rm -f $(OBJECTS) $(TARGET_D)
	rm -f $(TARGET_DIR)/$(TARGET_D)
	rm -f $(TARGET_DIR)/$(TARGET)

	ln -s $(TARGET) $(TARGET_D)


	cp $(TARGET) $(TARGET_DIR)
	cp -f -d $(TARGET_D) $(TARGET_DIR)


	rm -f $(TARGET) $(TARGET_D)

################################################################################

