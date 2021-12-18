# Couldn't figure this one out so I got help from this video:
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
    for number in ints:
        for board in boards:
            board.left.discard(number)
            

        for board in boards:
            if board.has_won:
                return sum(board.left) * number

    raise AssertionError('unreachable')

print(get_number())
