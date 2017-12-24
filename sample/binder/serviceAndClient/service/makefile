
COMPILER_DIR := /opt/EmbedSky/4.4.6/bin
PROJECT_DIR         := ../../../..


COMPILER_PREFIX     := arm-linux-
CC                  := $(COMPILER_DIR)/$(COMPILER_PREFIX)gcc
CXX                 := $(COMPILER_DIR)/$(COMPILER_PREFIX)g++
AR	                := $(COMPILER_DIR)/$(COMPILER_PREFIX)ar
LD               	:= $(COMPILER_DIR)/$(COMPILER_PREFIX)ld


TARGET := ServiceTest

SRCDIR := ./


OBJDIR := $(PROJECT_DIR)/out/sample/binder/serviceAndClient/client/obj
#LIBDIR := $(PROJECT_DIR)/out/sample/binder/serviceAndClient/client/lib
BINDIR := $(PROJECT_DIR)/out/sample/binder/serviceAndClient/client/bin


CFLAGS  :=  -fPIC
CFLAGS  += -DHAVE_PTHREADS
CFLAGS  += -DHAVE_SYS_UIO_H
CFLAGS  += -DHAVE_ENDIAN_H
CFLAGS  += -DHAVE_ANDROID_OS=1


LIBS := \
	-lcutils \
	-lutils \
	-lbinder \
	-llog \
	-lpthread \
	
LIBDIRS := \
	-L ../../../../out/libs/libbinder/lib \
	-L ../../../../out/libs/libutils/lib \
	-L ../../../../out/libs/libcutils/lib \
	-L ../../../../out/libs/liblog/lib \


INCPATHS := \
	-I ../../../../libs/include/ \

SOURCES := \
    ServiceTest.cpp \


OBJECTS := $(addprefix $(OBJDIR)/, $(SOURCES:.cpp=.o))

#$(AR)  -rcs $(LIBDIR)/$(TARGET) $(OBJECTS)
#$(LD) -shared $^ -o $@
$(BINDIR)/$(TARGET): $(OBJECTS)
	@-mkdir -p $(BINDIR) 2> /dev/null
	$(CXX)  $^ $(LIBDIRS) $(LIBS) -o $@
	
$(OBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@-mkdir -p $(OBJDIR) 2> /dev/null
	$(CXX) -c $(CFLAGS) $(INCPATHS) -o $@  $<

all: $(OBJECTS) $(BINDIR)/$(TARGET)

clean:
	rm -f $(OBJECTS) $(BINDIR)/$(TARGET)

