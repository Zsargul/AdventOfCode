# The results print out multiple times in the console, but the answers are correct regardless

# Reading from file with expenses & making it a list of integers
with open('expense_report.txt') as file:
    expenses = file.readlines()

expenses = [line.rstrip() for line in expenses]    
expenses = list(map(int, expenses))

# Getting first answer
print("First answer:")
for i in expenses:
    if 2020-i in expenses:
        print(i, " + ", 2020-i, " = ", (i+(2020-i)))
        print(i, " * ", 2020-i, " = ", i*(2020-i))

# Getting second answer
print("\nSecond answer:")
for i in expenses:
    for x in expenses:
        if (2020-i-x) in expenses:
            print(2020-i-x, " + ", i, " + ", x, " = ", (i+x+(2020-i-x)))
            print(2020-i-x, " * ", i, " * ", x, " = ", i*x*(2020-i-x))