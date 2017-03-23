"""
Extract a csv file out of video file representing eye blinks.

"""
    
__author__           = "Dilawar Singh"
__copyright__        = "Copyright 2015, Dilawar Singh and NCBS Bangalore"
__credits__          = ["NCBS Bangalore"]
__license__          = "GNU GPL"
__version__          = "1.0.0"
__maintainer__       = "Dilawar Singh"
__email__            = "dilawars@ncbs.res.in"
__status__           = "Development"

import cv2
import numpy as np
import os



def merge_contours(cnts, img):
    """Merge these contours together. And create an image"""
    for c in cnts:
        hull = cv2.convexHull(c)
        cv2.fillConvexPoly(img, hull, 0)
    return img


def accept_contour_as_possible_eye( contour, threshold = 0.1 ):
    # The eye has a certain geometrical shape. If it can not be approximated by
    # an ellipse which major/minor < 0.8, ignore it.
    return True
    if len(contour) < 5:
        # Too tiny to be an eye
        return True
    ellipse = cv2.fitEllipse( contour )
    axes = ellipse[1]
    minor, major = axes
    if minor / major > threshold:
        # Cool, also the area of ellipse and contour area cannot ve very
        # different.
        cntArea = cv2.contourArea( contour )
        ellipseArea = np.pi * minor * major 
        if cntArea < 1:
            return False
        return True
    else:
        return False

def process_frame(frame):
    # Find edge in frame
    s = np.mean(frame)
    edges = cv2.Canny(frame, 50, 250)
    cnts = cv2.findContours(edges, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_TC89_KCOS)
    cntImg = np.ones(frame.shape)
    merge_contours(cnts[0], cntImg)

    # cool, find the contour again and convert again. Sum up their area.
    im = np.array((1-cntImg) * 255, dtype = np.uint8)
    cnts = cv2.findContours(im, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)

    hullImg = np.ones(frame.shape)
    res = []
    for c in cnts[0]:
        c = cv2.convexHull(c)
        if accept_contour_as_possible_eye( c ):
            cv2.fillConvexPoly(hullImg, c, 0, 8)
            res.append(cv2.contourArea(c))
    hullImg = np.array((1-hullImg) * 255, dtype = np.uint8)
    return frame, hullImg, sum(res), s

