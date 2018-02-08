COMPILER_DIR := /opt/EmbedSky/4.4.6/bin
PROJECT_DIR         := ../..


COMPILER_PREFIX     := arm-linux-
CC                  := $(COMPILER_DIR)/$(COMPILER_PREFIX)gcc
CXX                 := $(COMPILER_DIR)/$(COMPILER_PREFIX)g++
AR	                := $(COMPILER_DIR)/$(COMPILER_PREFIX)ar
LD               	:= $(COMPILER_DIR)/$(COMPILER_PREFIX)ld


TARGET := debugger

SRCDIR := ./src


OBJDIR := $(PROJECT_DIR)/out/sample/debugger/obj
#LIBDIR := $(PROJECT_DIR)/out/sample/debugger/lib
BINDIR := $(PROJECT_DIR)/out/sample/debugger/bin


CFLAGS  :=  -fPIC
CFLAGS  += -DHAVE_PTHREADS
CFLAGS  += -DHAVE_SYS_UIO_H
CFLAGS  += -DHAVE_ENDIAN_H
CFLAGS  += -DHAVE_ANDROID_OS=1
CFLAGS  += -DHAVE_IOCTL
CFLAGS  += -g
CFLAGS  += -rdynamic 

LIBS := \
	-llog \
	-lbinder \
	-lutils \
	-lcutils \
	-lpthread \
	-ldebugger\

LIBDIRS := \
	-L ../../out/libs/liblog/lib \
	-L ../../out/libs/libbinder/lib \
	-L ../../out/libs/libutils/lib \
	-L ../../out/libs/libcutils/lib \
	-L ../../out/libs/debugger/lib \
	
INCPATHS := \
	-I ./inc/ \
	-I ../../libs/include/ \
	-I ../../libs/debugger/inc \
	
SOURCES := \
	main.cpp \

OBJECTS := $(addprefix $(OBJDIR)/, $(SOURCES:.cpp=.o))

$(BINDIR)/$(TARGET): $(OBJECTS)
	@-mkdir -p $(BINDIR) 2> /dev/null
#	$(AR)  -rcs $(BINDIR)/$(TARGET) $(OBJECTS)
	$(CXX) $(LIBDIRS) $(LIBS) $(OBJECTS) -o  $(BINDIR)/$(TARGET) 

$(OBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@-mkdir -p $(OBJDIR) 2> /dev/null
	$(CXX) -c $(CFLAGS) $(INCPATHS) -o $@  $<

all: $(OBJECTS) $(BINDIR)/$(TARGET)

clean:
	rm -f $(OBJECTS) $(BINDIR)/$(TARGET)

