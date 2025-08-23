PCC = ppu-gcc -m64

ppu_divcomp: ppu_divcomp.c
	$(PCC) -maltivec $^ -o $@ -lsimdmath -lmassv_64

.PHONY: clean

clean:
	rm -fv ppu_divcomp

