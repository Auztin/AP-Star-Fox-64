ASMDIR:= asm
BOOTDIR:= boot
SRCDIR:= src
TOOLSDIR:= tools
ROMDIR:= rom
ASSETSDIR:= assets
SHARED:= ../shared

GAME:=Star_Fox_64
OGROM:=$(ROMDIR)/$(GAME).z64
PATCHEDROM:=$(ROMDIR)/$(GAME)_Patched.z64
PATCHFILE:=$(ROMDIR)/$(GAME).patch

PATH+=:$(TOOLSDIR)/:$(TOOLSDIR)/mips64/bin/
CC:= mips64-elf-gcc
LD:= mips64-elf-ld
ARMIPS:= armips
ED64ROMCONFIG:= ed64romconfig

CFLAGS:= -O1 -G0 -fno-reorder-blocks -march=vr4300 -mtune=vr4300 -mno-gpopt -mdivide-breaks -mexplicit-relocs -msoft-float
CFLAGS+= -I $(SHARED)/include -I $(SRCDIR) -D NDEBUG
LDFLAGS:= -L .
LDFLAGS+= -L $(TOOLSDIR)/mips64/mips64-elf/lib/soft-float
LDFLAGS+= -L $(TOOLSDIR)/mips64/lib/gcc/mips64-elf/14.2.0/soft-float/
LDLIBS:= -lc -lgcc

ASM:= $(shell find $(ASMDIR)/ -type f -name '*.asm')
BOOTSOURCE:= $(shell find $(BOOTDIR)/ -type f -name '*.c')
BOOTOBJS = $(shell find $(BOOTDIR)/ -type f -name '*.o')
BOOTDEPS = $(shell find $(BOOTDIR)/ -type f -name '*.d')
SOURCE:= $(shell find $(SRCDIR)/ -type f -name '*.c')
OBJS = $(shell find $(SRCDIR)/ -type f -name '*.o')
DEPS = $(shell find $(SRCDIR)/ -type f -name '*.d')
ASSETS:= $(shell find $(ASSETSDIR)/ -type f -name '*' ! -name 'assets.dl')
CLEANUP = $(BOOTOBJS) $(BOOTDEPS) $(OBJS) $(DEPS) $(ASSETSDIR)/assets.dl

$(PATCHEDROM): $(BOOTDIR)/bundle.o $(SRCDIR)/bundle.o $(ASM) $(ASSETSDIR)/assets.dl
	$(ARMIPS) -root $(ASMDIR) -sym2 ../$(ROMDIR)/asm_symbols.txt build.asm\
		-strequ romfile ../$(OGROM) -strequ patchedfile ../$@\
		-strequ bootbundle ../$(word 1,$^) -strequ srcbundle ../$(word 2,$^) -strequ assetsdir ../$(ASSETSDIR)
	python $(TOOLSDIR)/crc.py $@
	$(ED64ROMCONFIG) -w sram256k $@

$(BOOTDIR)/bundle.o: $(patsubst %.c,%.o,$(BOOTSOURCE))
	$(LD) -T $(TOOLSDIR)/linker_script.ld -o $@ -i $(LDFLAGS) $(patsubst %.o,-l:%.o,$^) $(LDLIBS)

$(SRCDIR)/bundle.o: $(patsubst %.c,%.o,$(SOURCE))
	$(LD) -T $(TOOLSDIR)/linker_script.ld -o $@ -i $(LDFLAGS) $(patsubst %.o,-l:%.o,$^) $(LDLIBS)

include $(BOOTDEPS) $(DEPS)

%.o: %.c Makefile
	$(CC) -o $@ -c $< $(CFLAGS) $(CPPFLAGS) -MMD -Werror -Wall -Wextra -Wno-main

$(ASSETSDIR)/assets.dl: $(ASSETS) $(TOOLSDIR)/assets.py
	python $(TOOLSDIR)/assets.py $@ $(ASMDIR)/assets.asm $(shell find $(ASSETSDIR)/ -type f -name '*.obj')

.PHONY: patch
patch: $(PATCHFILE)

$(PATCHFILE): $(PATCHEDROM)
	python $(TOOLSDIR)/patch.py $(OGROM) $(PATCHEDROM) $(PATCHFILE)

.PHONY: clean
clean:
	$(RM) $(CLEANUP)
