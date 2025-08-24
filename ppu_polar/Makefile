PCC = ppu-gcc -m64

ppu_polar: ppu_polar.c
	$(PCC) $^ -o $@ -lmassv_64

.PHONY: clean

clean:
	rm -fv ppu_polar

