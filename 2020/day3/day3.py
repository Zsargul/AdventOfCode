with open('input.txt', 'r') as input:
    map_ = [line.rstrip() for line in input]

# This function works for both part 1 and part 2 of the problem
def treeCount(right: int, down: int):
    trees = 0

    x = 0
    y = 0
    mapHeight = len(map_)
    mapWidth = len(map_[0])

    while y < mapHeight:
        line = map_[y]
        if line[x%mapWidth] == '#':
            trees += 1

        x += right
        y += down

    return trees

print("Total for Solution 1: ", treeCount(3,1))

# Multiplying answers for part 2
def total():
    return (
        treeCount(1,1) * treeCount(3,1) * treeCount(5,1) * treeCount(7,1) * treeCount(1,2)
    )

print("Total for Solution 2: ", total())