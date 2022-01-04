import cv2
import time
import numpy as np
import sys
import os
from PIL import ImageFont, ImageDraw, Image

disign_platform = 0

if disign_platform:
    WORK_DIR_PATH = "/home/root/touchPenalProject/"         #work dir
else:
    WORK_DIR_PATH = "/home/user/JoeyLCD_DEV/touchpenalProject/src_py/"

if os.path.isdir(WORK_DIR_PATH):
    print("set work dir: " + WORK_DIR_PATH)
else:
    print("Can't find dir" + WORK_DIR_PATH)

IMG_DIR_PATH = WORK_DIR_PATH + "image/"         #work dir
if os.path.isdir(IMG_DIR_PATH):
    print("set work dir: " + IMG_DIR_PATH)
else:
    print("Can't find dir" + IMG_DIR_PATH)


FONT_PATH = WORK_DIR_PATH + "NotoSansCJKtc-Bold.otf"    #font file

if os.path.isfile(FONT_PATH):
    print ("reading font: " + FONT_PATH)
else:
    print ("no font file found" + FONT_PATH)
GENERATED_IMG_NAME = WORK_DIR_PATH + "frame.jpg"        #output file name
print("setting output file path: " + GENERATED_IMG_NAME)

if os.path.isfile(GENERATED_IMG_NAME):
    os.remove(GENERATED_IMG_NAME)
    print("File removed successfully")

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

inputImg = IMG_DIR_PATH + sys.argv[1] +".png"
if os.path.isfile(inputImg):
    print ("reading image: " + inputImg)
else:
    print ("no image found")

img = cv2.imread(inputImg)

if sys.argv[1] != "0":
    if sys.argv[1] == "1":
        selectBlockNum = int(sys.argv[2])
        selectBlockImg = cv2.imread(IMG_DIR_PATH + "SELECT_PARKING_SPACE.png", -1)

        pasteImg(img, selectBlockImg, int(selectBlockNum / 4) * 285 + 14, int(selectBlockNum % 4) * 130 + 14)


    font = ImageFont.truetype(FONT_PATH, 30)
    img_pil = Image.fromarray(img)
    draw = ImageDraw.Draw(img_pil)
    text = time.strftime("%Y-%m-%d %H:%M", time.localtime())

    w, h = draw.textsize(text, font)

    draw.text(((img.shape[1]-w)/2, (img.shape[0]-50)),  text, font = font, fill = (255, 255, 255, 0))

    img = np.array(img_pil)

cv2.imwrite(GENERATED_IMG_NAME, img)

if os.path.isfile(GENERATED_IMG_NAME):
    print("Generated image: " + GENERATED_IMG_NAME)
else:
    print("Cannot generated image")