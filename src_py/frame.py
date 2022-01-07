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

if not os.path.isdir(WORK_DIR_PATH):
    print("Can't find dir" + WORK_DIR_PATH)
    
IMG_DIR_PATH = WORK_DIR_PATH + "image/"         #work dir
if not os.path.isdir(IMG_DIR_PATH):
    print("Can't find dir" + IMG_DIR_PATH)

FONT_PATH = WORK_DIR_PATH + "NotoSansCJKtc-Bold.otf"    #font file

if not os.path.isfile(FONT_PATH):
    print ("no font file found" + FONT_PATH)
    
GENERATED_IMG_NAME = WORK_DIR_PATH + "frame.jpg"        #output file name

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
if not os.path.isfile(inputImg):
    print ("no image found")
    

img = cv2.imread(inputImg)

if sys.argv[1] != "0":
    if sys.argv[1] == "1":
        selectBlockNum = int(sys.argv[2])
        selectBlockImg = cv2.imread(IMG_DIR_PATH + "select_parking_space_frame.png", -1)

        pasteImg(img, selectBlockImg, int(selectBlockNum % 2) * 600 + 20, int(selectBlockNum / 2) * 270 + 30)
        for i in range(8):
            if sys.argv[i+3] != "0":                
                if sys.argv[i+3] == "1":
                        showblock = cv2.imread(IMG_DIR_PATH + "waiting_for_payment.png", -1)
                elif sys.argv[i+3] == "2":
                    showblock = cv2.imread(IMG_DIR_PATH + "expired.png", -1)
                elif sys.argv[i+3] == "3":
                    showblock = cv2.imread(IMG_DIR_PATH + "deadline.png", -1)

                pasteImg(img, showblock, int(i / 4) * 600 + 260, int(i % 4) * 270 + 100)
            
        font = ImageFont.truetype(FONT_PATH, 45)
        img_pil = Image.fromarray(img)
        draw = ImageDraw.Draw(img_pil)
        text = sys.argv[11]
        w, h = draw.textsize(text, font)
        draw.text(((img.shape[1]-w)/2, (img.shape[0]-220)),  sys.argv[11], font = font, fill = (49, 49, 49, 0))
        img = np.array(img_pil)
    if sys.argv[1] == "2":
        font = ImageFont.truetype(FONT_PATH, 100)
        img_pil = Image.fromarray(img)
        draw = ImageDraw.Draw(img_pil)
        text = str(int(sys.argv[2])*0.5)
        w, h = draw.textsize(text, font)
        draw.text((775-w/2, (676)),  text, font = font, fill = (49, 49, 49, 0))
        w, h = draw.textsize(sys.argv[3], font)
        draw.text((775-w/2, (935)),  sys.argv[3], font = font, fill = (49, 49, 49, 0))
        img = np.array(img_pil)

        if sys.argv[4] == "1":
            leftButton = cv2.imread(IMG_DIR_PATH + "decrease_button.png", -1)
            pasteImg(img, leftButton, 580, 715)
        elif sys.argv[4] == "2":
            rightButton = cv2.imread(IMG_DIR_PATH + "increase_button.png", -1)
            pasteImg(img, rightButton, 888, 715)

        if sys.argv[5] == "1":
            selectedButtons = cv2.imread(IMG_DIR_PATH + "back_button.png", -1)
            pasteImg(img, selectedButtons, 250, 1269)
        elif sys.argv[5] == "2":
            selectedButtons = cv2.imread(IMG_DIR_PATH + "confirm_button.png", -1)
            pasteImg(img, selectedButtons, 678, 1269)
        
    if sys.argv[1] == "7":
        font = ImageFont.truetype(FONT_PATH, 40)
        img_pil = Image.fromarray(img)
        draw = ImageDraw.Draw(img_pil)
        text = "$ "+ str(int(sys.argv[2])*4)
        w, h = draw.textsize(text, font)
        draw.text((275-w/2, (545)),  text, font = font, fill = (49, 49, 49, 0))
        w, h = draw.textsize(sys.argv[3], font)
        draw.text((575-w/2, (545)),  sys.argv[3], font = font, fill = (49, 49, 49, 0))
        text = str(int(sys.argv[2])*0.5)
        w, h = draw.textsize(text, font)
        draw.text((895-w/2, (545)),  text, font = font, fill = (49, 49, 49, 0))
        img = np.array(img_pil)

        if sys.argv[4] == "1":
            back_button = cv2.imread(IMG_DIR_PATH + "back.png", -1)
            pasteImg(img, back_button, 458, 1315)

    if sys.argv[1] == "8":
        font = ImageFont.truetype(FONT_PATH, 40)
        img_pil = Image.fromarray(img)
        draw = ImageDraw.Draw(img_pil)
        text = "$ "+ str(int(sys.argv[2])*4)
        w, h = draw.textsize(text, font)
        draw.text((275-w/2, (583)),  text, font = font, fill = (49, 49, 49, 0))
        w, h = draw.textsize(sys.argv[3], font)
        draw.text((575-w/2, (583)),  sys.argv[3], font = font, fill = (49, 49, 49, 0))
        text = str(int(sys.argv[2])*0.5)
        w, h = draw.textsize(text, font)
        draw.text((895-w/2, (583)),  text, font = font, fill = (49, 49, 49, 0))
        img = np.array(img_pil)

        if sys.argv[4] == "1":
            back_button = cv2.imread(IMG_DIR_PATH + "back.png", -1)
            pasteImg(img, back_button, 458, 1284)

    if sys.argv[1] == "9":
        if sys.argv[2] == "1":
            back_button = cv2.imread(IMG_DIR_PATH + "back_to_main_screen.png", -1)
            pasteImg(img, back_button, 438, 1300)
    
    if sys.argv[1] == "10":
        if sys.argv[2] == "1":
            back_button = cv2.imread(IMG_DIR_PATH + "back_to_main_screen.png", -1)
            pasteImg(img, back_button, 438, 1338)

        


    font = ImageFont.truetype(FONT_PATH, 55)
    img_pil = Image.fromarray(img)
    draw = ImageDraw.Draw(img_pil)
    text = time.strftime("%Y-%m-%d %H:%M", time.localtime())

    w, h = draw.textsize(text, font)

    draw.text((20, (img.shape[0]-90)),  text, font = font, fill = (255, 255, 255, 0))
    text = "00000001"
    w, h = draw.textsize(text, font)
    draw.text((img.shape[1] - w - 20, (img.shape[0]-90)),  text, font = font, fill = (255, 255, 255, 0))

    img = np.array(img_pil)


# for c in range(1, 4):
#     cv2.line(img, (300 * c, 0), (300 * c, 1600), (0, 0, 255), 5)

# for c in range(1, 6):
#     cv2.line(img, (0, 267 * c), (1200, 267 * c), (0, 0, 255), 5)

cv2.imwrite(GENERATED_IMG_NAME, img)

if os.path.isfile(GENERATED_IMG_NAME):
    print("Generated image: " + GENERATED_IMG_NAME)
else:
    print("Cannot generated image")