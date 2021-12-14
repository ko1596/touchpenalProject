import numpy as np
import cv2
import sys

SCREEN_WEIDTH = 1200
SCREEN_HEIGHT = 1600
BLOCK_WRIDTH = 260
BLOCK_HEIGHT = 290
b,g,r,a = 0,0,0,0

img = np.zeros((SCREEN_HEIGHT,SCREEN_WEIDTH,3),np.uint8)
img[:] = (255, 255, 255)
x = 0
y = 0
for i in sys.argv[1:]:
    cv2.rectangle(img, (10 + y*BLOCK_HEIGHT+10, 10 + x*BLOCK_WRIDTH+10), (10 + y*BLOCK_HEIGHT + BLOCK_HEIGHT, 10 + x*BLOCK_WRIDTH + BLOCK_WRIDTH), (0, 0, int(i)/40000*255), -1)
    x = x + 1
    if x == 6:
        x = 0
        y = y + 1
    

img = img[::-1]
cv2.imwrite("frame.bmp", img)