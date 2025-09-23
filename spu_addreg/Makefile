SCC=spu-gcc
SAS=spu-as

spu_addreg: spu_addreg.o
	$(SCC) -Wl,-Ttext=0x0 -nostartfiles -o $@ $^

spu_addreg.o: spu_addreg.s
	$(SAS) --gdwarf-2 -o $@ $^

.PHONY: clean

clean:
	rm -fv spu_addreg spu_addreg.o

