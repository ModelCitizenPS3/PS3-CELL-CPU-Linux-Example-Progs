SCC = spu-gcc

spu_heaptest: spu_heaptest.c
	$(SCC) -I/opt/cell/sdk/usr/spu/include -L/opt/cell/sdk/usr/spu/lib -o $@ $^ -lmisc

.PHONY: clean

clean:
	rm -fv spu_heaptest

