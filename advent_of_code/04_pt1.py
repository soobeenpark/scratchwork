import sys

def processLine(line):
    ret = {}
    items = line.split(" ")
    for item in items:
        keyval = item.split(":")
        key = keyval[0]
        val = keyval[1]
        ret[key] = val
    return ret

def isValidPassport(passport):
    return len(passport) == 8 or (len(passport) == 7 and "cid" not in passport)

def main():
    passports = []
    passport = {}
    for line in sys.stdin:
        if str.isspace(line):
            assert(passport)
            if isValidPassport(passport):
                print(passport)
                passports.append(passport)
            passport = {}
        else:
            passport.update(processLine(line))
    print(len(passports))
            

if __name__ == '__main__':
    main()
