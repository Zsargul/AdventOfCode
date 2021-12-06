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

puts "Gamme rate: \t\t" + gRateDec.to_s + "\t(" + gRateBin + ")"
puts "Epsilon rate: \t\t" + eRateDec.to_s + "\t(" + eRateBin + ")"
puts "Power Consumption: \t" + powerCons.to_s
