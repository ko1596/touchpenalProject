import cv2
import time
import numpy as np
import sys
import os
from PIL import ImageFont, ImageDraw, Image

disign_platform = 0

if disign_platform:
    WORK_DIR_PATH = "/home/root/gproject/"         #work dir
else:
    WORK_DIR_PATH = "/home/user/JoeyLCD_DEV/touchpenalProject/src_py/"

if not os.path.isdir(WORK_DIR_PATH):
    print("Can't find dir" + WORK_DIR_PATH)
    
IMG_DIR_PATH = WORK_DIR_PATH + "image/"         #work dir
if not os.path.isdir(IMG_DIR_PATH):
    print("Can't find dir" + IMG_DIR_PATH)

FONT_PATH = WORK_DIR_PATH + "NotoSansCJKtc-Bold.otf"    #font file

if not os.path.isfile(FONT_PATH):
    print ("no font file found" + FONT_PATH)
    
GENERATED_IMG_NAME = WORK_DIR_PATH + "frame.jpg"        #output file name

class ParkBlock:

    def __init__(self, last_time, status, stop_time, name):
        self.last_time = last_time
        self.status = status
        self.stop_time = stop_time
        self.name = name

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
if not os.path.isfile(inputImg):
    print ("no image found")
    

img = cv2.imread(inputImg)

if sys.argv[1] != "0":
    if sys.argv[1] == "1":
        font_last_time = ImageFont.truetype(FONT_PATH, 105)
        font_stop_time = ImageFont.truetype(FONT_PATH, 55)
        font_block_name = ImageFont.truetype(FONT_PATH, 55)
        img_pil = Image.fromarray(img)
        draw = ImageDraw.Draw(img_pil)

        last_time = sys.argv[2]
        block_status = int(sys.argv[3])
        stop_time = sys.argv[4]
        block_name = sys.argv[5]

        if block_status == 1:
            info = cv2.imread(IMG_DIR_PATH + "wait_for_payment_selected.png")
            pasteImg(img, info, 202-info.shape[1]/2, 480)
        elif block_status == 2:
            info = cv2.imread(IMG_DIR_PATH + "deadline.png")

        w, h = draw.textsize(last_time, font_last_time)

        draw.text(((202-w / 2), (413)),  last_time, font = font_last_time, fill = (48, 48, 48, 0))

        img = np.array(img_pil)

    font = ImageFont.truetype(FONT_PATH, 55)
    img_pil = Image.fromarray(img)
    draw = ImageDraw.Draw(img_pil)
    text = time.strftime("%Y-%m-%d %H:%M", time.localtime())

    w, h = draw.textsize(text, font)

    draw.text(((img.shape[1]-w) / 2, (img.shape[0]-75)),  text, font = font, fill = (255, 255, 255, 0))

    img = np.array(img_pil)


cv2.imwrite(GENERATED_IMG_NAME, img)

if os.path.isfile(GENERATED_IMG_NAME):
    print("Generated image: " + GENERATED_IMG_NAME)
else:
    print("Cannot generated image")