PROJECTNAME := ilmattoraytracer

CC := avr-gcc
OC := avr-objcopy
REMOVE := rm -f

MMCU := atmega644p
DF_CPU := 12000000

SRCDIR := src
OUTDIR := build

FLAGS := -mmcu=$(MMCU) -DF_CPU=$(DF_CPU) -O2 -lm
OCFLAGS := -O ihex

OBJS := $(patsubst $(SRCDIR)/%.c,$(OUTDIR)/%.o,$(wildcard $(SRCDIR)/*.c)) $(OUTDIR)/liblcd.a
OUT := $(OUTDIR)/$(PROJECTNAME)

all: $(OUT).hex

$(OUT).hex: $(OBJS)
	$(CC) $(FLAGS) -o $(OUT).elf $(OBJS)
	$(OC) $(OCFLAGS) $(OUT).elf $(OUT).hex

.SECONDEXPANSION:
$(OUTDIR)/%.o: $(SRCDIR)/%.c $$(wildcard $$(SRCDIR)/%.h)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(REMOVE) $(OBJS) $(OUT).elf $(OUT).hex