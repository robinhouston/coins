COINS = (1, 2, 5, 10, 20, 50, 100, 200)
DENOMINATIONS = 5
NUMBER = 100
TARGET = 3975

def quickcoins(coins, denominations, number, target):
    """Yield all the ways of making 'target' from 'number' different coins
    of 'denominations' different denominations drawn from 'coins'.
    """
    if denominations == 1:
        for coin in coins:
            if number > 0 and number * coin == target:
                yield ((number, coin),)
        return
    
    for i, coin in enumerate(coins):
        for n in range(1, min(number, target // coin) + 1):
            for r in quickcoins(coins[i+1:], denominations - 1, number - n, target - n*coin):
                yield ((n, coin,),) + r

for r in quickcoins(COINS, DENOMINATIONS, NUMBER, TARGET):
    print r
