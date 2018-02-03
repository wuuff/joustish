#ifndef GAME_H
#define GAME_H

struct entity{
  uint8_t type;
  uint8_t status;
  int16_t x;
  int16_t y;
  int16_t xvel;
  int16_t yvel;
};

#define GRAVITY 4
#define VEL_MAX 32

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define TYPE_NULL 0
#define TYPE_PLAYER 1
#define TYPE_ENEMY 2
#define TYPE_EGG 3

#define STATUS_NORMAL 0
#define STATUS_UNDYING 1
#define STATUS_DEAD 2

#define NUM_ENTITIES 8

extern struct entity entities[NUM_ENTITIES];

extern void stepGame();

#endif
