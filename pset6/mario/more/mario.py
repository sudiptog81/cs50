"""
PSet 6 - Sentimental/Mario - More Comfortable
Written by Sudipto Ghosh for CS50
"""

from cs50 import get_int

# get valid user input for height
while True:
    height = get_int("Height: ")
    if height >= 1 and height <= 8:
        break

# print the mario blocks
for i in range(1, height + 1):
    # print the spaces
    print(" " * (height - i), end="")

    # print the left blocks
    print("#" * i, end="")

    # print the separator
    print(" " * 2, end="")

    # print the right blocks
    print("#" * i, end="")

    # print a new line
    print()
