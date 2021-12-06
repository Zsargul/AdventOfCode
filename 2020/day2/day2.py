pwdata = open('password_database.txt').readlines()
pwdata = [line.strip() for line in pwdata]

valid1 = []
invalid1 = []

valid2 = []
invalid2 = []

for line in pwdata:
    policy, password = line.split(": ")
    #print(line)
    #print(policy, password)
    letter = policy.split(" ")[1]
    #print(letter)
    num1, num2 = policy.split(" ")[0].split("-")
    #print(minnum, maxnum, letter)
    num1, num2 = int(int(num1)-1), int(int(num2)-1)
    #print(num1, num2)

    # Solution 1
    if int(num1+1) <= password.count(letter) <= int(num2+1):
        valid1.append(password)
    else:
        invalid1.append(password)

    # Solution 2
    
    # Converting the numbers into ints to be used as index positions
    letter_position = lambda x: [int(i) for i in x]
    num1, num2 = letter_position([num1, num2])

    count = 0
    if password[num1] == letter:
        count+=1
    
    if password[num2] == letter:
        count+=1

    if count == 1:
        valid2.append(password)
    else:
        invalid2.append(password)

print("Solution 1:\nValid passwords: ", len(valid1), "\nInvalid Passwords: ", len(invalid1))
print("\nSolution 2:\nValid passwords: ", len(valid2), "\nInvalid Passwords: ", len(invalid2))