#include "game.h"
#include "draw.h"
#include "highscores.h"
#include <Tinyfont.h>

const unsigned char background[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x38, 0x18, 0x8, 0x8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x60, 0xe0, 0xe0, 0xe0, 0xc0, 0xa0, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0xa0, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0x60, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8, 0x8, 0x8, 0x18, 0x38, 0x38, 0x38, 0x38, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4, 0x4, 0xc, 0x1c, 0x1c, 0x1c, 0x3c, 0x3c, 0x3c, 0x38, 0x74, 0x6c, 0x6c, 0x6c, 0x6c, 0x6c, 0x6c, 0x6c, 0x6c, 0x74, 0x38, 0x3c, 0x9c, 0x8c, 0x84, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xf, 0xf, 0xf, 0xf, 0xf, 0xe, 0xd, 0xd, 0xd, 0xd, 0xd, 0xd, 0xd, 0xd, 0xe, 0xf, 0xf, 0xf, 0xf, 0xf, 0x7, 0x3, 0x3, 0x3, 0x3, 0x3, 0x1, 0x1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1, 0x3, 0x7, 0x7, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x1, 0x1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x86, 0x46, 0x86, 0x46, 0x86, 0x46, 0x86, 0x46, 0x86, 0x46, 0x86, 0x46, 0x86, 0x46, 0x86, 0x46, 0x86, 0x46, 0x86, 0x46, 0x86, 0x46, 0x86, 0x46, 0x86, 0x46, 0x86, 0x4e, 0x9e, 0x7e, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfc, 0xfa, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xfa, 0xfc, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x7e, 0x9e, 0x4e, 0x86, 0x46, 0x86, 0x46, 0x86, 0x46, 0x86, 0x46, 0x86, 0x46, 0x86, 0x46, 0x86, 0x46, 0x86, 0x46, 0x86, 0x46, 0x86, 0x46, 0x86, 0x46, 0x86, 0x46, 0x86, 0x46, 0x86, 
};

