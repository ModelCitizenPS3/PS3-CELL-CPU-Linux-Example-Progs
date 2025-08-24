PCC = ppu-gcc -m64

ppu_swizzle: ppu_swizzle.c
	$(PCC) -maltivec $^ -o $@

.PHONY: clean

clean:
	rm -fv ppu_swizzle

