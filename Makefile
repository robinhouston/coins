run: coins
	@./coins

.PHONY: run

coins: coins.c
	gcc --std=c99 -O3 -o $@ $<

hscoins: coins.hs
	ghc --make "$<" -o "$@"