const unsigned char title[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xf0, 0x10, 0x00, 0x00, 0xe0, 0xe0, 0xc0, 0xc0, 0xc0, 0xe0, 0xe0, 0x30, 0xc0, 0xf0, 0xf0, 0xfc, 0xfc, 0xfc, 0xfc, 0x7c, 0x7c, 0x78, 0x78, 0xf8, 0xf8, 0xf0, 0xf0, 0xe0, 0xe0, 0xe0, 0xc0, 0x00, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xf0, 0xf0, 0xfc, 0xfc, 0xfe, 0xde, 0xce, 0xc0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0xe0, 0xf8, 0xf8, 0xf8, 0xf0, 0xf0, 0xe0, 0xe0, 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xf8, 0x00, 0x00, 0x80, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xfe, 0xfe, 0xfc, 0xfc, 0xfc, 0xf8, 0xc0, 0x9f, 0x3f, 0xf, 0xe7, 0xfb, 0xff, 0xff, 0x3f, 0x7, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xf, 0xf0, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xf1, 0xe0, 0xc0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x1, 0x3, 0xf, 0x1f, 0x3f, 0x7f, 0xff, 0x3c, 0x3, 0xf, 0x87, 0xf3, 0xfd, 0xff, 0xff, 0x3f, 0x1f, 0x7, 0x1, 0x3, 0x7, 0x7, 0x7, 0xc7, 0xe3, 0xf1, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xf, 0x7, 0xf9, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x3f, 0x1f, 0x1f, 0x3f, 0x3f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x7c, 0x9b, 0xe7, 0xff, 0xff, 0xff, 0xf, 0x6, 0xc0, 0xf0, 0xf8, 0xf8, 0x70, 0x60, 0xf0, 0xf8, 0xf8, 0x7c, 0x7c, 0x3f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf9, 0x60, 0x80, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3, 0x1, 0x00, 0x1, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc3, 0xff, 0xff, 0xff, 0x80, 0x00, 0x3, 0x7, 0x7, 0xf, 0x1f, 0x3f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfc, 0xf8, 0xf0, 0xf0, 0xe0, 0xc0, 0x80, 0x00, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x7, 0x3, 0x1, 0x00, 0x00, 0x00, 0x1f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xf8, 0xf8, 0xf0, 0xe0, 0xc0, 0x80, 0x61, 0xfb, 0xf7, 0xfb, 0xfc, 0xff, 0xff, 0xbf, 0x3, 0x80, 0xf0, 0xfe, 0xff, 0x7f, 0xf, 0x3, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x1, 0x7, 0xff, 0xff, 0xff, 0xc0, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x83, 0xff, 0xff, 0xff, 0xff, 0x80, 0x7f, 0xff, 0xff, 0xff, 0xff, 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x70, 0xe0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x1, 0x3, 0x3, 0x7, 0xf, 0xf, 0x1f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xfc, 0xe3, 0x1f, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x80, 0x00, 0x1, 0x1, 0x3, 0x3, 0x7, 0xf, 0x1f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xf3, 0x8f, 0x7f, 0xff, 0xf, 0x1f, 0x7f, 0xff, 0xff, 0xff, 0xc3, 0x00, 0x00, 0x00, 0x00, 0x4, 0xc, 0x1e, 0x3f, 0x7f, 0xff, 0xfe, 0xf8, 0xf8, 0xf8, 0xff, 0xff, 0x7f, 0x3f, 0xf, 0x00, 0x7, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xc0, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xf0, 0xc0, 0x81, 0xf, 0x7f, 0xff, 0xff, 0xff, 0xfc, 0xfc, 0xf8, 0xf0, 0xe0, 0xe0, 0xe0, 0xf0, 0xf0, 0xfc, 0xff, 0xff, 0x7f, 0x9f, 0xe3, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xe0, 0xe0, 0xe0, 0xf0, 0xf7, 0xf9, 0xfe, 0xfe, 0x1, 0xff, 0xff, 0xff, 0xfe, 0xf8, 0xf0, 0xc0, 0x00, 0x80, 0x81, 0xe7, 0xff, 0xfc, 0xf8, 0xf0, 0xf0, 0xe0, 0xe0, 0xf0, 0xf8, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xbf, 0xcf, 0xf0, 0xff, 0xe0, 0x00, 0x00, 0x7, 0x7f, 0xff, 0xff, 0xfe, 0xf0, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x3, 0x1, 0x00, 0x00, 0x00, 0x00, 0x7, 0xf, 0xf, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x7, 0x3, 0x7, 0x1f, 0xf, 0x7, 0x7, 0x7, 0x13, 0x18, 0x1c, 0x1f, 0x1f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x1f, 0x1f, 0xf, 0xf, 0x7, 0x3, 0x00, 0x1, 0x1, 0x3, 0x7, 0xf, 0x1f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x1f, 0xf, 0x7, 0x00, 0x3, 0x7, 0xf, 0x1f, 0x3f, 0x3f, 0x3f, 0x1f, 0x1e, 0x1d, 0xb, 0x7, 0x7, 0x7, 0x7, 0x7, 0xf, 0xf, 0xf, 0xf, 0xf, 0x7, 0x3, 0x00, 0x3, 0x7, 0x7, 0x7, 0x3, 0x3, 0x1, 0x00, 0x00, 0x00, 0x1, 0x1, 0x3, 0x3, 0x1, 0x00, 
};

const unsigned char stripesTop[] PROGMEM = {
  0x66, 0x33, 0x99, 0xcc, 0x66, 0x33, 0x99, 0xcc, 
};

const unsigned char stripesBottom[] PROGMEM = {
  0xcc, 0x99, 0x33, 0x66, 0xcc, 0x99, 0x33, 0x66, 
};

uint16_t title_animation;

