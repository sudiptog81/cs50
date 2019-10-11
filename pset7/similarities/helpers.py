"""
PSet 7.1 - Similarities
Written by Sudipto Ghosh for CS50

"""

from nltk.tokenize import sent_tokenize as st


def lines(a, b):
    """Return lines in both a and b"""

    union = []

    for el in a.split("\n"):
        # check if el is in b as well as unique
        if el in b.split("\n") and el not in union:
            # add el to list
            union.append(el)

    return union


def sentences(a, b):
    """Return sentences in both a and b"""

    union = []

    for el in st(a):
        # check if el is in b as well as unique
        if el in st(b) and el not in union:
            # add el to list
            union.append(el)

    return union


def subt(s, n):
    """Returns list of substrings in s"""

    l = []

    for i in range(len(s) - (n - 1)):
        # add el to list
        l.append(s[i:(i + n)])

    return l


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    union = []

    for el in subt(a, n):
        # check if el is in b as well as unique
        if el in subt(b, n) and el not in union:
            # add el to list
            union.append(el)

    return union
