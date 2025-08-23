PCC = ppu-gcc -m64

ppu_union: ppu_union.c
	$(PCC) -mabi=altivec -maltivec $^ -o $@

.PHONY: clean

clean:
	rm -fv ppu_union

