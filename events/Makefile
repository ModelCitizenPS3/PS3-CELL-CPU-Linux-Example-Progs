PCC = ppu-gcc -m64
SCC = spu-gcc
EMBEDSPU=ppu-embedspu -m64

events: ppu_events.c spu_events.o
	$(PCC) $^ -o $@ -lspe2

spu_events.o: spu_events.c
	$(SCC) -o spu_events $^
	$(EMBEDSPU) spu_events spu_events $@

.PHONY: clean

clean:
	rm -fv events spu_events spu_events.o

