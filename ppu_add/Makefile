PCC = ppu-gcc -m64

ppu_add: ppu_add.c
	$(PCC) -maltivec $^ -o $@

.PHONY: clean

clean:
	rm -fv ppu_add

