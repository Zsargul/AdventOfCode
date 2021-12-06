with open('input.txt') as f:
    input = f.readlines()
    input = [line.strip() for line in input]

# Solution 1
def getAccumulator():
    acc = 0
    line = 0
    executedCommands = []

    # Keeping track of commands already executed
    # This while loop stops once it hits the command that is about to be executed a second time
    while line not in executedCommands:
        executedCommands.append(line)

        # Splitting commands into cmd and arg
        currentCommand = input[line]
        currentCommand = currentCommand.split()
        cmd = currentCommand[0]
        arg = currentCommand[1]

        # If the command is acc, increase/decrease the accumulator using the arg
        if cmd == 'acc':
            acc += int(arg)
            line += 1

        # If the command is jmp, increase the line (i.e position of command to be executed) accordingly
        elif cmd == 'jmp':
            line += int(arg)

        # If the command is nop, do nothing
        elif cmd == 'nop':
            line += 1

    return acc

print("Accumulator value at first repeat: ", getAccumulator())

# Solution 2
def getAccumulatorEof():
    acc = 0
    line = 0
    executedCommands = []

    # Keeping track of commands already executed
    # This while loop stops once it hits the command that is about to be executed a second time
    while line not in executedCommands:
        executedCommands.append(line)

        # Splitting commands into cmd and arg
        currentCommand = input[line]
        currentCommand = currentCommand.split()
        cmd = currentCommand[0]
        arg = currentCommand[1]

        # If the command is acc, increase/decrease the accumulator using the arg
        if cmd == 'acc':
            acc += int(arg)
            line += 1

        # If the command is jmp, increase the line (i.e position of command to be executed) accordingly
        elif cmd == 'jmp':
            line += int(arg)

        # If the command is nop, do nothing
        elif cmd == 'nop':
            line += 1

        # If 'line >= the length of the input', then that means we are at the end of the file
        if line >= len(input):
            return acc, True

    return acc, False

# Testing which 'jmp' must be changed to a 'nop' by iterating through all the commands and changing 'jmp' to 'nop'
for i in range(len(input)):
    if 'jmp' in input[i]:
        input[i] = input[i].replace('jmp', 'nop')
        acc, found = getAccumulatorEof()
        
        if found:
            print("Accumulator at the end of file: ", acc)
            break
        else: 
            input[i] = input[i].replace('nop', 'jmp')