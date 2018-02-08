
COMPILER_DIR := /opt/EmbedSky/4.4.6/bin
PROJECT_DIR         := ../..


COMPILER_PREFIX     := arm-linux-
CC                  := $(COMPILER_DIR)/$(COMPILER_PREFIX)gcc
CXX                 := $(COMPILER_DIR)/$(COMPILER_PREFIX)g++
AR	                := $(COMPILER_DIR)/$(COMPILER_PREFIX)ar
LD               	:= $(COMPILER_DIR)/$(COMPILER_PREFIX)ld


TARGET := libdebugger.so


OBJDIR := $(PROJECT_DIR)/out/libs/debugger/obj
LIBDIR := $(PROJECT_DIR)/out/libs/debugger/lib



CFLAGS  :=  -fPIC
CFLAGS  += -DHAVE_PTHREADS
CFLAGS  += -DHAVE_SYS_UIO_H
CFLAGS  += -DHAVE_ENDIAN_H
CFLAGS  += -DHAVE_ANDROID_OS=1
CFLAGS  += -DHAVE_LINUX_LOCAL_SOCKET_NAMESPACE


LIBS := \

LIBDIRS := \


INCPATHS := \
	-I ./inc \
	-I ../../../libs/include/ \

SRCDIR := ./src

SOURCES := \
	debugger.cpp

OBJECTS := $(addprefix $(OBJDIR)/, $(SOURCES:.cpp=.o))

#$(AR)  -rcs $(LIBDIR)/$(TARGET) $(OBJECTS)
$(LIBDIR)/$(TARGET): $(OBJECTS)
	@-mkdir -p $(LIBDIR) 2> /dev/null
	$(CXX) -shared $^ -o $@
	
$(OBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@-mkdir -p $(OBJDIR) 2> /dev/null
	$(CXX) -c $(CFLAGS) $(INCPATHS) -o $@  $<

all: $(OBJECTS) $(LIBDIR)/$(TARGET)

clean:
	rm -f $(OBJECTS) $(LIBDIR)/$(TARGET)

