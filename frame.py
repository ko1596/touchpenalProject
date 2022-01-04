import numpy as np
import cv2
import sys

SCREEN_WEIDTH = 1200
SCREEN_HEIGHT = 1600
BLOCK_WRIDTH = 260
BLOCK_HEIGHT = 290

def pasteImg(img, overlay, x, y):
    y1, y2 = y, y + overlay.shape[0]
    x1, x2 = x, x + overlay.shape[1]

    alpha_s = overlay[:, :, 3] / 255.0
    alpha_l = 1.0 - alpha_s

    for c in range(0, 3):
        img[y1:y2, x1:x2, c] = (alpha_s * overlay[:, :, c] +
                                alpha_l * img[y1:y2, x1:x2, c])



b,g,r,a = 0,0,0,0



img = np.zeros((SCREEN_HEIGHT,SCREEN_WEIDTH,3),np.uint8)
img[:] = (255, 255, 255)
x = 0
y = 0
for i in sys.argv[1:]:
    if int(i) > 60000:
        distance = 0
    else:
        distance = int(i)
    cv2.rectangle(img, (10 + y*BLOCK_HEIGHT+10, 10 + x*BLOCK_WRIDTH+10), (10 + y*BLOCK_HEIGHT + BLOCK_HEIGHT, 10 + x*BLOCK_WRIDTH + BLOCK_WRIDTH), (0, 0, distance/30000*255), -1)
    x = x + 1
    if x == 6:
        x = 0
        y = y + 1
    

img = img[::-1]
cv2.imwrite("frame.png", img)