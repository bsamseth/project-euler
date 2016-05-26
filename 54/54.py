# coding=utf-8
"""
In the card game poker, a hand consists of five cards and are ranked, from
lowest to highest, in the following way:

High Card: Highest value card.
One Pair: Two cards of the same value.
Two Pairs: Two different pairs.
Three of a Kind: Three cards of the same value.
Straight: All cards are consecutive values.
Flush: All cards of the same suit.
Full House: Three of a kind and a pair.
Four of a Kind: Four cards of the same value.
Straight Flush: All cards are consecutive values of same suit.
Royal Flush: Ten, Jack, Queen, King, Ace, in same suit.

The cards are valued in the order:
2, 3, 4, 5, 6, 7, 8, 9, 10, Jack, Queen, King, Ace.

If two players have the same ranked hands then the rank made up of the highest
value wins; for example, a pair of eights beats a pair of fives. But if two ranks
tie, for example, both players have a pair of queens, then highest cards in each
hand are compared (see example 4 below); if the highest cards tie then the next
highest cards are compared, and so on.

The file, poker.txt, contains one-thousand random hands dealt to two players.
Each line of the file contains ten cards (separated by a single space): the first
five are Player 1's cards and the last five are Player 2's cards. You can assume
that all hands are valid (no invalid characters or repeated cards), each player's
hand is in no specific order, and in each hand there is a clear winner.

How many hands does Player 1 win?

Solution comment:
Not my solution, but a very nifty one. I have built a litlle around it, just
to have some object oriented stuff. Encodes a hand in a list, structred so that
Pythons list comparison always gives the right result when comapring the hands.
"""

from collections import Counter
from functools import total_ordering
from enum import IntEnum, unique


@unique
class Quality(IntEnum):
    """Quality of a poker hand. Higher values beat lower values."""
    high_card = 1
    pair = 2
    two_pairs = 3
    three = 4
    straight = 5
    flush = 6
    full_house = 7
    four = 8
    straight_flush = 9

@total_ordering
class Hand:
    """Class to represent a poker hand. Initialization is done with
    a string like '5H TC 7S KH AD'. Objects can be converted to strings,
    in which case they are the (alphabeticaly) sorted version of the input.
    Objects can be compared, using any comparison operator.
    """
    def __init__(self, string):
        self.string = ' '.join(sorted(string.upper().split()))
        self.rep = self.canonical(self.string.split())

    def __str__(self):
        return self.string

    def __eq__(self, other):
        return self.rep == other.rep

    def __gt__(self, other):
        return self.rep > other.rep

    def canonical(self, hand):
        """Return the canonical form of the poker hand as a pair (q, r) where
        q is a value from the Quality enumeration, and r is a list of the
        distinct card ranks in the hand (from 1=low ace to 14=high ace),
        ordered in descreasing order by frequency and then by rank. These
        canonical forms can be compared to see who wins. The hand must be
        a sequence of five cards given as two-character strings in the
        form 2H, TS, JC etc.

        >>> canonical('TD 7H KH TS 7S'.split()) # two pairs (tens and sevens)
        (<Quality.two_pairs: 3>, [10, 7, 13])
        >>> canonical('3C AH 4D 2S 5C'.split()) # ace-low straight
        (<Quality.straight: 5>, [5, 4, 3, 2, 1])
        >>> canonical('JH 2H JC JS 2D'.split()) # full house (twos and jacks)
        (<Quality.full_house: 7>, [11, 2])
        >>> canonical('TS 4S 8S QS 5S'.split()) # queen-high flush
        (<Quality.flush: 6>, [12, 10, 8, 5, 4])

        """
        flush = len(set(suit for _, suit in hand)) == 1
        ranks = sorted('--23456789TJQKA'.find(rank) for rank, _ in hand)
        if ranks == [2, 3, 4, 5, 14]:  # ace-low straight
            ranks = [1, 2, 3, 4, 5]
        straight = ranks == list(range(ranks[0], ranks[0] + 5))
        count = Counter(ranks)
        counts = sorted(count.values())
        distinct_ranks = sorted(count, reverse=True, key=lambda v: (count[v], v))
        if flush and straight:
            q = Quality.straight_flush
        elif counts == [1, 4]:
            q = Quality.four
        elif counts == [2, 3]:
            q = Quality.full_house
        elif flush:
            q = Quality.flush
        elif straight:
            q = Quality.straight
        elif counts == [1, 1, 3]:
            q = Quality.three
        elif counts == [1, 2, 2]:
            q = Quality.two_pairs
        elif counts == [1, 1, 1, 2]:
            q = Quality.pair
        else:
            q = Quality.high_card
        return q, distinct_ranks


if __name__ == '__main__':
    with open('p054_poker.txt', 'r') as f:
        hands = f.readlines()

    total = 0
    for line in hands:
        cards = line.split()
        p1 = Hand(' '.join(cards[:5]))
        p2 = Hand(' '.join(cards[5:]))

        if p1 < p2:
            comp = '<'
        elif p1 == p2:
            comp = '='
        else:
            comp = '>'

        print 'Player 1: %s  %s   Player 2: %s' % (p1, comp, p2)
        total += p1 > p2
    print total
