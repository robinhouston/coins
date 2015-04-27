xtails [] = []
xtails (x:xs) = (x, xs) : xtails xs

count_coins coins 1 number target = map f coins
    where f coin | (number * coin == target) = [(number, coin)]
                 | otherwise = []

count_coins coins denominations number target = concat $ map f $ xtails coins
    where f (coin, other_coins) =
            [ (n, coin) : r
                | n <- [1..(min number (target `div` coin))],
                  r <- count_coins other_coins (denominations-1) (number-n) (target - n*coin) ]

main = mapM_ print $ count_coins [1,2,5,10,20,50,100,200] 5 100 3975
