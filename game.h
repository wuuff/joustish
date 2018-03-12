#ifndef GAME_H
#define GAME_H

struct entity{
  uint8_t type;
  uint8_t status;
  int16_t x;
  int16_t y;
  int16_t xvel;
  int16_t yvel;
  uint8_t anim;
  uint8_t skid;
};

struct coord{
  uint16_t x;
  uint16_t y;
};

#define GRAVITY 4
#define VEL_MAX 31
#define ENEMY_VEL_MAX 8//#define ENEMY_VEL_MAX 16

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define TYPE_NULL 0
#define TYPE_PLAYER 1
#define TYPE_ENEMY 2
#define TYPE_EGG 3

#define STATUS_NORMAL 0
#define STATUS_UNDYING 1
#define STATUS_DEAD 2
#define STATUS_FLAP 3
#define STATUS_RIGHT 4

#define NUM_ENTITIES 8
#define NUM_SPAWNS 4
#define NUM_EGG_SPAWNS 8

extern struct entity entities[NUM_ENTITIES];

extern void stepGame();

#endif
