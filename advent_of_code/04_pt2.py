import sys
import re

def processLine(line):
    ret = {}
    items = line.split(" ")
    for item in items:
        keyval = item.split(":")
        key = keyval[0].strip()
        val = keyval[1].strip()
        ret[key] = val
    return ret

def isValidPassport(passport):
    if not (len(passport) == 8 or (len(passport) == 7 and "cid" not in passport)):
        return False

    birthyear = int(passport["byr"])
    issueyear = int(passport["iyr"])
    expireyear = int(passport["eyr"])

    heightRegex = re.compile(r"^(?P<height>\d+)(?P<unit>cm|in)$")
    heightMatch = heightRegex.match(passport["hgt"])

    haircolorRegex = re.compile(r"^#[0-9a-f]{6}$")
    haircolorMatch = haircolorRegex.match(passport["hcl"])
    
    eyecolorRegex = re.compile(r"^(amb|blu|brn|gry|grn|hzl|oth)$")
    eyecolorMatch = eyecolorRegex.match(passport["ecl"])

    pidRegex = re.compile(r"^\d{9}$")
    pidMatch = pidRegex.match(passport["pid"])
    
    if 1920 > birthyear or birthyear > 2002:
        return False
    if 2010 > issueyear or issueyear > 2020:
        return False
    if 2020 > expireyear or expireyear > 2030:
        return False
    if not (heightMatch and haircolorMatch and eyecolorMatch and pidMatch):
        return False

    assert(heightMatch)
    heightDict = heightMatch.groupdict()
    height = int(heightDict["height"])
    unit = heightDict["unit"]
    if unit == "cm" and height not in range(150, 194):
        return False
    if unit == "in" and height not in range(59, 77):
        return False
    # All checks out!
    return True

def addValidPassport(passports, passport):
    assert(passport)
    if isValidPassport(passport):
        print("valid: " + str(passport))
        passports.append(passport)

def main():
    passports = []
    passport = {}
    for line in sys.stdin:
        if str.isspace(line):
            # Add parsed passport and start processing a new one
            addValidPassport(passports, passport)
            passport = {}
        else:
            # Continue parsing current passport
            passport.update(processLine(line))
    # Add one final passport on last line
    addValidPassport(passports, passport)
    print(len(passports))

if __name__ == '__main__':
    main()
