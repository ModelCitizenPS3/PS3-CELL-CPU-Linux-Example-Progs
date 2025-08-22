# Declare variables
FILE = a
PCC = ppu-gcc -m64
SCC = spu-gcc
HDIR = ./head_dir

# Tell make to build both applications
all: ppu_$(FILE) spu_$(FILE)

# Build the PPU executable
ppu_$(FILE): $(FILE).c
	$(PCC) -I$(HDIR) $^ -o $@

# Build the SPU executable
spu_$(FILE): $(FILE).c
	$(SCC) -I$(HDIR) $^ -o $@

.PHONY: clean

clean:
	rm -fv ppu_$(FILE) spu_$(FILE)

