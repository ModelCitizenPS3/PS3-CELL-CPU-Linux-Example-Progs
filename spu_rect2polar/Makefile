SCC = spu-gcc

spu_rect2polar: spu_rect2polar.c
	$(SCC) -o $@ $^ -lmassv

.PHONY: clean

clean:
	rm -fv spu_rect2polar

