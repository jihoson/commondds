.PHONY: clean all COMMONDDS_HOME
VPATH = src:src/idl

CXX 	:= g++
INCS 	:= 	-Iinclude \
			-Isrc/idl \
			-I$(OSPL_HOME)/include \
			-I$(OSPL_HOME)/include/sys \
			-I$(OSPL_HOME)/include/dcps/C++/SACPP
TYPE_CXXFLAGS := -fPIC -O3 -DNDEBUG -D_REENTRANT -Wall -DOSPL_BUILDEXAMPLE_LIB $(INCS)
BIN_CXXFLAGS := -fPIC -O3 -DNDEBUG -Wall $(INCS)

OBJDIR := obj

TYPE_OBJS := $(OBJDIR)/Hello.o	\
			 $(OBJDIR)/HelloDcps.o \
			 $(OBJDIR)/HelloDcps_impl.o \
			 $(OBJDIR)/HelloSplDcps.o

BIN_OBJS  := $(OBJDIR)/CheckStatus.o \
			 $(OBJDIR)/pub.o \
			 $(OBJDIR)/sub.o

LDFLAGS 	:=	-Wl,-rpath,. \
				-Wl,-rpath,$(OSPL_HOME)/lib
OSPL_LIBS 	:= -l"dcpssacpp" -l"ddskernel"
SYSLIBS   	:= -ldl -lpthread
LIBS 		:= -L"." -L$(OSPL_HOME)/lib $(OSPL_LIBS) $(SYSLIBS)

TARGET_TYPE := libsacpp_helloworld_types.so
TARGET_PUB  := pub
TARGET_SUB  := sub

GENERATED := src/idl/Hello.h

all: $(GENERATED) $(TARGET_TYPE) $(TARGET_PUB) $(TARGET_SUB)

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(TYPE_CXXFLAGS) -c -o $@ $<

generate : src/Hello.idl
	@mkdir -p obj
	@mkdir -p src/idl
	$(OSPL_HOME)/bin/idlpp -d src/idl -l c++ src/Hello.idl

$(GENERATED): src/Hello.idl
	@mkdir -p obj
	@mkdir -p src/idl
	$(OSPL_HOME)/bin/idlpp -d src/idl -l c++ src/Hello.idl
	@make # Generated code that using idlpp does not belong to the current VPATH of Make. so, recall it

$(TARGET_TYPE): $(TYPE_OBJS)
	$(CXX) $(TYPE_CXXFLAGS) $(LDFLAGS) -shared -o $@ $^ $(LIBs)

$(TARGET_PUB): $(TARGET_TYPE) $(BIN_OBJS)
	$(CXX) $(BIN_CXXFLAGS) $(LDFLAGS) -o $@ $(filter-out $(OBJDIR)/sub.o $(TARGET_TYPE),$^) $(LIBS) $(TARGET_TYPE)

$(TARGET_SUB): $(TARGET_TYPE) $(BIN_OBJS)
	$(CXX) $(BIN_CXXFLAGS) $(LDFLAGS) -o $@ $(filter-out $(OBJDIR)/pub.o $(TARGET_TYPE),$^) $(LIBS) $(TARGET_TYPE)

clean:
	@rm -rf src/idl
	@rm -rf $(TARGET_TYPE) $(TARGET_PUB) $(TARGET_SUB) $(OBJDIR)
	@rm -rf `find -name "*.log"`

