import cv2
import time
import numpy as np
import sys
import os
from PIL import ImageFont, ImageDraw, Image

disign_platform = 1

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
        
        last_time = sys.argv[2]
        block_status = int(sys.argv[3])
        stop_time = sys.argv[4]
        block_name = sys.argv[5]

        last_time2 = sys.argv[6]
        block_status2 = int(sys.argv[7])
        stop_time2 = sys.argv[8]
        block_name2 = sys.argv[9]
        selectLR = int(sys.argv[10])

        leftHaveCar = int(sys.argv[11])
        rightHaveCar = int(sys.argv[12])

        
        font_last_time = ImageFont.truetype(FONT_PATH, 105)
        font_stop_time = ImageFont.truetype(FONT_PATH, 40)
        font_block_name = ImageFont.truetype(FONT_PATH, 35)

        if selectLR == 1: 
            selectLeftFontColor = (255, 255, 255,0)
            selectRightFontColor = (48,48,48,0)
        elif selectLR == 2:
            selectLeftFontColor = (48,48,48,0)
            selectRightFontColor = (255,255,255,0)
        else: 
            selectLeftFontColor = (48,48,48,0)
            selectRightFontColor = (48,48,48,0)

        min_line = 202
        min_line2 = 568

        if selectLR == 1: 
            selectBlock = cv2.imread(IMG_DIR_PATH + "main_screen_selected.png", -1)
            pasteImg(img, selectBlock, min_line-int(selectBlock.shape[1]/2), 375)
        elif selectLR == 2: 
            selectBlock = cv2.imread(IMG_DIR_PATH + "main_screen_selected.png", -1)
            pasteImg(img, selectBlock, min_line2-int(selectBlock.shape[1]/2), 375)
        
        if leftHaveCar:
            if block_status == 1:
                if selectLR == 1:
                    info = cv2.imread(IMG_DIR_PATH + "wait_for_payment_white.png", -1)
                else:
                    info = cv2.imread(IMG_DIR_PATH + "wait_for_payment.png", -1)

                pasteImg(img, info, min_line-int(info.shape[1]/2), 588)
            elif block_status == 2:
                if selectLR == 1:
                    info = cv2.imread(IMG_DIR_PATH + "deadline_white.png", -1)
                else:
                    info = cv2.imread(IMG_DIR_PATH + "deadline.png", -1)
                pasteImg(img, info, min_line-int(info.shape[1]/2), 588)
                img_pil = Image.fromarray(img)
                draw = ImageDraw.Draw(img_pil)
                w, h = draw.textsize(stop_time, font_stop_time)
                draw.text(((min_line-w / 2), (673)),  stop_time, font = font_stop_time, fill = selectLeftFontColor)
                img = np.array(img_pil)

        if rightHaveCar:
            if block_status2 == 1:
                if selectLR == 2:
                    info = cv2.imread(IMG_DIR_PATH + "wait_for_payment_white.png", -1)
                else:
                    info = cv2.imread(IMG_DIR_PATH + "wait_for_payment.png", -1)
                pasteImg(img, info, min_line2-int(info.shape[1]/2), 588)
            elif block_status2 == 2:
                if selectLR == 2:
                    info = cv2.imread(IMG_DIR_PATH + "deadline_white.png", -1)
                else:
                    info = cv2.imread(IMG_DIR_PATH + "deadline.png", -1)
                pasteImg(img, info, min_line2-int(info.shape[1]/2), 588)
                img_pil = Image.fromarray(img)
                draw = ImageDraw.Draw(img_pil)
                w, h = draw.textsize(stop_time2, font_stop_time)
                draw.text(((min_line2-w / 2), (673)),  stop_time2, font = font_stop_time, fill = selectRightFontColor)
                img = np.array(img_pil)
            

        img_pil = Image.fromarray(img)
        draw = ImageDraw.Draw(img_pil)

        if leftHaveCar:
            w, h = draw.textsize(block_name, font_block_name)
            draw.text(((min_line-w / 2), (775)),  block_name, font = font_block_name, fill = selectLeftFontColor)
            w, h = draw.textsize(last_time, font_last_time)
            draw.text(((min_line-w / 2), (413)),  last_time, font = font_last_time, fill = selectLeftFontColor)

        if rightHaveCar:
            w, h = draw.textsize(block_name2, font_block_name)
            draw.text(((min_line2-w / 2), (775)),  block_name2, font = font_block_name, fill = selectRightFontColor)
            w, h = draw.textsize(last_time2, font_last_time)
            draw.text(((min_line2-w / 2), (413)),  last_time2, font = font_last_time, fill = selectRightFontColor)

        img = np.array(img_pil)

    elif sys.argv[1] == "2":
        font = ImageFont.truetype(FONT_PATH, 40)
        font_getinTime = ImageFont.truetype(FONT_PATH, 30)

        img_pil = Image.fromarray(img)
        draw = ImageDraw.Draw(img_pil)
        payment = "¥ " + sys.argv[2]
        block_number = sys.argv[3]
        getinTime = sys.argv[4]

        w, h = draw.textsize(payment, font)
        draw.text((480-w/2 , (664)),  payment, font = font, fill = (48, 48, 48, 0))

        w, h = draw.textsize(block_number, font)
        draw.text((480-w/2 , (749)),  block_number, font = font, fill = (48, 48, 48, 0))

        w, h = draw.textsize(getinTime, font)
        draw.text((360 , 841),  getinTime, font = font_getinTime, fill = (126, 126, 126, 0))

        img = np.array(img_pil)
    
    elif sys.argv[1] == "3":
        font = ImageFont.truetype(FONT_PATH, 30)
        img_pil = Image.fromarray(img)
        draw = ImageDraw.Draw(img_pil)
        text = sys.argv[2]
        w, h = draw.textsize(text, font)
        draw.text(((img.shape[1]-w) / 2 , 775),  text, font = font, fill = (126, 126, 126, 0))
        img = np.array(img_pil)

    font = ImageFont.truetype(FONT_PATH, 30)
    img_pil = Image.fromarray(img)
    draw = ImageDraw.Draw(img_pil)
    text = time.strftime("%Y-%m-%d %H:%M", time.localtime())

    w, h = draw.textsize(text, font)

    draw.text(((img.shape[1]-w) / 2, (img.shape[0]-55)),  text, font = font, fill = (255, 255, 255, 0))

    img = np.array(img_pil)


cv2.imwrite(GENERATED_IMG_NAME, img)

if os.path.isfile(GENERATED_IMG_NAME):
    print("Generated image: " + GENERATED_IMG_NAME)
else:
    print("Cannot generated image")