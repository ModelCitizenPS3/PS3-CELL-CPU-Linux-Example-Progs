PCC = ppu-gcc -m64

ppu_permtest: ppu_permtest.c
	$(PCC) -maltivec $^ -o $@

.PHONY: clean

clean:
	rm -fv ppu_permtest

