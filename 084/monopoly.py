"""
The following monopoly simulator appears to have a small bug. This leads to an
incorrect result when simulating with regular 6-sided dice. However,
the bug seems to be small enough that the correct result for 4-sided dice is
still produced.
"""

from collections import deque, OrderedDict
import random

square_names = ['GO', 'A1', 'CC1', 'A2', 'T1', 'R1', 'B1', 'CH1', 'B2', 'B3', 'JAIL',
                'C1', 'U1', 'C2', 'C3', 'R2', 'D1', 'CC2', 'D2', 'D3', 'FP',
                'E1', 'CH2', 'E2', 'E3', 'R3', 'F1', 'F2', 'U2', 'F3', 'G2J',
                'G1', 'G2', 'CC3', 'G3', 'R4', 'CH3', 'H1', 'T2', 'H2']
squares = OrderedDict((name, number) for number, name in enumerate(square_names))

class Game(object):
    def __init__(self):
        self.board = [0 for i in range(40)]
        self.pos = squares['GO']
        self.CC = deque([squares['GO'], squares['JAIL']] + [-1]*14)
        self.CH = deque([squares['GO'], squares['JAIL'], squares['C1'],
                   squares['E3'], squares['H2'], squares['R1'],
                   self.next_R, self.next_R, self.next_U, self.back_3] + [-1]*6)
        random.shuffle(self.CC)
        random.shuffle(self.CH)
        self.play_count = 0
        self.double_count = 0

    def dice_throw(self):
        dice1 = random.randint(1, 4)
        dice2 = random.randint(1, 4)
        if dice1 == dice2:
            self.double_count += 1
        else:
            self.double_count = 0
        return dice1 + dice2

    def move(self, throw=None):
        if not throw:
            throw = self.dice_throw()
        if self.double_count == 3:
            self.pos = squares['JAIL']
            self.double_count = 0
        else:
            self.pos = (self.pos + throw) % 40

        if self.pos == squares['G2J']:
            self.pos = squares['JAIL']
        if self.pos in (squares['CH1'], squares['CH2'], squares['CH3']):
            card = self.CH.popleft()
            self.CH.append(card)
            if isinstance(card, int):
                if card >= 0:
                    self.pos = card
            else:
                self.pos = card()
        if self.pos in (squares['CC1'], squares['CC2'], squares['CC2']):
            card = self.CC.popleft()
            self.CC.append(card)
            if card >= 0:
                self.pos = card

        self.board[self.pos] += 1
        self.play_count += 1

    def next_R(self):
        square = self.pos
        while not square_names[square].startswith('R'):
            square = (square + 1) % 40
        return square

    def next_U(self):
        square = self.pos
        while not square_names[square].startswith('U'):
            square = (square + 1) % 40
        return square

    def back_3(self):
        return (40 + self.pos - 3) % 40


if __name__ == "__main__":
    g = Game()
    for _ in range(10000000):
        g.move()

    sort = sorted(((square, g.board[idx] / g.play_count) \
                   for square, idx in squares.items()),
                   key=lambda pair: -pair[1])
    print(''.join(str(squares[square]) for square, prob in sort[:3]))

