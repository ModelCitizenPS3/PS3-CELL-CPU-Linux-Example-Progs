PCC = ppu-gcc -m64
SCC = spu-gcc
EMBEDSPU = ppu-embedspu -m64

dmabasic: ppu_dmabasic.c spu_dmabasic.o
	$(PCC) $^ -o $@ -lspe2

spu_dmabasic.o: spu_dmabasic.c
	$(SCC) -o spu_dmabasic $^
	$(EMBEDSPU) spu_dmabasic spu_dmabasic $@

.PHONY: clean

clean:
	rm -fv dmabasic spu_dmabasic spu_dmabasic.o

