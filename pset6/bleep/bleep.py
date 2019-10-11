"""
PSet 6 - Bleep
Written by Sudipto Ghosh for CS50

"""

from cs50 import get_string
from sys import argv


def getArgs():
    """
    validates arguments passed during execution
    """
    # ensure only two arguments are passed
    if not len(argv) == 2:
        exit("Usage: python bleep.py dictionary")

    return argv[1]


def loadList(bannedList):
    """
    loads the list to memory
    """
    # initialise a set
    words = set()

    # open the bannedList file and
    # add words to the ser
    with open(bannedList, "r") as file:
        for word in file:
            words.add(word.rstrip("\n"))

    return words


def censor(message, bannedList):
    """
    censors the passed string
    """
    # split the message into a list
    message = message.split(" ")

    # manipulate elements of the list
    # based on the given conditions
    message = ["*" * len(m) if m.lower() in bannedList else m for m in message]

    return " ".join(message)


def main():
    # extract arguments
    bannedList = getArgs()

    # prompt user for message to be censored
    message = get_string("What message would you like to censor?\n")

    # load bannedlist into memory
    bannedWords = loadList(bannedList)

    # censor the message as per the bannedList
    censoredMessage = censor(message, bannedWords)

    # print the censored message
    print(censoredMessage)


if __name__ == "__main__":
    main()
