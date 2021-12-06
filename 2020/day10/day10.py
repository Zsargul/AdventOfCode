with open('input.txt') as f:
    input = f.readlines()
    input = [line.strip() for line in input]
    data = list(map(int, input))
    data.sort()

# Appending the built-in adapter
data.append(max(data)+3)

# Solution 1

# Built-in adapter is rated 3 jolts higher than the highest rated adapter
builtInAdapter = 3

def getDifferences(adapters):
    differences = []

    rating = 0 # Joltage of charging outlet begins at 0

    # Iterating through adapters and finding differences
    for adapter in adapters:
            difference = adapter-rating
            differences.append(difference)
            rating = adapter
    
    # Counting the differences
    dif1 = differences.count(1)
    dif2 = differences.count(2)
    dif3 = differences.count(3)

    return dif1, dif2, dif3

count1, count2, count3 = getDifferences(data)
solution1 = count1 * count3

print("1-jolt differences multiplied by 3-jolt differences: ", solution1)

# Solution 2
def getArrangements(adapters):
    
    sol = {0:1}
    for adapter in adapters:
        sol[adapter] = 0

        if adapter - 1 in sol:
            sol[adapter] += sol[adapter-1]
        if adapter - 2 in sol:
            sol[adapter] += sol[adapter-2]
        if adapter - 3 in sol:
            sol[adapter] += sol[adapter-3]

    return sol[max(adapters)]

print("Distinct arrangements: ", getArrangements(data))