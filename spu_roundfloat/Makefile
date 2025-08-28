SCC = spu-gcc

spu_roundfloat: spu_roundfloat.c
	$(SCC) -o $@ $^ -lsimdmath

.PHONY: clean

clean:
	rm -fv spu_roundfloat

