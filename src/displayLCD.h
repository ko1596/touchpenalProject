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

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define WORK_SPACE_DIR "python3 /home/root/gproject/frame.py "
#define COMMAND_PATH "/home/root/gproject/"

/** @defgroup Radar_PredictionStatus_group Defines Prediction Status
 *  Defines all possible prediction status mode
 *  @{
 */
typedef uint8_t Block_Status;

#define BLOCK_EMPTY       ((Block_Status)  0)
#define BLOCK_PAYMENT     ((Block_Status)  1)
#define BLOCK_DEADLINE    ((Block_Status)  2)
/** @} Radar_PredictionStatus_group */

typedef struct Block_Data_t
{
  uint8_t timeHour;
  uint8_t timeMinute;

  Block_Status blockStatus;

  uint8_t stopTimeMonth;
  uint8_t stopTimeDay;
  uint8_t stopTimeHour;
  uint8_t stopTimeMinute;

  char blockName[8];
} Block_Data_t;

uint8_t payment;

Block_Data_t BlockDataLeft;
Block_Data_t BlockDataRight;
uint8_t selectBlockLR;

uint8_t leftHaveCar;
uint8_t rightHaveCar;

/** @defgroup Radar_PredictionStatus_group Defines Prediction Status
 *  Defines all possible prediction status mode
 *  @{
 */
typedef uint8_t Page_Status;

#define PAGE_HOMEPAGE                     ((Page_Status)  0)
#define PAGE_BLOCK_SELECT_PAGE            ((Page_Status)  1)
#define PAGE_PAYMENT_PAGE                 ((Page_Status)  2)
#define PAGE_SUCCESS_PAGE                 ((Page_Status)  3)
#define PAGE_PAYMENT_FAIL_PAGE            ((Page_Status)  4)
#define PAGE_PAYMENT_CONNECTION_PAGE      ((Page_Status)  5)
#define PAGE_CONNECTION_FAIL_PAGE         ((Page_Status)  6)
#define PAGE_FREE_PARKING_PAGE            ((Page_Status)  7)
#define PAGE_NO_PARKING_PAGE              ((Page_Status)  8)
#define PAGE_Blank_PAGE                   ((Page_Status)  9)
/** @} Radar_PredictionStatus_group */

Page_Status pageStatus;

void initData(void);

void generateFrame(void);

 #endif /* DISPLAY_LCD_H */