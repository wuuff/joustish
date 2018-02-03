#include "game.h"

struct entity entities[NUM_ENTITIES];

void stepPlayer(uint8_t index){
  uint8_t state = arduboy.buttonsState();
  if( LEFT_BUTTON & state ){
    entities[index].xvel -= 5;
  }
  else if( RIGHT_BUTTON & state ){
    entities[index].xvel += 5;
  }
  
  if( A_BUTTON & state ){
    entities[index].yvel += 20;
  }
  
  entities[index].x += entities[index].xvel;
  entities[index].y += entities[index].yvel;
}

void stepEnemy(uint8_t index){
  
}

void stepEgg(uint8_t index){
  
}

void stepGame(){
  uint8_t i;
  for( i = 0; i < NUM_ENTITIES; i++ ){
    switch( entities[i].type ){
      case TYPE_PLAYER:
        stepPlayer(i);
        break;
      case TYPE_ENEMY:
        stepEnemy(i);
        break;
      case TYPE_EGG:
        stepEgg(i);
        break;
    }
  }
}
