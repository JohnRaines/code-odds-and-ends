import cv2
import numpy as np
import array
from collections import deque
import math
from PID import PID

'''
inecusable number of global variables X
'''
cap = cv2.VideoCapture(0) #video signal
d = deque()               #3 deques for storing positions of all objects
d2 = deque()
d3 = deque()
X1 = 1                    #X1Y1 Green object
Y1 = 1
X2 = 2                    #X2Y2 blue object
Y2 = 2
X3 = 3                    #X3Y3 purple object
Y3 = 3
Xa = 0                    #a and b sets are the derived corners of the square
Ya = 0
Xb = 0
Yb = 0
K = 0                     #k is a constant used to determine corners
SIDE = 0                  #Length of a side of the square
SLOPE = 0                 #slope of the line defined by the blue and green points
NSLOPE = 0                #slope normal to SLOPE
XDIS = 1                  #X and Y disstance from the top and sides 
YDIS = 1
CENTERX = 0               #X and Y coordinates for center of the square
CENTERY = 0
ERRORX = 0
ERRORY = 0
PIDX = 0
PIDY = 0


'''
Tonnes of functions
'''
#function for finding the distance from point 3 to the line created by points
#1 and 2
def distance(xa, ya, xb, yb, xi, yi):
        y1 = -ya
        y2 = -yb
        y3 = -yi
        
        numer = ((y2-y1)*xi)-((xb-xa)*y3)+(xb*y1)-(y2*xa)
        denom = ((y2-y1)**2) + ((xb-xa)**2)
        return ((abs(numer))/(math.sqrt(denom)))

#Finds the x and y position error
def errorfinder():
        global ERRORX, ERRORY
        ERRORX = CENTERX - X3
        ERRORY = CENTERY - Y3
        

#finds the length of one side of the square
def sidefinder():
        global SIDE
        SIDE = math.sqrt((X2-X1)**2 + (Y2-Y1)**2)

#finds the slope and normal slope of that side
def slopefinder():
        global SLOPE, NSLOPE
        SLOPE = (Y2-Y1)/(X2-X1)

        if(SLOPE == 0):
                NSLOPE = 0
        else:
                NSLOPE = (-1/ SLOPE)

        
#finds the factor for generating lines of the same length
def kfinder():
        global K
        K =(SIDE / (math.sqrt(1 + NSLOPE**2)))


#finds all the points of the square
def squarefinder():
        global Xa, Ya, Xb, Yb, CENTERX, CENTERY
        slopefinder()
        sidefinder()
        kfinder()
        Xa = X1 + K * np.sign(SLOPE)
        Ya = Y1 - abs(K * NSLOPE)
        Xb = X2 + K * np.sign(SLOPE)
        Yb = Y2 - abs(K * NSLOPE)
        CENTERX = ((X1 + X2) / 2) + K * np.sign(SLOPE)/2
        CENTERY = ((Y1 + Y2) / 2) - abs(K * NSLOPE)/2
        #update goal points

        cv2.line(frame, (int(X1),int(Y1)), (int(X2),int(Y2)), (0, 0, 255), 5)
        cv2.line(frame, (int(X1),int(Y1)), (int(Xa),int(Ya)), (0, 0, 255), 5)
        cv2.line(frame, (int(Xb),int(Yb)), (int(X2),int(Y2)), (0, 0, 255), 5)
        cv2.line(frame, (int(Xa),int(Ya)), (int(Xb),int(Yb)), (0, 0, 255), 5)
        cv2.circle(frame, (int(CENTERX), int(CENTERY)), int(1),(0, 255, 0), 2)

#filter an image using input hsv values        
def ColorFilter(picture, low, high):
        mask = cv2.inRange(picture, low, high)
        mask = cv2.erode(mask, None, iterations=3)
        return cv2.dilate(mask, None, iterations=3)

#get pid output
PIDX = pid.GenOut(ERRORX)
PIDY = pid.GenOut(ERRORY)


'''
inits
'''
#set our upper and lower color values
low_green = np.array([50,255,85])
hi_green = np.array([75,255,255])

low_blue = np.array([80,255,85])
hi_blue = np.array([120,255,255])

low_purp = np.array([150,255,85])
hi_purp = np.array([200,255,255])

#intialize pid
pid = PID()
pid.SetKp(1)
pid.SetKd(1)
pid.SetKi(1)
pid.Initialize()

'''
"main"
'''
while(1):

        #get frame and convert it to hsv
        _, frame = cap.read()
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)


        #adjust image saturation
        H,S,V = cv2.split(hsv)
        S.fill(255)
        hsv = cv2.merge([H,S,V])
        
        #filter by green 
        mask = ColorFilter(hsv, low_green, hi_green)
        res = cv2.bitwise_and(frame, frame, mask=mask)

        #filter by blue 
        mask2 = ColorFilter(hsv, low_blue, hi_blue)
        res2 = cv2.bitwise_and(frame, frame, mask=mask2)

        #filter by purple 
        mask3 = ColorFilter(hsv, low_purp, hi_purp)
        res3 = cv2.bitwise_and(frame, frame, mask=mask3)


        #find contours
        cnts = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[-2]
        cnts2 = cv2.findContours(mask2.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[-2]
        cnts3 = cv2.findContours(mask3.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[-2]

        #if contours found continue
        if len(cnts) > 0:
                c = max(cnts, key=cv2.contourArea) #find biggest contour
                ((x, y), radius) = cv2.minEnclosingCircle(c)
                X1 = x
                Y1 = y
                M = cv2.moments(c)
                center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))
                d.appendleft(center)

                #draw cirlce 1
                cv2.circle(frame, (int(x), int(y)), int(radius),(0, 255, 0), 2)

        if len(cnts2) > 0:
                c = max(cnts2, key=cv2.contourArea) #find biggest contour
                ((x, y), radius) = cv2.minEnclosingCircle(c)
                X2 = x
                Y2 = y
                M = cv2.moments(c)
                center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))
                d2.appendleft(center)
                
                #draw circle  2
                cv2.circle(frame, (int(x), int(y)), int(radius),(255, 0, 0), 2)

        if len(cnts3) > 0:
                c = max(cnts3, key=cv2.contourArea) #find biggest contour
                ((x, y), radius) = cv2.minEnclosingCircle(c)
                X3 = x
                Y3 = y
                M = cv2.moments(c)
                center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))
                d3.appendleft(center)
                
                #draw circle  3
                cv2.circle(frame, (int(x), int(y)), int(radius),(0, 0, 255), 2)
                cv2.circle(frame, (int(x), int(y)), int(1),(0, 0, 255), 2)

        #draw the square
        squarefinder()

        #get the displacements
        XDIS = distance(X1,Y1,Xa,Ya,X3,Y3)
        YDIS = distance(Xa,Ya,Xb,Yb,X3,Y3)
        
        
        ########display coordinate and velocities
        text = str(int(X1)) + " " + str(int(Y1))
        text2 = str(int(XDIS)) + " " + str(int(YDIS))
        cv2.putText(frame,text2,(0,200),cv2.FONT_HERSHEY_COMPLEX,1,(255,0,255),2)
        cv2.line(frame, (int(X1),int(Y1)), (int(X2),int(Y2)), (0, 0, 255), 5) #line connecting points
                 	
        #displays
        cv2.imshow('original', frame)
        cv2.imshow('res', res)
        cv2.imshow('res2', res2)
        cv2.imshow('res3', res3)

        k = cv2.waitKey(5) & 0xFF
        if k==27:
            break

cv2.destroyAllWindows()
cap.release()





