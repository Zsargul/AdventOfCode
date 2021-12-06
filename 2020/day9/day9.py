with open('input.txt') as f:
    input = f.readlines()
    input = [line.strip() for line in input]
    data = list(map(int, input))

preambleSize = 25

# Solution 1

# Using this function to check if 2 values sum into the next number, and if they do, return True
def sumCheck(num: int, preamble: list):
    for x in preamble:
        if num - x in preamble and num - x != x:
            return True
        
    return False

# Iterating through the changing 25 numbers and checking if any 2
# of those numbers sum to the next number. If not, return the next number.
def solution1(list):
    currentNums = data[:preambleSize]
    for x in range(preambleSize, len(data)):
        if not sumCheck(data[x], currentNums):
            return data[x] 

        currentNums = currentNums[1:] + [data[x]]

invalidNumber = solution1(data)

print("Invalid Number: ", invalidNumber)

# Solution 2
def solution2(invalidNumber, list):
    end = 3
    while True:
        for start in range(len(data) - end):
            if sum(data[start:start+end]) == invalidNumber:
                lowestNum = min((data[start:start + end]))
                highestNum = max((data[start:start + end]))

                return lowestNum + highestNum

        end += 1

print(f"Sum of the Min and Max of the numbers that sum to {invalidNumber}: ", solution2(invalidNumber, data))