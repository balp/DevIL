#!/usr/bin/env python
#
#
#

from ctypes import *
import os
import sys

libPath = os.path.join(os.path.dirname(__file__), "..", "build",
	"libIL.so")
ILLIBRARY = CDLL(libPath)

def osCurdir():
    return os.getcwd()

def ilInit():
    """Set up the IL library"""
    ILLIBRARY.ilInit()

def ilGenAndBindImage():
    """Make a new image"""
    ImgID = c_uint()
    ILLIBRARY.ilGenImages(c_int(1), byref(ImgID))
    ILLIBRARY.ilBindImage(ImgID)
    return ImgID

def ilLoadImage(filename):
    """Load a image into memory."""
    return ILLIBRARY.ilLoadImage(c_char_p(filename))

def ilGetError():
    """Get current error status"""
    return ILLIBRARY.ilGetError()

if __name__ == "__main__":
    try:
        ilInit()
        tmp = ilGenAndBindImage()
        res = ilLoadImage(sys.argv[1])
        print "Error code: 0x%04X" % (ilGetError())
    except AssertionError, err:
        print err

