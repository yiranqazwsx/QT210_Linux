
COMPILER_DIR := /opt/EmbedSky/4.4.6/bin
PROJECT_DIR         := ../..


COMPILER_PREFIX     := arm-linux-
CC                  := $(COMPILER_DIR)/$(COMPILER_PREFIX)gcc
CXX                 := $(COMPILER_DIR)/$(COMPILER_PREFIX)g++
AR	                := $(COMPILER_DIR)/$(COMPILER_PREFIX)ar
LD               	:= $(COMPILER_DIR)/$(COMPILER_PREFIX)ld


TARGET := libmsglooperhandle.so

SRCDIR := ./


OBJDIR := $(PROJECT_DIR)/out/libs/libmsglooperhandle/obj
LIBDIR := $(PROJECT_DIR)/out/libs/libmsglooperhandle/lib
#BINDIR := $(PROJECT_DIR)/out/libs/libmsglooperhandle/bin


CFLAGS  :=  -fPIC
CFLAGS  += -DHAVE_PTHREADS
CFLAGS  += -DHAVE_SYS_UIO_H
CFLAGS  += -DHAVE_ENDIAN_H
CFLAGS  += -DHAVE_ANDROID_OS=1
CFLAGS  += -DHAVE_PRCTL
CFLAGS  += -DHAVE_SCHED_H


LIBS := \
	
LIBDIRS := \

INCPATHS := \
	-I ../include \
	
SOURCES := \
    AAtomizer.cpp                 \
    ABitReader.cpp                \
    ABuffer.cpp                   \
    AHandler.cpp                  \
    AHierarchicalStateMachine.cpp \
    ALooper.cpp                   \
    ALooperRoster.cpp             \
    AMessage.cpp                  \
    AString.cpp                   \
    base64.cpp                    \
    hexdump.cpp 			\




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