const unsigned char playerSprites[] PROGMEM = {
  //Skid 
  0xa, 0x8b, 0x4e, 0xb8, 0x6e, 0x3f, 0x10, 0x8, 
  //SkidFlip
  0x8, 0x10, 0x3f, 0x6e, 0xb8, 0x4e, 0x8b, 0xa, 
  
  //Walk1
  0xa, 0xb, 0x8e, 0x78, 0x2e, 0x7f, 0x90, 0x8,
  //Walk1Flip
  0x8, 0x90, 0x7f, 0x2e, 0x78, 0x8e, 0xb, 0xa,
  //Walk2
  0xa, 0xb, 0xe, 0xb8, 0xee, 0xbf, 0x10, 0x8,
  //Walk2Flip 
  0x8, 0x10, 0xbf, 0xee, 0xb8, 0xe, 0xb, 0xa,

  //Fly1
  0xa, 0xb, 0xe, 0x38, 0x6e, 0x7f, 0x50, 0x8, 
  //Fly1Flip 
  0x8, 0x50, 0x7f, 0x6e, 0x38, 0xe, 0xb, 0xa, 
  //Fly2
  0xa, 0xb, 0xe, 0x38, 0x2e, 0x3f, 0x1c, 0x8,
  //Fly2Flip 
  0x8, 0x1c, 0x3f, 0x2e, 0x38, 0xe, 0xb, 0xa,
  //DeadWalk1 
  0x2, 0x3, 0x8e, 0x78, 0x28, 0x70, 0x90, 0x8, 
  //DeadWalk1Flip
  0x8, 0x90, 0x70, 0x28, 0x78, 0x8e, 0x3, 0x2,
  //DeadWalk2 
  0x2, 0x3, 0xe, 0xb8, 0xe8, 0xb0, 0x10, 0x8, 
  //DeadWalk2Flip
  0x8, 0x10, 0xb0, 0xe8, 0xb8, 0xe, 0x3, 0x2, 
  //DeadFly1
  0x2, 0x3, 0xe, 0x38, 0x68, 0x70, 0x50, 0x8, 
  //DeadFly1Flip
  0x8, 0x50, 0x70, 0x68, 0x38, 0xe, 0x3, 0x2, 
  //DeadFly2
  0x2, 0x3, 0xe, 0x38, 0x28, 0x38, 0x1c, 0x8, 
  //DeadFly2Flip 
  0x8, 0x1c, 0x38, 0x28, 0x38, 0xe, 0x3, 0x2, 
};

const unsigned char enemySprites[] PROGMEM = {
  0xa, 0x8b, 0x4f, 0xb8, 0x5f, 0x3e, 0x10, 0x8, 
  0x8, 0x10, 0x3e, 0x5f, 0xb8, 0x4f, 0x8b, 0xa, 
  
  0xa, 0x8b, 0x4f, 0x38, 0x1f, 0x3e, 0x50, 0x88, 
  0x88, 0x50, 0x3e, 0x1f, 0x38, 0x4f, 0x8b, 0xa, 
  0xa, 0xb, 0xf, 0xb8, 0x5f, 0xbe, 0x10, 0x8, 
  0x8, 0x10, 0xbe, 0x5f, 0xb8, 0xf, 0xb, 0xa, 

  0xa, 0xb, 0xf, 0x38, 0x7f, 0xfe, 0x90, 0x8, 
  0x8, 0x90, 0xfe, 0x7f, 0x38, 0xf, 0xb, 0xa, 
  0xa, 0xb, 0xf, 0x18, 0x3f, 0x3e, 0x16, 0xb, 
  0xb, 0x16, 0x3e, 0x3f, 0x18, 0xf, 0xb, 0xa, 
  0x2, 0x83, 0x4f, 0x38, 0x18, 0x38, 0x50, 0x88, 
  0x88, 0x50, 0x38, 0x18, 0x38, 0x4f, 0x83, 0x2, 
  0x2, 0x3, 0xf, 0xb8, 0x58, 0xb8, 0x10, 0x8, 
  0x8, 0x10, 0xb8, 0x58, 0xb8, 0xf, 0x3, 0x2, 
  0x2, 0x3, 0xf, 0x38, 0x78, 0xf8, 0x90, 0x8, 
  0x8, 0x90, 0xf8, 0x78, 0x38, 0xf, 0x3, 0x2, 
  0x2, 0x3, 0xf, 0x18, 0x38, 0x3e, 0x16, 0xb, 
  0xb, 0x16, 0x3e, 0x38, 0x18, 0xf, 0x3, 0x2,
};

