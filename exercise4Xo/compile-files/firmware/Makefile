# Makefile

RISCV_GNU_TOOLCHAIN_GIT_REVISION = 411d134
RISCV_GNU_TOOLCHAIN_INSTALL_PREFIX = /opt/riscv32
TOOLCHAIN_PREFIX = $(RISCV_GNU_TOOLCHAIN_INSTALL_PREFIX)/bin/riscv32-unknown-elf-

PYTHON = /usr/bin/python3

# FIRMWARE_OBJS = firmware/start.o firmware/irq.o firmware/print.o firmware/hello.o firmware/sieve.o firmware/multest.o firmware/stats.o

# TEST_OBJS = $(addsuffix .o,$(basename $(wildcard *.c)))

# GCC_WARNS  = -Werror -Wall -Wextra -Wshadow -Wundef -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings
# GCC_WARNS += -Wredundant-decls -Wstrict-prototypes -Wmissing-prototypes -pedantic # -Wconversion
GCC_ARGS = -mcmodel=medlow

COMPRESSED_ISA = 

CC      = /usr/bin/gcc
CFLAGS  = -Wall -pg
LDFLAGS = #-pg -g

BUILDDIR = build
SOURCEDIR = src
HEADERDIR = src
TOOLS = tools

SOURCES = $(wildcard $(SOURCEDIR)/*.c)
SOURCES_A = $(wildcard $(SOURCEDIR)/*.S)
OBJECTS = $(patsubst $(SOURCEDIR)/%.c, $(BUILDDIR)/%.o, $(SOURCES))
OBJECTS_A = $(patsubst $(SOURCEDIR)/%.S, $(BUILDDIR)/%.o, $(SOURCES_A))

BINARY = firmware.elf

RM = rm -rf
MKDIR = mkdir

.PHONY: all clean sizes setup

################################################################################

all: firmware.hex firmware.objdump

################################################################################

%.objdump: %.elf
	$(TOOLCHAIN_PREFIX)objdump -D $< > $@

%.bin: %.elf
	$(TOOLCHAIN_PREFIX)objcopy -O binary $< $@

%.hex: %.bin
	$(PYTHON) $(TOOLS)/makehex.py $^ 2048 > $@

# LINKING ######################################################################
$(BINARY): $(OBJECTS) $(OBJECTS_A)
	$(TOOLCHAIN_PREFIX)gcc -Os -ffreestanding -nostdlib -o $@ $^ $(GCC_ARGS) --std=gnu99 -Wl,-Bstatic,-T,firmware.lds,-Map,firmware.map,--strip-debug -lgcc

# COMPILING ####################################################################
$(BUILDDIR)/%.o: $(SOURCEDIR)/%.c
	$(TOOLCHAIN_PREFIX)gcc -c -march=rv32i$(subst C,c,$(COMPRESSED_ISA)) -Os --std=c99 $(GCC_WARNS) -ffreestanding -nostdlib -o $@ $<

# MAIN STRUCTURE
$(BUILDDIR)/start.o: $(SOURCEDIR)/start.S
	$(TOOLCHAIN_PREFIX)gcc -c -march=rv32im$(subst C,c,$(COMPRESSED_ISA)) -o $@ $<


################################################################################

sizes: firmware.elf
	$(TOOLCHAIN_PREFIX)size $^

setup:
	$(MKDIR) -p $(BUILDDIR)

clean:
	$(RM) firmware*.elf firmware*.bin firmware*.hex firmware*.map firmware*.objdump
	$(RM) $(BINARY) $(OBJECTS) $(OBJECTS_A)
