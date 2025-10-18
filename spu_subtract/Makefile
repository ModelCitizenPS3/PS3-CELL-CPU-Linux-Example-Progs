SCC=spu-gcc
SAS=spu-as

spu_subtract: spu_subtract.o
	$(SCC) -g -Wl,-Ttext=0x0 -nostartfiles -o $@ $^

spu_subtract.o: spu_subtract.s
	$(SAS) --gdwarf-2 -o $@ $^

.PHONY: clean

clean:
	rm -fv spu_subtract spu_subtract.o

