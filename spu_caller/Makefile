SCC=spu-gcc

spu_func: spu_caller.o spu_func.o
	$(SCC) -Wl,-Ttext=0x0 -nostartfiles $^ -o $@

spu_caller.o: spu_caller.s
	$(SCC) -c $^ -o $@

spu_func.o: spu_func.c
	$(SCC) -c $^ -o $@

.PHONY: clean

clean:
	rm -fv spu_func spu_caller.o spu_func.o

