COMPILER_DIR := /opt/EmbedSky/4.4.6/bin
PROJECT_DIR         := ../../..



COMPILER_PREFIX     := arm-linux-
CC                  := $(COMPILER_DIR)/$(COMPILER_PREFIX)gcc
CXX                 := $(COMPILER_DIR)/$(COMPILER_PREFIX)g++
AR	                := $(COMPILER_DIR)/$(COMPILER_PREFIX)ar
LD               	:= $(COMPILER_DIR)/$(COMPILER_PREFIX)ld


TARGET := servicemanager

SRCDIR := ./


OBJDIR := $(PROJECT_DIR)/out/framework/services/servicemanager/obj
#LIBDIR := $(PROJECT_DIR)/out/framework/services/servicemanagerr/lib
BINDIR := $(PROJECT_DIR)/out/framework/services/servicemanager/bin


CFLAGS  :=  -fPIC
CFLAGS  += -DHAVE_PTHREADS
CFLAGS  += -DHAVE_SYS_UIO_H
CFLAGS  += -DHAVE_ENDIAN_H
CFLAGS  += -DHAVE_ANDROID_OS=1

LIBS := \
	-llog \

LIBDIRS := \
	-L ../../../out/libs/liblog/lib \
	
INCPATHS := \
	-I . \
	-I ../../../libs/include/ \

SOURCES := \
	service_manager.c \
	binder.c \


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
