################################################################################
## Compiler = g++

# TARGET PLATFORM
tpf = wiz

TARGET_S	= libdgx20.a
TARGET_F	= libdgx20.so
T_VERSION	= .2.0.1


L_SRCS = \
	DGX_Font2.cpp \
	DGX_Font.cpp \
	DGX_Input.cpp \
	DGX_Mixer.cpp \
	DGX_Media.cpp \
	DGX_Sound.cpp \
	DGX_Network.cpp \
	DGX_Entity.cpp \
	DGX_Camera.cpp \
	DGX_GeoAxis.cpp \
	DGX_GeoGrid.cpp \
	_dge_ase/DGX_Ast.cpp \
	_dge_ase/DGX_Ast2.cpp \
	_dge_ase/DGX_Ast3.cpp \
	_dge_ase/DGX_AstIns.cpp \
	_dge_ase/DGX_Asb.cpp \
	_dge_ase/DGX_AsbIns.cpp \
	DGX_Mdl.cpp

L_OBJS = \
	DGX_Font2.o \
	DGX_Font.o \
	DGX_Input.o \
	DGX_Mixer.o \
	DGX_Media.o \
	DGX_Sound.o \
	DGX_Network.o \
	DGX_Entity.o \
	DGX_Camera.o \
	DGX_GeoAxis.o \
	DGX_GeoGrid.o \
	DGX_Ast.o \
	DGX_Ast2.o \
	DGX_Ast3.o \
	DGX_AstIns.o \
	DGX_Asb.o \
	DGX_AsbIns.o \
	DGX_Mdl.o

########################################################################

SOURCES = $(L_SRCS)
OBJECTS = $(L_OBJS)

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

	TARGET_S	= libdgx20w.a
	TARGET_F	= libdgx20w.so

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
	INCS += -I$(GPH_HOME)/include/freetype2
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

