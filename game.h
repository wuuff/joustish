#ifndef GAME_H
#define GAME_H

struct entity{
  uint8_t type;
  uint8_t status;
  uint16_t x;
  uint16_t y;
  uint16_t xvel;
  uint16_t yvel;
};

#define TYPE_PLAYER 0
#define TYPE_ENEMY 1
#define TYPE_EGG 2

#define STATUS_NORMAL 0
#define STATUS_UNDYING 1
#define STATUS_DEAD 2

#define NUM_ENTITIES 8

extern struct entity entities[NUM_ENTITIES];

extern void stepGame();

#endif
