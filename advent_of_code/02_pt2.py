import sys
import re

def main():
    pw_re = re.compile(r'^(?P<lo>\d+)-(?P<hi>\d+) (?P<c>\w): (?P<s>\w+)$')
    ans = 0
    for line in sys.stdin:
        match = pw_re.search(line)
        assert(match)

        gd = match.groupdict()
        password = gd['s']
        ch = gd['c']
        lo = int(gd['lo'])-1
        hi = int(gd['hi'])-1
        if (password[lo] == ch) + (password[hi] == ch) == 1:
            ans += 1

    print(ans)


if __name__ == '__main__':
    main()
