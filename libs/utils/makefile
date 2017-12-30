
COMPILER_DIR := /opt/EmbedSky/4.4.6/bin
PROJECT_DIR         := ../..


COMPILER_PREFIX     := arm-linux-
CC                  := $(COMPILER_DIR)/$(COMPILER_PREFIX)gcc
CXX                 := $(COMPILER_DIR)/$(COMPILER_PREFIX)g++
AR	                := $(COMPILER_DIR)/$(COMPILER_PREFIX)ar
LD               	:= $(COMPILER_DIR)/$(COMPILER_PREFIX)ld


TARGET := libutils.so

SRCDIR := ./


OBJDIR := $(PROJECT_DIR)/out/libs/libutils/obj
LIBDIR := $(PROJECT_DIR)/out/libs/libutils/lib
#BINDIR := $(PROJECT_DIR)/out/libs/libutils/bin


CFLAGS  :=  -fPIC
CFLAGS  += -DHAVE_PTHREADS
CFLAGS  += -DHAVE_SYS_UIO_H
CFLAGS  += -DHAVE_ENDIAN_H
CFLAGS  += -DHAVE_ANDROID_OS=1
CFLAGS  += -DHAVE_PRCTL
CFLAGS  += -DHAVE_SCHED_H


LIBS := \
	-lcutils \
	-lrt \
	-ldl \
	-lpthread \
	
LIBDIRS := \

INCPATHS := \
	-I ../include \

SOURCES := \
    RefBase.cpp \
    String8.cpp \
    String16.cpp \
    StringArray.cpp \
    VectorImpl.cpp \
    Threads.cpp \
    Unicode.cpp \
    Static.cpp \
    BufferedTextOutput.cpp \
    TextOutput.cpp \
    Timers.cpp \
    SharedBuffer.cpp \
    Debug.cpp \
    SystemClock.cpp \


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

