def factorial_num_zeroes(n):
    ans = 0
    div = 5
    while (n >= div):
        ans += n//div
        div *= 5
    return ans

def main():
    # Tests
    assert(factorial_num_zeroes(1) == 0)
    assert(factorial_num_zeroes(2) == 0)
    assert(factorial_num_zeroes(3) == 0)
    assert(factorial_num_zeroes(4) == 0)
    assert(factorial_num_zeroes(5) == 1)
    assert(factorial_num_zeroes(8) == 1)
    assert(factorial_num_zeroes(10) == 2)
    assert(factorial_num_zeroes(11) == 2)
    assert(factorial_num_zeroes(19) == 3)
    assert(factorial_num_zeroes(24) == 4)
    assert(factorial_num_zeroes(25) == 6)
    assert(factorial_num_zeroes(125) == 31)
    assert(factorial_num_zeroes(127) == 31)
    
    print(factorial_num_zeroes(1))
    print(factorial_num_zeroes(2))
    print(factorial_num_zeroes(3))
    print(factorial_num_zeroes(4))
    print(factorial_num_zeroes(5))
    print(factorial_num_zeroes(8))
    print(factorial_num_zeroes(10))
    print(factorial_num_zeroes(11))
    print(factorial_num_zeroes(19))
    print(factorial_num_zeroes(24))
    print(factorial_num_zeroes(25))
    print(factorial_num_zeroes(125))
    print(factorial_num_zeroes(127))


if __name__ == '__main__':
    main()
