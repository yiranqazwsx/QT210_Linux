COMPILER_DIR := /opt/EmbedSky/4.4.6/bin
PROJECT_DIR         := ../..


COMPILER_PREFIX     := arm-linux-
CC                  := $(COMPILER_DIR)/$(COMPILER_PREFIX)gcc
CXX                 := $(COMPILER_DIR)/$(COMPILER_PREFIX)g++
AR	                := $(COMPILER_DIR)/$(COMPILER_PREFIX)ar
LD               	:= $(COMPILER_DIR)/$(COMPILER_PREFIX)ld

TARGET := logWrite

SRCDIR := ./


OBJDIR := $(PROJECT_DIR)/out/sample/logwrite/obj
BINDIR := $(PROJECT_DIR)/out/sample/logwrite/bin


CFLAGS  :=  -fPIC
CFLAGS  += -DHAVE_PTHREADS
CFLAGS  += -DHAVE_SYS_UIO_H
CFLAGS  += -DHAVE_ENDIAN_H
CFLAGS  += -DHAVE_ANDROID_OS=1

LIBS := \
	-llog \

LIBDIRS := \
	-L ../../out/libs/liblog/lib \
	
INCPATHS := \
	-I . \
	-I ../../libs/include/ \

SOURCES := \
	logWrite.cpp \

CPPOBJECTS := $(addprefix $(OBJDIR)/, $(SOURCES:.cpp=.o))

$(BINDIR)/$(TARGET): $(CPPOBJECTS)
	@-mkdir -p $(BINDIR) 2> /dev/null
	$(CXX) $(LIBDIRS) $(LIBS) $(CPPOBJECTS) -o  $(BINDIR)/$(TARGET) 

$(CPPOBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@-mkdir -p $(OBJDIR) 2> /dev/null
	$(CXX) -c $(CFLAGS) $(INCPATHS) -o $@  $<

all: $(CPPOBJECTS) $(BINDIR)/$(TARGET)

clean:
	rm -f $(CPPOBJECTS) $(BINDIR)/$(TARGET)
