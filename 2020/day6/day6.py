with open('input.txt') as f:
    input = f.read()
    groups = input.split("\n\n")
    
# Solution 1
count = 0 

for group in groups:
    answers = [] # Collecting all answers from each group into this array
    for letter in group:
        if not letter == '\n':
            answers.append(letter)
    count+=(len(set(answers)))

print("Sum of answers: ", count)

# Solution 2
count = 0

from collections import Counter

for group in groups:
    letterCounter = Counter(group) # Counts occurences of each letter in each group
    personCount = len(group.split('\n'))

    # Assigns a value of either true or false to universalAnswers, depending on whether
    # or not the occurence of a letter is equal to the amount of people in the group
    universalAnswers = [occurence == personCount for occurence in letterCounter.values()]
    
    # Summing all 'True' answers (answers which were answered as 'yes' by everyone in the group)
    # and adding them to the rolling total
    count+=sum(universalAnswers)

print("Sum of all answers answered by everyone in each group: ", count)