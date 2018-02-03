#include "game.h"

const unsigned char playerWalk1[] PROGMEM = {
  0xa, 0xb, 0x8e, 0x78, 0x3e, 0x7f, 0x90, 0x8, 
};

const unsigned char playerWalk1Flip[] PROGMEM = {
0x8, 0x90, 0x7f, 0x3e, 0x78, 0x8e, 0xb, 0xa, 
};

const unsigned char playerWalk2[] PROGMEM = {
0xa, 0xb, 0xe, 0xb8, 0xfe, 0xbf, 0x10, 0x8, 
};

const unsigned char playerWalk2Flip[] PROGMEM = {
0x8, 0x10, 0xbf, 0xfe, 0xb8, 0xe, 0xb, 0xa, 
};

const unsigned char playerSkid[] PROGMEM = {
0xa, 0x8b, 0x4e, 0xb8, 0x7e, 0x3f, 0x10, 0x8, 
};

const unsigned char playerSkidFlip[] PROGMEM = {
0x8, 0x10, 0x3f, 0x7e, 0xb8, 0x4e, 0x8b, 0xa, 
};

const unsigned char playerFly1[] PROGMEM = {
0xa, 0xb, 0xe, 0x38, 0x7e, 0x7f, 0x50, 0x8, 
};

const unsigned char playerFly1Flip[] PROGMEM = {
0x8, 0x50, 0x7f, 0x7e, 0x38, 0xe, 0xb, 0xa, 
};

const unsigned char playerFly2[] PROGMEM = {
0xa, 0xb, 0xe, 0x38, 0x3e, 0x3f, 0x1c, 0x8,
};

const unsigned char playerFly2Flip[] PROGMEM = {
0x8, 0x1c, 0x3f, 0x3e, 0x38, 0xe, 0xb, 0xa, 
};

void drawGame(){
  uint8_t i;
  for( i = 0; i < NUM_ENTITIES; i++ ){
    switch( entities[i].type ){
      case TYPE_PLAYER:
        //TODO: convert player sprites into one big block and use offsets for mirroring and animation
        //Run animation is timed with walking speed
        entities[i].anim += abs(entities[i].xvel)*2;
        //Skid if velocity differs
        if( entities[i].skid ){
          if( entities[i].xvel < 0 )
            arduboy.drawBitmap(((uint16_t)entities[i].x)/8, ((uint16_t)entities[i].y)/8, playerSkid, 8, 8, WHITE);
          else
            arduboy.drawBitmap(((uint16_t)entities[i].x)/8, ((uint16_t)entities[i].y)/8, playerSkidFlip, 8, 8, WHITE);
        }
        //Otherwise run with frame 1 or 2 depending on animation
        else if( entities[i].anim > 128 ){
          if( entities[i].xvel < 0 ){
            //If on ground
            if( arduboy.getPixel((uint16_t)entities[i].x/8+4, (uint16_t)entities[i].y/8+8) == WHITE ){
              arduboy.drawBitmap(((uint16_t)entities[i].x)/8, ((uint16_t)entities[i].y)/8, playerWalk1, 8, 8, WHITE);
            }else{
              arduboy.drawBitmap(((uint16_t)entities[i].x)/8, ((uint16_t)entities[i].y)/8, playerFly1, 8, 8, WHITE);
            }
          }else{
            //If on ground
            if( arduboy.getPixel((uint16_t)entities[i].x/8+4, (uint16_t)entities[i].y/8+8) == WHITE ){
              arduboy.drawBitmap(((uint16_t)entities[i].x)/8, ((uint16_t)entities[i].y)/8, playerWalk1Flip, 8, 8, WHITE);
            }else{
              arduboy.drawBitmap(((uint16_t)entities[i].x)/8, ((uint16_t)entities[i].y)/8, playerFly1Flip, 8, 8, WHITE);
            }
          }
        }else{
          if( entities[i].xvel < 0 ){
            //If on ground
            if( arduboy.getPixel((uint16_t)entities[i].x/8+4, (uint16_t)entities[i].y/8+8) == WHITE ){
              arduboy.drawBitmap(((uint16_t)entities[i].x)/8, ((uint16_t)entities[i].y)/8, playerWalk2, 8, 8, WHITE);
            }else{
              arduboy.drawBitmap(((uint16_t)entities[i].x)/8, ((uint16_t)entities[i].y)/8, playerFly2, 8, 8, WHITE);
            }
          }else{
            //If on ground
            if( arduboy.getPixel((uint16_t)entities[i].x/8+4, (uint16_t)entities[i].y/8+8) == WHITE ){
              arduboy.drawBitmap(((uint16_t)entities[i].x)/8, ((uint16_t)entities[i].y)/8, playerWalk2Flip, 8, 8, WHITE);
            }else{
              arduboy.drawBitmap(((uint16_t)entities[i].x)/8, ((uint16_t)entities[i].y)/8, playerFly2Flip, 8, 8, WHITE);
            }
          }
        }
        break;
      case TYPE_ENEMY:
        
        break;
      case TYPE_EGG:
        
        break;
    }
  }
}
