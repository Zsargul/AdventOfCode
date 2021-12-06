with open('input.txt', 'r') as input:
    boardingPasses = [line.rstrip() for line in input]

# Solution 1

# Used to convert the row (first 7 letters) to binary
def binaryConversionRows(string):
    translation = string.maketrans("FB", "01")
    return string.translate(translation)

# Used to convert colummn (last 3 letters) to binary
def binaryConversionColumns(string):
    translation = string.maketrans("LR", "01")
    return string.translate(translation)

for boardingPass in boardingPasses:
    
    # Converting rows and columns to decimal values and then back to binary
    binaryRows = [binaryConversionRows(boardingPass[:7]) for boardingPass in boardingPasses]
    decimalRows = [int(binaryRow, 2) for binaryRow in binaryRows] 

    binaryColumns = [binaryConversionColumns(boardingPass[-3:]) for boardingPass in boardingPasses]
    decimalColumns = [int(binaryColumn, 2) for binaryColumn in binaryColumns]

    # Combining rows and colummns into seats
    seats = zip(decimalRows, decimalColumns)

    seatIDs = []

    # Assigning seat IDs
    for seat in seats:
        seatIDs.append(seat[0] * 8 + seat[1])

print("The highest seat ID is: ", max(seatIDs))

# Solution 2

# Iterating through the seats and checking for the missing seat
for seat in seatIDs:
    if (seat+2 in seatIDs) and not (seat+1 in seatIDs):
        mySeat = seat+1

print("\nMy seat ID: ", mySeat)