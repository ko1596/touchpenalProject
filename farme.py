import numpy as np
from PIL import ImageFont, ImageDraw, Image
import cv2
import sys

# for i in sys.argv:
#     print(i)

# # argc
# argc = len(sys.argv)
# print(argc)

SCREEN_WEIDTH = 1600
SCREEN_HEIGHT = 1200
b,g,r,a = 0,0,0,0

img = np.zeros((SCREEN_HEIGHT,SCREEN_WEIDTH,3),np.uint8)
img[:] = (255, 255, 255)
cv2.rectangle(img, (0, 0), (1600, 250), (0, 0, 0), -1)
cv2.rectangle(img, (1075, 0), (1600, 250), (0, 0, 255), -1)
cv2.rectangle(img, (0, 250), (1600, 420), (255, 0, 0), -1)

fontpath = "./NotoSansCJKtc-Light.otf"
font = ImageFont.truetype(fontpath, 200)
img_pil = Image.fromarray(img)
draw = ImageDraw.Draw(img_pil)
draw.text((500, 500),  "aaaa", font = font, fill = (0, 0, 0, a))
img = np.array(img_pil)

cv2.imwrite("time.bmp", img)