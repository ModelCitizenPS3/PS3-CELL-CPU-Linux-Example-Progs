PCC = ppu-gcc -m64

ppu_shiftadd: ppu_shiftadd.c
	$(PCC) -maltivec $^ -o $@

.PHONY: clean

clean:
	rm -fv ppu_shiftadd

