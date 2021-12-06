with open('input.txt') as input:
    lines = list(input);

horizontal = 0
depth = 0

for line in lines:
    command, num = line.split(" ")
    if (command == "forward"):
        horizontal += int(num)
    elif (command == "down"):
        depth += int(num)
    else:
        depth -= int(num)

position = horizontal * depth

print("Final position is", position);
