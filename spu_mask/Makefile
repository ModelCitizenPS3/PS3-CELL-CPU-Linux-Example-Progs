SCC=spu-gcc
SAS=spu-as

spu_mask: spu_mask.o
	$(SCC) -g -Wl,-Ttext=0x0 -nostartfiles -o $@ $^

spu_mask.o: spu_mask.s
	$(SAS) --gdwarf-2 -o $@ $^

.PHONY: clean

clean:
	rm -fv spu_mask spu_mask.o

