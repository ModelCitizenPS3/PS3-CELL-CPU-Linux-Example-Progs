PCC = ppu-gcc -m64

ppu_load: ppu_load.c
	$(PCC) -maltivec $^ -o $@

.PHONY: clean

clean:
	rm -fv ppu_load

