SRCDIR:= src
SHARED:= ../shared
TARGET:= EverDrive64
CXXFLAGS:= -I include
CXXFLAGS+= -std=c++20 -O3
LDFLAGS := -L lib/vcp-driver/amd64 -L lib/vcp-driver/i386
LDFLAGS += -l ftd2xx
PLATFORM:= unknown
BUILD:= $(MAKE) --no-print-directory -f MakeBuild.mk -j

SOURCE:= $(shell find $(SRCDIR)/ -type f -name '*.cpp')
OBJS = $(shell find $(SRCDIR)/ -type f -name '*.o')
DEPS = $(shell find $(SRCDIR)/ -type f -name '*.d')
CLEANUP = $(TARGET) $(TARGET).exe $(OBJS) $(DEPS)
export

.PHONY: all
all: linux windows

linux:
	@$(MAKE) --no-print-directory -f MakeLinux.mk

windows:
	@$(MAKE) --no-print-directory -f MakeWindows.mk

.PHONY: clean
clean:
	$(RM) $(CLEANUP)
