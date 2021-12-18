# Couldn't figure this one out so i got help from this video:
# https://www.youtube.com/watch?v=zAjliaaIjIc

from __future__ import annotations
from typing import NamedTuple

with open('input.txt', 'r') as text:
    data = text.read()

class Board(NamedTuple):
    left: set[int]
    ints: list[int]

    @property
    def has_won(self) -> bool:
        for i in range(5):
            for j in range(5):
                if self.ints[i * 5 + j] in self.left:
                    break
            else: return True

            for j in range(5):
                if self.ints[i + 5 * j] in self.left:
                    break
            else: return True
        else:
            return False

    @classmethod
    def parse(cls, board: str) -> Board:
        ints = [int(s) for s in board.split()]
        left = set(ints)
        return cls(left, ints)


first, *rest = data.split('\n\n')
boards = [Board.parse(board) for board in rest]
ints = [int(s) for s in first.split(',')]

def get_number() -> int:
    last_winner = -1
    seen = set()
    for number in ints:
        for board in boards:
            board.left.discard(number)
            

        for i, board in enumerate(boards):
            if i not in seen and board.has_won:
                 last_winner = sum(board.left) * number
                 seen.add(i)

    return last_winner 

print(get_number())
