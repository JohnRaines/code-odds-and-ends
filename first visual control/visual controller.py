'''
program that uses an object's position on a webcam
feed to control the speed of 4 fans

requires opencv

@author: John Raines
@created: 6 Feb. 2018
@last update: 6 Feb. 2018
'''

import cv2
import serial
import numpy as np
from collections import deque

ser = serial.Serial("COM6", 9600) #set up serial communication
s = [0]
cap = cv2.VideoCapture(0)         #acquire video signal
d =  deque()                      #holds the positions of the object
X = 1                             #x and y coordinates for object
Y = 1
PUSHER = 1



#function for isolating a certain coloured object
def ColorFilter(picture, low, high):
    mask = cv2.inRange(picture, low, high)
    mask = cv2.erode(mask, None, iterations = 3)
    return cv2.dilate(mask, None, iterations = 3)

#setup green colour mask
low_green = np.array([50,255,85])
hi_green = np.array([75,255,255])

#main
while(1):

    #get frame and convert to hsv
    _, frame = cap.read()
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    #adjust image saturation
    H,S,V = cv2.split(hsv)
    S.fill(255)
    hsv = cv2.merge([H,S,V])

    #filter by green 
    mask = ColorFilter(hsv, low_green, hi_green)
    res = cv2.bitwise_and(frame, frame, mask=mask)

    #find contours
    cnts = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[-2]
    #if contours found continue
    if len(cnts) > 0:
            c = max(cnts, key=cv2.contourArea) #find biggest contour
            ((x, y), radius) = cv2.minEnclosingCircle(c)
            X = int(x)
            Y = int(y)
            M = cv2.moments(c)
            center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))
            d.appendleft(center)

            #draw cirlce 1
            cv2.circle(frame, (int(x), int(y)), int(radius),(0, 255, 0), 2)

    #serial write
    PUSHER = (X * 65536)  + Y
    PUSHER = int(PUSHER)
    #ser.write(1);
    ser.write(X)
    #ser.write(int(Y))
            
    #center display
    text = str(int(X)) + " " + str(int(Y))
    cv2.putText(frame,text,(0,200),cv2.FONT_HERSHEY_COMPLEX,1,(255,0,255),2)

    cv2.imshow('original', frame)
    cv2.imshow('res',res)

    k = cv2.waitKey(5) & 0xFF
    if k==27:
        break

cv2.destroyAllWindows()
cap.release()


    
