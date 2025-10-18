SCC=spu-gcc
SAS=spu-as

spu_caller: spu_caller.c spu_func.o
	$(SCC) -g -o $@ $^

spu_func.o: spu_func.s
	$(SAS) --gdwarf-2 -o $@ $^

.PHONY: clean

clean:
	rm -fv spu_caller spu_func.o

