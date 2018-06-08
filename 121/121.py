"""
A bag contains one red disc and one blue disc. In a game of chance a player
takes a disc at random and its colour is noted. After each turn the disc is
returned to the bag, an extra red disc is added, and another disc is taken at
random.

The player pays £1 to play and wins if they have taken more blue discs than red
discs at the end of the game.

If the game is played for four turns, the probability of a player winning is
exactly 11/120, and so the maximum prize fund the banker should allocate for
winning in this game would be £10 before they would expect to incur a loss.
Note that any payout will be a whole number of pounds and also includes the
original £1 paid to play the game, so in the example given the player actually
wins £9.

Find the maximum prize fund that should be allocated to a single game in which
fifteen turns are played.


Solution comment: Very quick, ~0.5 ms (would be much less for C++ impl.).
Derived explicitly the N = 4 case above, from which the pattern emerges.  The
memoization helps a whole bunch. Would have been slightly better to use DP and
build the table directly, but memoizing a recursive solution is so much nicer.
"""

import time
import numpy as np
from functools import lru_cache

def P(n):
    """Probability of drawing a blue in the n-th round."""
    return 1 / (n + 1)

@lru_cache(maxsize=None)
def Prob(blues, n, N):
    """
    Return probability of getting some number of blues, starting on round n,
    with N rounds total.
    """
    if blues <= 0:
        return 1    # Can always get 0 blues.
    elif blues > N - n + 1:
        return 0    # Can never get more blues than draws.
    elif blues == N - n + 1:
        return np.prod(P(np.arange(n, N+1)))  # Prob of getting blue of every draw.
    else:
        # Prob is prob of getting a blue now and then blues-1 on the remaining throws,
        # or prob of getting red now and blues blues on the remaining throws.
        return P(n) * Prob(blues - 1, n + 1, N) + (1-P(n)) * Prob(blues, n + 1, N)

if __name__ == "__main__":
    t0 = time.time()
    rounds = 15
    bet = 1
    winning_prob = Prob(rounds // 2 + 1, 1, rounds)
    print('Execution time: {:.3f} ms'.format((time.time() - t0) * 1e3))
    print('Max payout with {} rounds: {}£'.format(rounds, int(bet / winning_prob)))
