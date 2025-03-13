#!/usr/bin/python3
"""a method that determines if a given data set represents a valid UTF-8 encoding"""


def validUTF8(data):
    """a method that determines if a given data set represents a valid UTF-8 encoding"""
    try:
        maskeddata = [n & 255 for n in data]
        bytes(maskeddata).decode("UTF-8")
        return True
    except Exception:
        return False
