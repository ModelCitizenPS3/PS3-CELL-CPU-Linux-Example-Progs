PCC = ppu-gcc -m64

ppu_massv: ppu_massv.c
	$(PCC) $^ -o $@ -lmassv_64

.PHONY: clean

clean:
	rm -fv ppu_massv

