import cv2
import numpy as np

def nothing(x):
    pass

cv2.namedWindow('Trackbars')

cv2.createTrackbar('Hue lower','Trackbars',0,179,nothing)
cv2.createTrackbar('Sat lower','Trackbars',0,255,nothing)
cv2.createTrackbar('Val lower','Trackbars',0,255,nothing)
cv2.createTrackbar('Hue upper','Trackbars',0,179,nothing)
cv2.createTrackbar('Sat upper','Trackbars',0,255,nothing)
cv2.createTrackbar('Val upper','Trackbars',0,255,nothing)

cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    if not ret:
        break

    hue_low = cv2.getTrackbarPos('Hue lower','Trackbars')
    sat_low = cv2.getTrackbarPos('Sat lower','Trackbars')
    val_low = cv2.getTrackbarPos('Val lower','Trackbars')
    hue_up = cv2.getTrackbarPos('Hue upper','Trackbars')
    sat_up = cv2.getTrackbarPos('Sat upper','Trackbars')
    val_up = cv2.getTrackbarPos('Val upper','Trackbars')

    lower = np.array([hue_low, sat_low, val_low])
    upper = np.array([hue_up, sat_up, val_up])

    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    mask = cv2.inRange(hsv, lower, upper)
    result = cv2.bitwise_and(frame, frame, mask=mask)

    cv2.imshow('Original', frame)
    cv2.imshow('Mask', mask)
    cv2.imshow('Result', result)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()