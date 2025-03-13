#!/usr/bin/python3
"""a method that determines if a given data"""


def validUTF8(data):
    """a method that determines if a given data """
    try:
        maskeddata = [n & 255 for n in data]
        bytes(maskeddata).decode("UTF-8")
        return True
    except Exception:
        return False
