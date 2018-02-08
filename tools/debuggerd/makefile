COMPILER_DIR := /opt/EmbedSky/4.4.6/bin
PROJECT_DIR         := ../..


COMPILER_PREFIX     := arm-linux-
CC                  := $(COMPILER_DIR)/$(COMPILER_PREFIX)gcc
CXX                 := $(COMPILER_DIR)/$(COMPILER_PREFIX)g++
AR	                := $(COMPILER_DIR)/$(COMPILER_PREFIX)ar
LD               	:= $(COMPILER_DIR)/$(COMPILER_PREFIX)ld


TARGET := debuggerd

SRCDIR := ./src


OBJDIR := $(PROJECT_DIR)/out/tools/debuggerd/obj
#LIBDIR := $(PROJECT_DIR)/out/tools/debuggerd/lib
BINDIR := $(PROJECT_DIR)/out/tools/debuggerd/bin


CFLAGS  :=  -fPIC
CFLAGS  += -DHAVE_PTHREADS
CFLAGS  += -DHAVE_SYS_UIO_H
CFLAGS  += -DHAVE_ENDIAN_H
CFLAGS  += -DHAVE_ANDROID_OS=1
CFLAGS  += -DHAVE_IOCTL
CFLAGS  += -DHAVE_LINUX_LOCAL_SOCKET_NAMESPACE

LIBS := \
	-llog \
	-lbinder \
	-lutils \
	-lcutils \
	-lpthread \
	-lrt \
	-lalarmmanager \
	

LIBDIRS := \
	-L ../../out/libs/liblog/lib \
	-L ../../out/libs/libbinder/lib \
	-L ../../out/libs/libutils/lib \
	-L ../../out/libs/libcutils/lib \
	-L ../../out/framework/managers/alarmmanager/lib/

INCPATHS := \
	-I ../../libs/include/ \
	-I ../../framework/managers/alarmmanager/inc/
	
SOURCES := \
	debuggerd.c \
	utility.c \
	getevent.c \
	machine.c \
	unwind.c \
	symbol_table.c \
	pr-support.c \


OBJECTS := $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))

$(BINDIR)/$(TARGET): $(OBJECTS)
	@-mkdir -p $(BINDIR) 2> /dev/null
#	$(AR)  -rcs $(BINDIR)/$(TARGET) $(OBJECTS)
	$(CC) $(LIBDIRS) $(LIBS) $(OBJECTS) -o  $(BINDIR)/$(TARGET) 

$(OBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.c
	@-mkdir -p $(OBJDIR) 2> /dev/null
	$(CC) -c $(CFLAGS) $(INCPATHS) -o $@  $<

all: $(OBJECTS) $(BINDIR)/$(TARGET)

clean:
	rm -f $(OBJECTS) $(BINDIR)/$(TARGET)

