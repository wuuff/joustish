#include "game.h"

const unsigned char playerWalk1[] PROGMEM = {
  0xa, 0xb, 0x8e, 0x78, 0x3e, 0x7f, 0x90, 0x8, 
};

const unsigned char playerWalk1flip[] PROGMEM = {
0x8, 0x90, 0x7f, 0x3e, 0x78, 0x8e, 0xb, 0xa, 
};

void drawGame(){
  uint8_t i;
  for( i = 0; i < NUM_ENTITIES; i++ ){
    switch( entities[i].type ){
      case TYPE_PLAYER:
        if( entities[i].xvel < 0 )
          arduboy.drawBitmap(((uint16_t)entities[i].x)/8, ((uint16_t)entities[i].y)/8, playerWalk1, 8, 8, WHITE);
        else
          arduboy.drawBitmap(((uint16_t)entities[i].x)/8, ((uint16_t)entities[i].y)/8, playerWalk1flip, 8, 8, WHITE);
        break;
      case TYPE_ENEMY:
        
        break;
      case TYPE_EGG:
        
        break;
    }
  }
}
