#include "game.h"

const unsigned char playerWalk1[] PROGMEM = {
  0xa, 0xb, 0x8e, 0x78, 0x3e, 0x7f, 0x90, 0x8, 
};

void drawGame(){
  uint8_t i;
  for( i = 0; i < NUM_ENTITIES; i++ ){
    switch( entities[i].type ){
      case TYPE_PLAYER:
        arduboy.drawBitmap(entities[i].x/8, entities[i].y/8, playerWalk1, 8, 8, WHITE);
        break;
      case TYPE_ENEMY:
        
        break;
      case TYPE_EGG:
        
        break;
    }
  }
}
