
COMPILER_DIR := /opt/EmbedSky/4.4.6/bin
PROJECT_DIR         := ../..


COMPILER_PREFIX     := arm-linux-
CC                  := $(COMPILER_DIR)/$(COMPILER_PREFIX)gcc
CXX                 := $(COMPILER_DIR)/$(COMPILER_PREFIX)g++
AR	                := $(COMPILER_DIR)/$(COMPILER_PREFIX)ar
LD               	:= $(COMPILER_DIR)/$(COMPILER_PREFIX)ld


TARGET := libcutils.so

SRCDIR := ./


OBJDIR := $(PROJECT_DIR)/out/libs/libcutils/obj
LIBDIR := $(PROJECT_DIR)/out/libs/libcutils/lib
#BINDIR := $(PROJECT_DIR)/out/libs/libcutils/bin


CFLAGS  :=  -fPIC
CFLAGS  += -DHAVE_PTHREADS
CFLAGS  += -DHAVE_SYS_UIO_H
CFLAGS  += -DHAVE_ENDIAN_H
CFLAGS  += -DHAVE_ANDROID_OS=1
CFLAGS  += -DHAVE_PRCTL
CFLAGS  += -DANDROID_SMP=0
CFLAGS  += -DHAVE_SYS_SOCKET_H
CFLAGS  += -DHAVE_STRLCPY=0
CFLAGS  += -DHAVE_SCHED_H
CFLAGS  += -DHAVE_LINUX_LOCAL_SOCKET_NAMESPACE

LIBS := \
	-lutils \
	-lrt \
	-ldl \
	-lpthread \
	
LIBDIRS := \

INCPATHS := \
	-I ../include \

SOURCES := \
	array.c \
	hashmap.c \
	atomic.c \
	native_handle.c \
	buffer.c \
	socket_inaddr_any_server.c \
	socket_local_client.c \
	socket_local_server.c \
	socket_loopback_client.c \
	socket_loopback_server.c \
	socket_network_client.c \
	sockets.c \
	config_utils.c \
	cpu_info.c \
	load_file.c \
	list.c \
	open_memstream.c \
	strdup16to8.c \
	strdup8to16.c \
	record_stream.c \
	process_name.c \
	properties.c \
	threads.c \
	sched_policy.c \
	iosched_policy.c \
	str_parms.c \
	memory.c \
	ashmem-dev.c \
	partition_utils.c \
	qtaguid.c \
	klog.c \

OBJECTS := $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))


$(LIBDIR)/$(TARGET): $(OBJECTS)
	@-mkdir -p $(LIBDIR) 2> /dev/null
	$(CC) -shared $^ -o $@
	
$(OBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.c
	@-mkdir -p $(OBJDIR) 2> /dev/null
	$(CC) -c $(CFLAGS) $(INCPATHS) -o $@  $<

all: $(OBJECTS) $(LIBDIR)/$(TARGET)

clean:
	rm -f $(OBJECTS) $(LIBDIR)/$(TARGET)

