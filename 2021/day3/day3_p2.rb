# This is my first ruby program so it might be fairly sub-par

binarynums = File.readlines("input.txt")

oneCount = 0
zeroCount = 0
i = 0

gRate = ""
eRate = ""

# Iterate through binary numbers and their elements,
# and count the occurences of 0 and 1, appending the
# less/more frequent values onto epsilon/gamme rates
# respectively
n = 0
while n < binarynums[1].length

  for num in binarynums do 
    if num[i] == '1'
      oneCount+=1
    elsif num[i] == '0'
      zeroCount+=1
    end
  end

  if oneCount > zeroCount
    gRate << "1"
    eRate << "0"
  elsif zeroCount > oneCount
    gRate << "0"
    eRate << "1"
  end

  zeroCount = 0
  oneCount = 0

  i+=1
  n+=1
end

# Keep binary values are separate variables
gRateBin = gRate
eRateBin = eRate

# Convert binary to decimal
gRateDec = eRate.to_i(2)
eRateDec = gRate.to_i(2)

# Get total power consumption
powerCons = gRateDec * eRateDec
puts "Power Consumption: " + powerCons.to_s()

# Function to get oxygen rating
def oxygenRating arr

  i = 0
  zeroCount = 0
  oneCount = 0


  # Iterating array and removing elements with most common values (1/0)
  while arr.length() > 1

    for num in arr do
      if num[i] == '1'
        oneCount += 1
      elsif num[i] == '0'
        zeroCount += 1
      end
    end

    if oneCount >= zeroCount
      for num in arr do
        arr.delete_if { |num| num[i] == '0' }
      end
    elsif zeroCount > oneCount
      for num in arr do
        arr.delete_if { |num| num[i] == '1' }
      end
    end

    i+=1
    zeroCount = 0
    oneCount = 0

  end
  
  arr[0]

end

# Function to get C02 Scrubber Rating
def c02rating arr
  
  i = 0
  zeroCount = 0
  oneCount = 0

  # Iterating array and removing elements with least common values (1/0)
  while arr.length() > 1

    for num in arr do
      if num[i] == '1'
        oneCount += 1
      elsif num[i] == '0'
        zeroCount += 1
      end
    end

    if zeroCount <= oneCount
      for num in arr do
        arr.delete_if { |num| num[i] == '1' }
      end
    elsif oneCount < zeroCount
      for num in arr do
        arr.delete_if { |num| num[i] == '0' }
      end
    end

    i+=1 
    zeroCount = 0
    oneCount = 0

  end 
  
  arr[0]

end

# Getting Oxygen Generator Rating & C02 Scrubber Rating

oxygen_generator_rating = oxygenRating(binarynums)
oxDec = oxygen_generator_rating.to_i(2)
puts "Oxygen Generator Rating:\t#{oxygen_generator_rating}(#{oxDec.to_s()})"

# For some reason I had to put this line here AGAIN otherwise the 2 functions would
# give me identical output. I have no idea why. This is the only thing that I found
# that fixed it.
binarynums = File.readlines("input.txt")

c02_scrubber_rating = c02rating(binarynums)
c02Dec = c02_scrubber_rating.to_i(2)  
puts "C02 Scrubber Rating:\t\t#{c02_scrubber_rating}(#{c02Dec.to_s()})"

# Getting final life support value
lifeSupport = oxDec * c02Dec
puts "Life Support:\t\t\t#{lifeSupport}"
