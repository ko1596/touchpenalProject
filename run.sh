#!/bin/bash
scp serial.c gpio_dev.c gpio_dev.h displayLCD.c displayLCD.h spi_8MM_driver.c spi_8MM_driver.h user@192.168.1.200:/home/user/yocto_imx8/sdk/JoeyLCD_DEV/touchPenal
scp frame.py root@192.168.1.146:/home/root/touchPenalProject