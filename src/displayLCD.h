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

#include "gstService.h"

#define WORK_SPACE_DIR "python3 /home/root/touchPenalProject/frame.py "
#define COMMAND_PATH "/home/root/touchPenalProject/"

int lock;
pthread_t displayThread; // 宣告 pthread 變數



void displayFrame(void *parm);
void initLCD(void);

/**
 * @brief Create a fork to display the page of the status
 * 
 */
void *display(void *);

 #endif /* DISPLAY_LCD_H */