PCC = ppu-gcc -m64

ppu_denormal: ppu_denormal.c
	$(PCC) -mabi=altivec -maltivec $^ -o $@

.PHONY: clean

clean:
	rm -fv ppu_denormal

