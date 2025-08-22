PCC = ppu-gcc -m64

double_dot: double_dot.c
	$(PCC) -o $@ $^ -lpthread

.PHONY: clean

clean:
	rm -fv double_dot

