# Thanks to Dylan from 'Dylan Codes' on Youtube for helping me out with this one, with his fantastic video
# Check it out here: https://www.youtube.com/watch?v=7IOd7wvxDX0

with open('input.txt') as f:
    rules = f.readlines()
    rules = [line.strip() for line in rules]

# Solution 1

def getBags(colour):
    # Find every line in the rules that contains given color
    lines = [line for line in rules if colour in line and line.index(colour) != 0] 

    allColours = []

    # If no other bags hold the argument bag, then an empty list is returned
    if len(lines) == 0:
        return []

    else:
        colours = [line[:line.index(' bags')] for line in lines]

        # Keeping track of colors we have checked
        colours = [colour for colour in colours if colours not in allColours]
        
        # Using the function recursively to find the total amount of colors
        for colour in colours:
            allColours.append(colour)
            bags = getBags(colour)
            allColours += bags

        # Getting rid of duplicates
        uniqueColours = []
        for colour in allColours:
            if colour not in uniqueColours:
                uniqueColours.append(colour)

        return uniqueColours

colors = getBags('shiny gold')

print("The number of bags that contain shiny gold are: ", len(colors))

# Solution 2
def getBagCount(colour):

    # Finding the rule for the color
    rule = ''
    for line in rules:
        if line[:line.index(' bags')] == colour:
            rule = line
            
    if 'no' in rule:
        return 1

    # Splitting the rule into the different colors and their respective counts
    rule = rule[rule.index('contain')+8:].split()

    # Finding the total amount of bags by using the function recursively
    total = 0
    i = 0
    while i < len(rule):
        count = int(rule[i])
        colour = rule[i+1] + ' ' + rule[i+2]

        total += count * getBagCount(colour)
        i += 4

    return total + 1

# Subtracting 1 because the function above counts the original bag, making the return value 1 too many
count = getBagCount('shiny gold') - 1

print("The amount of required bags are: ", count)