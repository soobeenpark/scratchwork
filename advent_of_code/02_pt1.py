import sys
import re

def main():
    pw_re = re.compile(r'^(?P<lo>\d+)-(?P<hi>\d+) (?P<c>\w): (?P<s>\w+)$')
    ans = 0
    for line in sys.stdin:
        match = pw_re.search(line)
        assert(match)

        gd = match.groupdict()
        cnt = gd['s'].count(gd['c'])
        if cnt >= int(gd['lo']) and cnt <= int(gd['hi']):
            ans += 1

    print(ans)


if __name__ == '__main__':
    main()
