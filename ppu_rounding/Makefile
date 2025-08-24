PCC = ppu-gcc -m64

ppu_rounding: ppu_rounding.c
	$(PCC) -maltivec $^ -o $@ -lsimdmath

.PHONY: clean

clean:
	rm -fv ppu_rounding