const unsigned char eggSprites[] PROGMEM = {
  //Egg
0x00, 0x30, 0x78, 0xfc, 0xfc, 0x78, 0x30, 0x00, 
  //Egg hatching
0x30, 0x78, 0xfc, 0x88, 0x20, 0xfc, 0x78, 0x30, 
};

/*
 * Step the animation of the entity forward.
 * The state of the entity influences how the animation advances.
 */
void tickAnim(uint8_t i){
  //Normal statuses (TODO: perhaps organize normal statuses better)
  if( entities[i].status == STATUS_NORMAL || entities[i].status == STATUS_FLAP || entities[i].status == STATUS_RIGHT || entities[i].status == STATUS_DEAD ){
    //Run animation is timed with walking speed
    entities[i].anim += abs(entities[i].xvel)*4/4;
  }//If entity is spawning
  else if( arduboy.everyXFrames(4) && entities[i].status == STATUS_UNDYING ){
    if( entities[i].anim < 32 ){
      entities[i].anim++;// Tick forward by only 1
    }else{
      entities[i].anim = entities[i].anim == 33 ? 32 : 33;// Alternate between 32 and 33
    }
  }
}

/*
 * Get the offset of the correct sprite for the character
 * depending on their speed, direction, etc.
 */
uint8_t getSpriteOffset(uint8_t i){
  uint8_t sprOff = 0;//Use sprite offset to indicate which sprite to draw

  tickAnim(i);

  if( entities[i].status == STATUS_DEAD ){
    sprOff = ANIM_DEAD;
  }
  
  //Skid if attempting to go opposite direction of current velocity
  if( entities[i].skid ){
    sprOff += ANIM_SKID;
    //If velocity is to the right
    if( entities[i].xvel >= 0 ){
      sprOff += ANIM_FLIP;//Use flipped image
    }
  }
  //Otherwise run with frame 1 or 2 depending on animation
  else{
    //If on ground, walk.  If in air, fly.
    if( arduboy.getPixel((uint16_t)entities[i].x/32+4, (uint16_t)entities[i].y/32+8) == WHITE ){
      sprOff += ANIM_WALK;
    }else{
      sprOff += ANIM_FLY;
    }
    
    //If velocity is to the right
    if( entities[i].xvel >= 0 ){
      sprOff += ANIM_FLIP;//Use flipped image
    }

    //If anim is in the upper 50% of value of a byte, use second frame
    if( entities[i].anim > 128 ){
      sprOff += ANIM_FRAME;
    }
  }
  return sprOff;
}

void drawBackground(){
  if( game_mode == MODE_GAME ){
    arduboy.drawBitmap(0, 0, background, 128, 64, WHITE);
    /*
     * There are several regions in the stage that we overwrite
     * with black rectangles to erase them in later waves
     */
    if( wave >= 11 ){
      //Fill top platform
      arduboy.fillRect(0,10,15,5,BLACK);
      arduboy.fillRect(107,10,21,5,BLACK);
    }
    if( wave >= 21 ){
      //Fill middle platform
      arduboy.fillRect(44,37,30,5,BLACK);
    }
    if( wave >= 31 ){
      //Fill walkway over lava
      arduboy.fillRect(0,56,25,3,BLACK);
      arduboy.fillRect(102,56,26,3,BLACK);
    }
  }
}

