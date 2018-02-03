#include "game.h"

struct entity entities[NUM_ENTITIES];

void stepPlayer(uint8_t index){
  uint8_t state = arduboy.buttonsState();

  entities[index].skid = 0;

  //Apply left or right velocity
  if( LEFT_BUTTON & state ){
    //If direction differs, then we are skidding
    if( entities[index].xvel > 0 ) entities[index].skid = 1;
    entities[index].xvel -= 2;
  }
  else if( RIGHT_BUTTON & state ){
    //If direction differs, then we are skidding
    if( entities[index].xvel < 0 ) entities[index].skid = 1;
    entities[index].xvel += 2;
  }

  //Jump or apply gravity
  if( A_BUTTON & state ){
    entities[index].yvel -= 7;
  }else{
    entities[index].yvel += GRAVITY;
  }

  //Cap off velocity so we can't go through things
  if( entities[index].yvel > VEL_MAX ) entities[index].yvel = VEL_MAX;
  else if( entities[index].yvel < -VEL_MAX ) entities[index].yvel = -VEL_MAX;
  if( entities[index].xvel > VEL_MAX ) entities[index].xvel = VEL_MAX;
  else if( entities[index].xvel < -VEL_MAX ) entities[index].xvel = -VEL_MAX;

  //Test world collision (x)
  while( entities[index].xvel != 0 && 
      //Top left, top right, bottom left, bottom right, mid left, mid right
      (arduboy.getPixel((uint16_t)(entities[index].x + entities[index].xvel)/8+2, (uint16_t)entities[index].y/8+4) == WHITE || 
      arduboy.getPixel((uint16_t)(entities[index].x + entities[index].xvel)/8+6, (uint16_t)entities[index].y/8+4) == WHITE || 
      arduboy.getPixel((uint16_t)(entities[index].x + entities[index].xvel)/8+2, (uint16_t)entities[index].y/8+7) == WHITE || 
      arduboy.getPixel((uint16_t)(entities[index].x + entities[index].xvel)/8+6, (uint16_t)entities[index].y/8+7) == WHITE ||
      arduboy.getPixel((uint16_t)(entities[index].x + entities[index].xvel)/8+2, (uint16_t)entities[index].y/8+6) == WHITE ||
      arduboy.getPixel((uint16_t)(entities[index].x + entities[index].xvel)/8+6, (uint16_t)entities[index].y/8+6) == WHITE ) ){
  //arduboy.print("XX");
    entities[index].xvel /= 2;
  }
  arduboy.print( arduboy.getPixel((uint16_t)entities[index].x/8, (uint16_t)(entities[index].y + entities[index].yvel)/8) );
  //Test world collision (y)
  while( entities[index].yvel != 0 &&
      (arduboy.getPixel((uint16_t)entities[index].x/8+2, (uint16_t)(entities[index].y + entities[index].yvel)/8+1) == WHITE || 
      arduboy.getPixel((uint16_t)entities[index].x/8+6, (uint16_t)(entities[index].y + entities[index].yvel)/8+1) == WHITE || 
      arduboy.getPixel((uint16_t)entities[index].x/8+2, (uint16_t)(entities[index].y + entities[index].yvel)/8+7) == WHITE || 
      arduboy.getPixel((uint16_t)entities[index].x/8+6, (uint16_t)(entities[index].y + entities[index].yvel)/8+7) == WHITE ||
      arduboy.getPixel((uint16_t)entities[index].x/8+2, (uint16_t)(entities[index].y + entities[index].yvel)/8+4) == WHITE ||
      arduboy.getPixel((uint16_t)entities[index].x/8+6, (uint16_t)(entities[index].y + entities[index].yvel)/8+4) == WHITE ||
      (entities[index].y + entities[index].yvel)/8 > (SCREEN_HEIGHT-10) ||
      (entities[index].y + entities[index].yvel) < 0 ) ){
        //arduboy.print("YY");
    entities[index].yvel /= 2;
  }

  //Free if get stuck
  if( arduboy.getPixel((uint16_t)entities[index].x/8+2, (uint16_t)entities[index].y/8+4) == WHITE || 
      arduboy.getPixel((uint16_t)entities[index].x/8+6, (uint16_t)entities[index].y/8+4) == WHITE || 
      arduboy.getPixel((uint16_t)entities[index].x/8+2, (uint16_t)entities[index].y/8+7) == WHITE || 
      arduboy.getPixel((uint16_t)entities[index].x/8+6, (uint16_t)entities[index].y/8+7) == WHITE ||
      arduboy.getPixel((uint16_t)entities[index].x/8+2, (uint16_t)entities[index].y/8+6) == WHITE ||
      arduboy.getPixel((uint16_t)entities[index].x/8+6, (uint16_t)entities[index].y/8+6) == WHITE ){
     entities[index].yvel -= 4;
   }
  
  
  entities[index].x += (int16_t)entities[index].xvel;
  entities[index].y += (int16_t)entities[index].yvel;

  //Stop from falling off bottom
  /*if( entities[index].y > (SCREEN_HEIGHT-8)*8 ){
    entities[index].y = (SCREEN_HEIGHT-8)*8-4;
    entities[index].yvel = 0;
  }*/

  //Wrap left and right
  if( entities[index].x > (SCREEN_WIDTH-7)*8 ){
    arduboy.print("AAAAAAA");
    entities[index].x -= (SCREEN_WIDTH-8)*8;
  }
  else if( entities[index].x < 0 ){
    entities[index].x += (SCREEN_WIDTH-8)*8;
    arduboy.print("BBBBBB");
  }

  arduboy.setCursor(4, 9);
  arduboy.print((int16_t)entities[index].x);
  arduboy.print(F(","));
  arduboy.println((int16_t)entities[index].y);
  
  arduboy.print(entities[index].xvel);
  arduboy.print(F(","));
  arduboy.println(entities[index].yvel);
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
