SCC=spu-gcc
SAS=spu-as

spu_shright: spu_shright.o
	$(SCC) -Wl,-Ttext=0x0 -nostartfiles -o $@ $^

spu_shright.o: spu_shright.s
	$(SAS) --gdwarf-2 -o $@ $^

.PHONY: clean

clean:
	rm -fv spu_shright spu_shright.o