void drawText(){
  Tinyfont tinyfont = Tinyfont(arduboy.sBuffer, Arduboy2::width(), Arduboy2::height());
  if( wave_spawn_count > 0 ){
    tinyfont.setCursor(Arduboy2::width()/2-24,Arduboy2::height()/2-8);
    tinyfont.print(F("WAVE "));
    if( wave < 10 ){
      tinyfont.print(0);
    }
    tinyfont.print(wave);
    if( wave % 5 == 0 ){
      tinyfont.setCursor(Arduboy2::width()/2-14,Arduboy2::height()/2-2);
      tinyfont.print(F("EGG"));
    }else if( (wave % 5) % 2 == 0 ){
      tinyfont.setCursor(Arduboy2::width()/2-26,Arduboy2::height()/2-2);
      tinyfont.print(F("SURVIVAL"));
    }
  }
  //Draw lives and score
  tinyfont.setTextColor(BLACK);
  tinyfont.setCursor(31,59);
  tinyfont.print(F("Lx"));
  if( lives < 10 ) tinyfont.print(0);
  tinyfont.print(lives);
  tinyfont.setCursor(68,59);
  if( score < 10000 ) tinyfont.print(0);
  if( score < 1000 ) tinyfont.print(0);
  if( score < 100 ) tinyfont.print(0);
  if( score < 10 ) tinyfont.print(0);
  tinyfont.print(score);
}

void drawTitle(){
  uint8_t i;
  // Draw title graphic
  arduboy.drawBitmap(0, 8, title, 128, 48, WHITE);
}

void drawHighscores(){
  uint8_t i;
  arduboy.setCursor(128/2-6*5,8);
  arduboy.print(F("HIGHSCORES"));
  for( i = 0; i < NUM_HIGHSCORES; i++ ){
    arduboy.setCursor(128/2-6*5,16+i*8);
    arduboy.print(highscores.initials[i][0]);
    arduboy.print(highscores.initials[i][1]);
    arduboy.print(highscores.initials[i][2]);
    arduboy.print(F("  "));
    if( highscores.scores[i] < 10000 ) arduboy.print(0);
    if( highscores.scores[i] < 1000 ) arduboy.print(0);
    if( highscores.scores[i] < 100 ) arduboy.print(0);
    if( highscores.scores[i] < 10 ) arduboy.print(0);
    arduboy.print(highscores.scores[i]);
  }
}

