#include <stdio.h>

/*
    List all the ways to make £39.75 from 100 coins of five different denominations.
*/

#define DENOMINATIONS 5
#define NUMBER 100
#define TARGET 3975

static int all_coins[] = { 200, 100, 50, 20, 10, 5, 2, 1, 0 };

/* A set of coins is represented as an array of type pair[DENOMINATIONS]. */
typedef struct {
    int count;
    int denomination;
} pair;

/* Callback chaining. */
typedef struct {
    int i;
    void (*callback)(pair *, void *);
    void *callback_args;
    int count;
    int denomination;
} chain_args;

void chain(pair *pairs, void *untyped_args) {
    chain_args *args = (chain_args *) untyped_args;
    pairs[args->i].count = args->count;
    pairs[args->i].denomination = args->denomination;
    args->callback(pairs, args->callback_args);
}

/* Print the result in the same format as the Python programs. */
void print(pair *pairs, void *ignored) {
    printf("(");
    for (int i=0; i<DENOMINATIONS; i++) {
        if (i > 0) printf(", ");
        printf("(%d, %d)", pairs[i].count, pairs[i].denomination);
    }
    printf(")\n");
}

/* Find all the ways to make 'target' from 'number' coins of 'denominations'
   different denominations drawn from 'coins'. For each combination found,
   call the 'callback' function with two arguments: an array of pairs,
   and the supplied 'callback_args' pointer.
*/
void quickcoins(int *coins, int denominations, int number, int target,
                void (*callback)(pair *, void *), void *callback_args) {
    int coin;

    if (denominations == 1) {
        pair p[DENOMINATIONS];
        for (int *coinp=coins; (coin=*coinp); coinp++) {
            if (number > 0 && number * coin == target) {
                p[DENOMINATIONS - 1].count = number;
                p[DENOMINATIONS - 1].denomination = coin;
                callback(p, callback_args);
            }
        }
        return;
    }

    chain_args args;
    args.callback = callback;
    args.callback_args = callback_args;
    args.i = DENOMINATIONS - denominations;

    for(int *coinp=coins; (coin=*coinp); coinp++) {
        int max = target / coin;
        if (max > number) max = number;
        args.denomination = coin;
        for(int n=1; n<=max; n++) {
            args.count = n;
            quickcoins(coinp + 1, denominations - 1, number - n, target - n*coin,
                       chain, &args);
        }
    }
}

/* Find and print all the combinations */
int main() {
    quickcoins(all_coins, DENOMINATIONS, NUMBER, TARGET, print, NULL);
}
