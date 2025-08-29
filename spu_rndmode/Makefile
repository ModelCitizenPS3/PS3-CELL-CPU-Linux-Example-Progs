SCC = spu-gcc

spu_rndmode: spu_rndmode.c
	$(SCC) -o $@ $^ -lsimdmath

.PHONY: clean

clean:
	rm -fv spu_rndmode

