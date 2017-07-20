from monopoly import *

def test_regmove():
    g = Game()
    g.move(5)
    assert g.pos == squares['R1']
    assert g.board[g.pos] == 1
    assert sum(g.board) == 1

def test_chest_GO():
    g = Game()
    g.move(1)
    assert g.pos == squares['A1']
    g.CC.remove(squares['GO'])
    g.CC.appendleft(squares['GO'])
    assert g.CC[0] == squares['GO']
    g.move(1)
    assert g.pos == squares['GO']
    assert g.board[g.pos] == 1
    assert g.board[squares['CC1']] == 0

def test_chest_JAIL():
    g = Game()
    g.move(1)
    assert g.pos == squares['A1']
    g.CC.remove(squares['JAIL'])
    g.CC.appendleft(squares['JAIL'])
    assert g.CC[0] == squares['JAIL']
    g.move(1)
    assert g.pos == squares['JAIL']
    assert g.board[g.pos] == 1
    assert g.board[squares['CC1']] == 0

def test_chance_GO():
    g = Game()
    g.CH.remove(squares['GO'])
    g.CH.appendleft(squares['GO'])
    assert g.CH[0] == squares['GO']
    g.move(7)
    assert g.pos == squares['GO']
    assert g.board[g.pos] == 1
    assert sum(g.board) == 1

def test_chance_next_R():
    g = Game()
    g.CH.remove(g.next_R)
    g.CH.appendleft(g.next_R)
    assert g.CH[0] == g.next_R
    g.move(36)
    assert g.pos == squares['R1']
    assert g.board[g.pos] == 1
    assert sum(g.board) == 1

def test_chance_next_U():
    g = Game()
    g.CH.remove(g.next_U)
    g.CH.appendleft(g.next_U)
    assert g.CH[0] == g.next_U
    g.move(36)
    assert g.pos == squares['U1']
    assert g.board[g.pos] == 1
    assert sum(g.board) == 1

def test_chance_back_3():
    g = Game()
    g.CH.remove(g.back_3)
    g.CH.appendleft(g.back_3)
    assert g.CH[0] == g.back_3
    g.move(7)
    assert g.pos == squares['T1']
    assert g.board[g.pos] == 1
    assert sum(g.board) == 1
