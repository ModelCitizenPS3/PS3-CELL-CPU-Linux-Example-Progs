FILE = a
HDIR = ./head_dir

PCPP=ppu-cpp
PCC = ppu-gcc -m64
PAS=ppu-as
PLD=ppu-ld

$(FILE): $(FILE).o /usr/lib64/crt1.o /usr/lib64/crti.o /usr/lib64/crtn.o
	$(PLD) $^ -dynamic-linker /lib64/ld64.so.1 -o $@ -lc

$(FILE).o: $(FILE).s
	$(PAS) $^ -o $@

$(FILE).s: $(FILE).i
	$(PCC) -S $^ -o $@

$(FILE).i: $(FILE).c
	$(PCPP) -I$(HDIR) $^ -o $@

.PHONY: clean

clean:
	rm -fv $(FILE).i $(FILE).s $(FILE).o $(FILE)
