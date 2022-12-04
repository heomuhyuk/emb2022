#pragma once
#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <stdio.h>
#include <stdlib.h>    // for exit
#include <unistd.h>    // for open/close
#include <fcntl.h>     // for O_RDWR
#include <sys/ioctl.h> // for ioctl
#include <sys/kd.h>    // for remove cursor
#include <sys/mman.h>
#include <linux/fb.h> // for fb_var_screeninfo, FBIOGET_VSCREENINFO

#define FBDEV_FILE0 "/dev/fb0"
#define FBDEV_FILE1 "/dev/fb1"

int display_init(void);
int draw_background(int color, int idx_buffer);
int draw_square(int der_x, int der_y, int dX, int dY, int color, int idx_buffer);
int draw_bmp_menu(void);
int draw_bmp_win(void);
int draw_bmp_fail(void);
int display_close(void);

#endif