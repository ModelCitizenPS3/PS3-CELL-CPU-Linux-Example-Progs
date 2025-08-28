SCC = spu-gcc

spu_intfract: spu_intfract.c
	$(SCC) -o $@ $^ -lsimdmath

.PHONY: clean

clean:
	rm -fv spu_intfract

