with open('passports.txt') as f:
    passports = f.read()
    passports = passports.split("\n\n")

# Solution 1
reqFields = ["byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"] # "cid" is not required
validPassports = []

# This function checks for passports that have all required fields present (And nothing else!)
def validate_fields():
    for passport in passports:
        if all(x in passport for x in reqFields):
            validPassports.append(passport)
        
    return validPassports

print("Passports that meet the first criteria: ", len(validate_fields()), "\n")

# Solution 2
# This functions takes the fields in each passport and checks if the data in those fields is valid
def validate_data():
    newPassports = validPassports # Passports that passed the first check
    legitPassports = [] # Passports that have passed the second check and have been deemed legitamate
    for passport in newPassports:
        fields = passport.split() # Separating each field
        for field in fields:
            data = field.split(":", 1) # Separating data within each field

            # Verifying each piece of information

            # Birth year
            if data[0] == "byr":
                if 1920 <= int(data[1]) <= 2002:
                    birthYear = True
                else:
                    birthYear = False
            
            # Issue year
            if data[0] == "iyr":
                if 2010 <= int(data[1]) <= 2020:
                    issueYear = True
                else:
                    issueYear = False

            # Expiration year
            if data[0] == "eyr":
                if 2020 <= int(data[1]) <= 2030:
                    expYear = True
                else:
                    expYear = False

            # Height
            if data[0] == "hgt":
                if "cm" in data[1]:
                    data[1] = data[1].removesuffix('cm')
                    if 150 <= int(data[1]) <= 193:
                        height = True
                    else:
                        height = False

                elif "in" in data[1]:
                    data[1] = data[1].removesuffix('in')
                    if 59 <= int(data[1]) <= 76:
                        height = True
                    else:
                        height = False
                
                else:
                    height = False

            # Hair color
            if data[0] == "hcl":
                invalidLetters = ["g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v"]
                if (not any(x in data[1] for x in invalidLetters)) and len(data[1]) <= 7 and data[1].startswith('#'):
                    hairColor = True
                else:
                    hairColor = False

            # Eye Color
            if data[0] == "ecl":
                validEyeColors = ["amb", "blu", "brn", "gry", "grn", "hzl", "oth"]
                if any(x in data[1] for x in validEyeColors) and len(data[1]) <= 3:
                    eyeColor = True
                else:
                    eyeColor = False

            # Passport ID
            if data[0] == "pid":
                if data[1].isdecimal() and len(data[1]) == 9:
                    passID = True
                else:
                    passID = False

            # Country ID
                # N/A

        if (birthYear == True and issueYear == True and 
            expYear == True and height == True and 
            hairColor == True and eyeColor == True and 
            passID == True):
            legitPassports.append(passport)

    return(len(legitPassports))

print("Passports that meet the second criteria: ", validate_data())