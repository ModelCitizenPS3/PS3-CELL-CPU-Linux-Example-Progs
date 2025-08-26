SCC = spu-gcc

spu_dectest: spu_dectest.c
	$(SCC) -O3 -o $@ $^ -lsimdmath -lmassv

.PHONY: clean

clean:
	rm -fv spu_dectest

