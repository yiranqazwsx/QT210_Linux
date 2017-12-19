COMPILER_DIR := /opt/EmbedSky/4.4.6/bin
PROJECT_DIR         := ../..

COMPILER_PREFIX     := arm-linux-
CC  := $(COMPILER_DIR)/$(COMPILER_PREFIX)gcc
CXX := $(COMPILER_DIR)/$(COMPILER_PREFIX)c++
AR  := $(COMPILER_DIR)/$(COMPILER_PREFIX)ar
LD  := $(COMPILER_DIR)/$(COMPILER_PREFIX)ld





OBJDIR :=$(PROJECT_DIR)/out/libs/liblog/obj
LIBDIR := $(PROJECT_DIR)/out/libs/liblog/lib
#BINDIR := $(PROJECT_DIR)/out/libs/log/bin
SRCDIR := ./


#CFLAGS := --sysroot=$(SYSROOT)
CFLAGS := -fPIC
CFLAGS += -I ../include

CFLAGS += -DHAVE_PTHREADS  -DHAVE_IOCTL -DHAVE_ANDROID_OS=1 
CFLAGS += -DLIBLOG_LOG_TAG=1005
CFLAGS += -DHAVE_SYS_UIO_H



CSOURCES := \
	logd_write.c \
	event_tag_map.c \
	logprint.c \



CppSOURCES := \



COBJECTS := $(addprefix $(OBJDIR)/, $(CSOURCES:.c=.o))
CppOBJECTS := $(addprefix $(OBJDIR)/, $(CppSOURCES:.cpp=.o))


TARGET := liblog.so


$(LIBDIR)/$(TARGET): $(COBJECTS)  $(CppOBJECTS)
	@-mkdir -p $(LIBDIR) 2> /dev/null
	$(LD) -shared $^ -o $@      
	#$(AR)  -rcs $@ $^

$(COBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.c
	@-mkdir -p $(OBJDIR) 2> /dev/null
	$(CC) -c $(CFLAGS)   $(INCPATHS) -o $@  $<
	
$(CppOBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@-mkdir -p $(OBJDIR) 2> /dev/null
	$(CXX) -c $(CFLAGS) -std=c++11 $(INCPATHS) -o $@  $<

clean:
	rm -f $(COBJECTS) $(CppOBJECTS)  $(LIBDIR)/$(TARGET)




