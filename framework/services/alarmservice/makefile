COMPILER_DIR := /opt/EmbedSky/4.4.6/bin
PROJECT_DIR         := ../../..


COMPILER_PREFIX     := arm-linux-
CC                  := $(COMPILER_DIR)/$(COMPILER_PREFIX)gcc
CXX                 := $(COMPILER_DIR)/$(COMPILER_PREFIX)g++
AR	                := $(COMPILER_DIR)/$(COMPILER_PREFIX)ar
LD               	:= $(COMPILER_DIR)/$(COMPILER_PREFIX)ld

TARGET := alarmservice

SRCDIR := ./src


OBJDIR := $(PROJECT_DIR)/out/framework/services/alarmservice/obj
BINDIR := $(PROJECT_DIR)/out/framework/services/alarmservice/bin


CFLAGS  :=  -fPIC
CFLAGS  += -DHAVE_PTHREADS
CFLAGS  += -DHAVE_SYS_UIO_H
CFLAGS  += -DHAVE_ENDIAN_H
CFLAGS  += -DHAVE_ANDROID_OS=1

LIBS := \
	-llog \
	-lbinder \
	-lutils \
	-lcutils \
	-lpthread \
	-lalarmmanager \
		
LIBDIRS := \
	-L ../../../out/libs/liblog/lib \
	-L ../../../out/libs/libbinder/lib \
	-L ../../../out/libs/libutils/lib \
	-L ../../../out/libs/libcutils/lib \
	-L ../../../out/framework/managers/alarmmanager/lib/
	
INCPATHS := \
	-I ./inc \
	-I ../../managers/alarmmanager/inc/ \
	-I ../../../libs/include/ \

SOURCES := \
	AlarmService.cpp \
	main.cpp \

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

