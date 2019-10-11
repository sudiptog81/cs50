"""
PSet 6 - Sentimental/Crack
Written by Sudipto Ghosh for CS50

"""

from time import sleep
from crypt import crypt
from sys import argv

ALPHABETS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"


def getArgs():
    """
    validates arguments passed during execution
    """
    # ensures only two arguments are passed
    if not len(argv) == 2:
        exit("Usage: python crack.py hash")

    return argv[1]


def check(password, salt, hash):
    """
    checks whether the password is valid
    """
    return hash == crypt(password, salt)


def crack(hash):
    """
    bruteforces hash to find out the password
    """
    # extract salt
    salt = hash[:2]

    # iterate over all possible permutations
    password = ""
    attempts = 0
    for i in range(len(ALPHABETS)):
        for j in range(len(ALPHABETS)):
            for k in range(len(ALPHABETS)):
                for l in range(len(ALPHABETS)):
                    for m in range(len(ALPHABETS)):
                        attempts += 1
                        if check(password, salt, hash):
                            return password, attempts, True
                        password = ALPHABETS[m] + password[1:]
                    password = password[:1] + ALPHABETS[l] + password[2:]
                password = password[:2] + ALPHABETS[k] + password[3:]
            password = password[:3] + ALPHABETS[j] + password[4:]
        password = password[:4] + ALPHABETS[i] + password[5:]

    return "", attempts, False


def main():
    # get cli arguments
    hash = getArgs()

    # get password and cracked flag
    password, attempts, cracked = crack(hash)

    # print password if cracked flag is true
    print(f"Password: {password}\nAttempts: {attempts}" if cracked else "Couldn't crack")


if __name__ == "__main__":
    main()