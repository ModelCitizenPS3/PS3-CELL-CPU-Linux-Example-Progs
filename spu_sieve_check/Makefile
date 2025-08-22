SCC = spu-gcc

spu_sieve_check: spu_sieve_check.c
	$(SCC) -I/opt/ibm/systemsim-cell/include/callthru/spu -o $@ $^

.PHONY: clean

clean:
	rm -fv spu_sieve_check

