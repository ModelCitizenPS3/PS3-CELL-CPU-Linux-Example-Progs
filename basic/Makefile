PCC = ppu-gcc -m64
SCC = spu-gcc
EMBEDSPU = ppu-embedspu -m64

basic: ppu_basic.c spu_basic.o
	$(PCC) $^ -o $@ -lspe2

spu_basic.o: spu_basic.c
	$(SCC) -o spu_basic $^
	$(EMBEDSPU) spu_basic spu_basic $@

.PHONY: clean

clean:
	rm -fv basic spu_basic spu_basic.o

