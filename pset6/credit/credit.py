"""
  PSet 6 - Sentimental/Credit
  Written by Sudipto Ghosh for CS50
"""

from cs50 import get_int

# get card number from user input
while True:
    cardNumber = get_int("Number: ")
    if cardNumber > 0:
        break

# calculate number of digits
digits = len(str(cardNumber))

# find out checksum digits * 2
checksumDigits = []
for i in range(1, 17, 2):
    checksumDigits.append((cardNumber // 10 ** i) % 10 * 2)

# calculate sum of checksum digits
sum = 0
for i in checksumDigits:
    for j in range(2):
        sum += i % 10
        i //= 10

# add remaining digits to sum
for j in range(0, 16, 2):
    sum += (cardNumber // 10 ** j) % 10

# determine and print card type
if sum % 10 == 0:
    first = int(str(cardNumber)[0])
    firstTwo = int(str(cardNumber)[0]) * 10 + int(str(cardNumber)[1])

    if digits == 13:
        if first == 4:
            print("VISA")
        else:
            print("INVALID")
    elif digits == 15:

        if (firstTwo == 34 or firstTwo == 37):
            print("AMEX")
        else:
            print("INVALID")
    elif digits == 16:
        if first == 4:
            print("VISA")
        elif (firstTwo == 51 or
              firstTwo == 52 or
              firstTwo == 53 or
              firstTwo == 54 or
              firstTwo == 55):
            print("MASTERCARD")
        else:
            print("INVALID")
else:
    print("INVALID")
