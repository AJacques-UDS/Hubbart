from math import sqrt
from typing import Tuple

def findRoots(a: float, b: float, c: float) -> Tuple[bool, float, float]:
    if a == 0:
        return (1, 0, 0)

    d = b * b - 4 * a * c
    print(d)
    sqrt_val = sqrt(abs(d))

    if d > 0:
        return (0, (-b + sqrt_val)/(2 * a), (-b - sqrt_val)/(2 * a))
    elif d == 0:
        return (0, -b / (2 * a), -b / (2 * a))

    return (1, 0, 0)

if __name__ == "__main__":

    res1 = findRoots(1, -7, 12)
    res2 = findRoots(2, 4, 4)
    res3 = findRoots(2, -4, 2)
    res4 = findRoots(0, 4, 4)

    print(res1)
    print(res2)
    print(res3)
    print(res4)