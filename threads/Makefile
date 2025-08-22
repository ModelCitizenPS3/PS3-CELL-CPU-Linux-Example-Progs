PCC = ppu-gcc -m64
SCC = spu-gcc
EMBEDSPU=ppu-embedspu -m64

threads: ppu_threads.c spu_threads.o
	$(PCC) $^ -o $@ -lspe2 -lpthread

spu_threads.o: spu_threads.c
	$(SCC) -o spu_threads $^
	$(EMBEDSPU) spu_threads spu_threads $@

.PHONY: clean

clean:
	rm -fv threads spu_threads spu_threads.o

