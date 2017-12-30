COMPILER_DIR := /opt/EmbedSky/4.4.6/bin
PROJECT_DIR         := ../..


COMPILER_PREFIX     := arm-linux-
CC                  := $(COMPILER_DIR)/$(COMPILER_PREFIX)gcc
CXX                 := $(COMPILER_DIR)/$(COMPILER_PREFIX)g++
AR	                := $(COMPILER_DIR)/$(COMPILER_PREFIX)ar
LD               	:= $(COMPILER_DIR)/$(COMPILER_PREFIX)ld


TARGET := logcat

SRCDIR := ./


OBJDIR := $(PROJECT_DIR)/out/application/logcat/obj
#LIBDIR := $(PROJECT_DIR)/out/application/logcat/lib
BINDIR := $(PROJECT_DIR)/out/application/logcat/bin


CFLAGS  :=  -fPIC
CFLAGS  += -DHAVE_PTHREADS
CFLAGS  += -DHAVE_SYS_UIO_H
CFLAGS  += -DHAVE_ENDIAN_H
CFLAGS  += -DHAVE_ANDROID_OS=1
CFLAGS  += -DHAVE_IOCTL

LIBS := \
	-llog \

LIBDIRS := \
	-L ../../out/libs/liblog/lib \
	
INCPATHS := \
	-I . \
	-I ../../libs/include/ \
	

SOURCES := \
	logcat.cpp \



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
