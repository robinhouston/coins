from itertools import combinations

COINS = (1, 2, 5, 10, 20, 50, 100, 200)
TARGET = 3975

def partitions(n, k):
    if k == 1:
        yield (n,)
        return
    for i in range(1, n):
        for p in partitions(n-i, k-1):
            yield (i,) + p

for coin_values in combinations(COINS, 5):
    for counts in partitions(100, 5):
        if sum([ a*b for a,b in zip(coin_values, counts) ]) == TARGET:
            print tuple(zip(counts, coin_values))
