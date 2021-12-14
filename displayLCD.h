/**
  ******************************************************************************
  * File Name          : displayLCD.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  *
  * COPYRIGHT(c) 2021 Joey Ke
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef DISPLAY_LCD_H
#define DISPLAY_LCD_H
/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <fcntl.h>
#include <time.h>
#include <pthread.h>
#include <sys/ioctl.h>
#include <linux/ioctl.h>
#include <linux/input.h>
#include <sys/stat.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <linux/gpio.h>
#include "gpio_dev.h"
#include "spi_8MM_driver.h"

#define ROW_BYTE_NUM (1600 * 3)

#define GPIO_DCX 6
#define GPIO_RESX 7
#define GPIO_CSX 8

int lock;

void LCD_WrCmd(unsigned char cmd);
void LCD_WrDat(unsigned char dat);
void LCD_SetCmd1(unsigned char cmd, unsigned char dat);
void LCD_SetCmd2(unsigned char cmd, unsigned char dat1, unsigned char dat2);
void LCD_SetCmd3(unsigned char cmd, unsigned char dat1, unsigned char dat2, unsigned char dat3);
void LCD_SetCmd4(unsigned char cmd, unsigned char dat1, unsigned char dat2, unsigned char dat3, unsigned char dat4);
void LCD_Image(unsigned char data[]);
void displayFrame(void *parm);
void initLCD();
void LCD_Init(void);

 #endif /* DISPLAY_LCD_H */