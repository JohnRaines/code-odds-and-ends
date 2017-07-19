import cv2
import numpy as np
import array
from collections import deque 

cap = cv2.VideoCapture(1)
d = deque()
X = 0
Y = 0
XVEL = 0
YVEL = 0

while(1):

        #get frame and convert it to hsv
        _, frame = cap.read()
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

        #set our upper and lower green values
        low_green = np.array([50,255,85])
        hi_green = np.array([250,255,255])

        #adjust image saturation
        H,S,V = cv2.split(hsv)
        S.fill(255)
        hsv = cv2.merge([H,S,V])
        #hsv = cv2.cvtColor(hsv, cv2.COLOR_HSV2BGR)
        
        #filter by colour and smooth the image
        mask = cv2.inRange(hsv, low_green, hi_green)
        mask = cv2.erode(mask, None, iterations=3)
        mask = cv2.dilate(mask, None, iterations=3)
        res = cv2.bitwise_and(frame, frame, mask=mask)

        #find contours
        cnts = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[-2]

        #if contours found continue
        if len(cnts) > 0:
                c = max(cnts, key=cv2.contourArea) #find biggest contour
                ((x, y), radius) = cv2.minEnclosingCircle(c)
                X = x
                Y = y
                M = cv2.moments(c)
                center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))
                d.appendleft(center)
                
                #draw the circle
                cv2.circle(frame, (int(x), int(y)), int(radius),(255, 0, 0), 2)

        #display coordinate and velocities
        text = str(int(X)) + " " + str(int(Y))
        cv2.putText(frame,text,(0,100),cv2.FONT_HERSHEY_COMPLEX,1,(0,255,255),2)
        cv2.putText(frame,str(XVEL),(0,400),cv2.FONT_HERSHEY_COMPLEX,1,(0,255,255),2)
        cv2.putText(frame,str(YVEL),(0,450),cv2.FONT_HERSHEY_COMPLEX,1,(0,255,255),2)

        #trace line and get velocity
        for i in range(1, len(d)):
                if d[i-1] is None or d[i] is None:
                        continue
                ptA = d[i-1] #pull the points into holders
                ptB= d[i]
                cv2.line(frame, ptA, ptB, (0, 0, 255), 5) #line connecting points
                XVEL = ptB[0] - ptA[0] #calculate X and Y velocity
                YVEL = ptB[1] - ptA[1]
                d.pop()

        
	
        #displays
        cv2.imshow('original', frame)
        cv2.imshow('mask', mask)
        cv2.imshow('res', res)
        cv2.imshow('saturated', cv2.cvtColor(hsv, cv2.COLOR_HSV2BGR))

        k = cv2.waitKey(5) & 0xFF
        if k==27:
            break

cv2.destroyAllWindows()
cap.release()
