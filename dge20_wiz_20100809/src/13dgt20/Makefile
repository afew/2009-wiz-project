################################################################################
##

# TARGET PLATFORM
tpf = wiz

TARGET_S = libdgt20.a
TARGET_D = libdgt20.so
TARGET_V = .2.0.1


L_SRCS = \
	vkb/Automata.cpp \
	vkb/VirtualKeyboard.cpp \
	DGT_Util.cpp \
	DGT_SpriteMx.cpp \
	DGT_Lzo.c \
	lzo/lzo1.c \
	lzo/lzo1_99.c \
	lzo/lzo1a.c \
	lzo/lzo1a_99.c \
	lzo/lzo1b_1.c \
	lzo/lzo1b_2.c \
	lzo/lzo1b_3.c \
	lzo/lzo1b_4.c \
	lzo/lzo1b_5.c \
	lzo/lzo1b_6.c \
	lzo/lzo1b_7.c \
	lzo/lzo1b_8.c \
	lzo/lzo1b_9.c \
	lzo/lzo1b_99.c \
	lzo/lzo1b_9x.c \
	lzo/lzo1b_cc.c \
	lzo/lzo1b_d1.c \
	lzo/lzo1b_d2.c \
	lzo/lzo1b_rr.c \
	lzo/lzo1b_xx.c \
	lzo/lzo1c_1.c \
	lzo/lzo1c_2.c \
	lzo/lzo1c_3.c \
	lzo/lzo1c_4.c \
	lzo/lzo1c_5.c \
	lzo/lzo1c_6.c \
	lzo/lzo1c_7.c \
	lzo/lzo1c_8.c \
	lzo/lzo1c_9.c \
	lzo/lzo1c_99.c \
	lzo/lzo1c_9x.c \
	lzo/lzo1c_cc.c \
	lzo/lzo1c_d1.c \
	lzo/lzo1c_d2.c \
	lzo/lzo1c_rr.c \
	lzo/lzo1c_xx.c \
	lzo/lzo1f_1.c \
	lzo/lzo1f_9x.c \
	lzo/lzo1f_d1.c \
	lzo/lzo1f_d2.c \
	lzo/lzo1x_1.c \
	lzo/lzo1x_1k.c \
	lzo/lzo1x_1l.c \
	lzo/lzo1x_1o.c \
	lzo/lzo1x_9x.c \
	lzo/lzo1x_d1.c \
	lzo/lzo1x_d2.c \
	lzo/lzo1x_d3.c \
	lzo/lzo1x_o.c \
	lzo/lzo1y_1.c \
	lzo/lzo1y_9x.c \
	lzo/lzo1y_d1.c \
	lzo/lzo1y_d2.c \
	lzo/lzo1y_d3.c \
	lzo/lzo1y_o.c \
	lzo/lzo1z_9x.c \
	lzo/lzo1z_d1.c \
	lzo/lzo1z_d2.c \
	lzo/lzo1z_d3.c \
	lzo/lzo2a_9x.c \
	lzo/lzo2a_d1.c \
	lzo/lzo2a_d2.c \
	lzo/lzo_crc.c \
	lzo/lzo_init.c \
	lzo/lzo_ptr.c \
	lzo/lzo_str.c \
	lzo/lzo_util.c

L_OBJS = \
	Automata.o \
	VirtualKeyboard.o \
	DGT_Util.o \
	DGT_SpriteMx.o \
	DGT_Lzo.o \
	lzo1.o \
	lzo1_99.o \
	lzo1a.o \
	lzo1a_99.o \
	lzo1b_1.o \
	lzo1b_2.o \
	lzo1b_3.o \
	lzo1b_4.o \
	lzo1b_5.o \
	lzo1b_6.o \
	lzo1b_7.o \
	lzo1b_8.o \
	lzo1b_9.o \
	lzo1b_99.o \
	lzo1b_9x.o \
	lzo1b_cc.o \
	lzo1b_d1.o \
	lzo1b_d2.o \
	lzo1b_rr.o \
	lzo1b_xx.o \
	lzo1c_1.o \
	lzo1c_2.o \
	lzo1c_3.o \
	lzo1c_4.o \
	lzo1c_5.o \
	lzo1c_6.o \
	lzo1c_7.o \
	lzo1c_8.o \
	lzo1c_9.o \
	lzo1c_99.o \
	lzo1c_9x.o \
	lzo1c_cc.o \
	lzo1c_d1.o \
	lzo1c_d2.o \
	lzo1c_rr.o \
	lzo1c_xx.o \
	lzo1f_1.o \
	lzo1f_9x.o \
	lzo1f_d1.o \
	lzo1f_d2.o \
	lzo1x_1.o \
	lzo1x_1k.o \
	lzo1x_1l.o \
	lzo1x_1o.o \
	lzo1x_9x.o \
	lzo1x_d1.o \
	lzo1x_d2.o \
	lzo1x_d3.o \
	lzo1x_o.o \
	lzo1y_1.o \
	lzo1y_9x.o \
	lzo1y_d1.o \
	lzo1y_d2.o \
	lzo1y_d3.o \
	lzo1y_o.o \
	lzo1z_9x.o \
	lzo1z_d1.o \
	lzo1z_d2.o \
	lzo1z_d3.o \
	lzo2a_9x.o \
	lzo2a_d1.o \
	lzo2a_d2.o \
	lzo_crc.o \
	lzo_init.o \
	lzo_ptr.o \
	lzo_str.o \
	lzo_util.o


L_SRCS += DGT_DRM.cpp
L_OBJS += DGT_DRM.o

########################################################################

SOURCES = $(L_SRCS)
OBJECTS = $(L_OBJS)

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

	TARGET_S = libdgt20w.a
	TARGET_D = libdgt20w.so

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


LIBRARY+= -linkadrm -ldrmcode
LIBRARY+= -lglport -lopengles_lite -lpng -lfreetype -lz -lts -lm -lc -s -lpthread


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