void drawGame(){
  uint8_t i, sprOff;
  int16_t xdraw;
  switch( game_mode ){
    case MODE_TITLE:
      /* Convoluted way to get around slowdown when drawing title animation */
      if( (title_animation >= 128 && arduboy.everyXFrames(2)) || arduboy.everyXFrames(4) ){
        title_animation++;
        title_animation %= 256;
      }
      if( title_animation < 128 ){
        drawTitle();
      }else{
        drawHighscores();
        // I am drawing stripes in a different way than I originally intended.  The angle they lean
        // at has been changed compared to how it works in the original
        // Draw stripes to the left and right only for highscores
        for( i = 0; i < 9; i++ ){
          arduboy.drawBitmap(120, (int16_t)(title_animation+(8*i)) % 64, stripesBottom, 8, 8, WHITE);
          arduboy.drawBitmap(0, 64 - ((int16_t)(title_animation+(8*i)) % 64), stripesBottom, 8, 8, WHITE);
        }
        // Clear out stripe regions on top and bottom with black bars
        arduboy.fillRect(0,0,128,8,BLACK);
        arduboy.fillRect(0,56,128,8,BLACK);
      }
      // Draw stripes above and below title or highscores
      for( i = 0; i < 17; i++ ){
        arduboy.drawBitmap((int16_t)(title_animation+(8*i)) % 136 - 8, 0, stripesTop, 8, 8, WHITE);
        arduboy.drawBitmap(120 - ((int16_t)(title_animation+(8*i)) % 136 - 8), 56, stripesTop, 8, 8, WHITE);
      }
      // Slowly reveal stripes based on animation
      if( title_animation < 64 ){
        arduboy.fillRect(title_animation*2,0,128,8,BLACK);
        arduboy.fillRect(0,56,128-title_animation*2,8,BLACK);
      }
      break;
    case MODE_GAME:
      for( i = 0; i < NUM_ENTITIES; i++ ){
        switch( entities[i].type ){
          case TYPE_PLAYER:
            sprOff = getSpriteOffset(i);
            //If spawning, make it rise out of the spawn area
            if( entities[i].status == STATUS_UNDYING ){
              //Flash while invulnerable but ready to move
              if( entities[i].anim != 33 ){
                arduboy.drawBitmap(((uint16_t)entities[i].x)/32, ((uint16_t)entities[i].y)/32 + (8-entities[i].anim/4), playerSprites+sprOff, 8, entities[i].anim/4, WHITE);
              }
            }else{
              //Enable drawing off the left side of the screen
              xdraw = ((uint16_t)entities[i].x)/32;
              if( xdraw > 256 ) xdraw -= 2048;// 65536/32
              arduboy.drawBitmap( xdraw, ((uint16_t)entities[i].y)/32, playerSprites+sprOff, 8, 8, WHITE);
            }
            break;
          case TYPE_ENEMY:
            sprOff = getSpriteOffset(i);
            //If spawning, make it rise out of the spawn area
            if( entities[i].status == STATUS_UNDYING ){
              arduboy.drawBitmap(((uint16_t)entities[i].x)/32, ((uint16_t)entities[i].y)/32 + (8-entities[i].anim/4), enemySprites+sprOff, 8, entities[i].anim/4, WHITE);
            }else{
              //Enable drawing off the left side of the screen
              xdraw = ((uint16_t)entities[i].x)/32;
              if( xdraw > 256 ) xdraw -= 2048;// 65536/32
              arduboy.drawBitmap( xdraw, ((uint16_t)entities[i].y)/32, enemySprites+sprOff, 8, 8, WHITE);
            }
            break;
          case TYPE_EGG:
            if( arduboy.everyXFrames(4) ){
              entities[i].anim++;
            }
            //Enable drawing off the left side of the screen
            xdraw = ((uint16_t)entities[i].x)/32;
            if( xdraw > 256 ) xdraw -= 2048;// 65536/32
            //If animation is less than 3/4 completed, don't show it starting to hatch
            if( entities[i].anim < 192 ){
              arduboy.drawBitmap( xdraw, ((uint16_t)entities[i].y)/32, eggSprites, 8, 8, WHITE);
            }else{
              //Show egg starting to hatch
              arduboy.drawBitmap( xdraw, ((uint16_t)entities[i].y)/32, eggSprites+8, 8, 8, WHITE);
            }
            break;
        }
      }
      drawText();
      break;
    case MODE_DEAD:
      arduboy.setCursor(128/2-6*4-3,16);
      arduboy.print(F("GAME OVER"));
      arduboy.setCursor(128/2-6*3-3,32);
      arduboy.print(F("PRESS A"));
      break;
    case MODE_HIGHSCORE:
      arduboy.setCursor(128/2-6*6-3,16);
      arduboy.print(F("NEW HIGHSCORE"));
      arduboy.setCursor(128/2-9,24);
      for( i = 0; i < 3; i++ ){
        //If this letter is selected, show arrows for it
        if( i == initials_cursor ){
          arduboy.print(F("\x1e"));
        }else{
          arduboy.print(F(" "));
        }
      }
      arduboy.setCursor(128/2-9,32);
      for( i = 0; i < 3; i++ ){
        //Display value of letter
        arduboy.print(score_initials[i]);
      }
      arduboy.setCursor(128/2-9,40);
      for( i = 0; i < 3; i++ ){
        //If this letter is selected, show arrows for it
        if( i == initials_cursor ){
          arduboy.print(F("\x1f"));
        }else{
          arduboy.print(F(" "));
        }
      }
      // Print highscore
      arduboy.setCursor(128/2-6*2-3,48);
      if( score < 10000 ) arduboy.print(0);
      if( score < 1000 ) arduboy.print(0);
      if( score < 100 ) arduboy.print(0);
      if( score < 10 ) arduboy.print(0);
      arduboy.print(score);
      
      break;
  }
}
