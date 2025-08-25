PCC = ppu-gcc -m64

vecsort: vecsort.c
	$(PCC) -maltivec $^ -o $@

.PHONY: clean

clean:
	rm -fv vecsort

