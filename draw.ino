#include "game.h"
#include "draw.h"

const unsigned char playerSprites[] PROGMEM = {
  //Walk1
  0xa, 0xb, 0x8e, 0x78, 0x3e, 0x7f, 0x90, 0x8, 
  //Walk1Flip
  0x8, 0x90, 0x7f, 0x3e, 0x78, 0x8e, 0xb, 0xa,
  //Walk2
  0xa, 0xb, 0xe, 0xb8, 0xfe, 0xbf, 0x10, 0x8,
  //Walk2Flip
  0x8, 0x10, 0xbf, 0xfe, 0xb8, 0xe, 0xb, 0xa,
  //Skid
  0xa, 0x8b, 0x4e, 0xb8, 0x7e, 0x3f, 0x10, 0x8,
  //SkidFlip
  0x8, 0x10, 0x3f, 0x7e, 0xb8, 0x4e, 0x8b, 0xa, 
  //Fly1
  0xa, 0xb, 0xe, 0x38, 0x7e, 0x7f, 0x50, 0x8, 
  //Fly1Flip
  0x8, 0x50, 0x7f, 0x7e, 0x38, 0xe, 0xb, 0xa, 
  //Fly2
  0xa, 0xb, 0xe, 0x38, 0x3e, 0x3f, 0x1c, 0x8,
  //Fly2Flip
  0x8, 0x1c, 0x3f, 0x3e, 0x38, 0xe, 0xb, 0xa,
};

void drawGame(){
  uint8_t i, sprOff;
  for( i = 0; i < NUM_ENTITIES; i++ ){
    sprOff = 0;//Use sprite offset to indicate which sprite to draw
    switch( entities[i].type ){
      case TYPE_PLAYER:
        //Run animation is timed with walking speed
        entities[i].anim += abs(entities[i].xvel)*4;
        //Skid if attempting to go opposite direction of current velocity
        if( entities[i].skid ){
          sprOff = ANIM_SKID;
          //If velocity is to the right
          if( entities[i].xvel >= 0 ){
            sprOff += ANIM_FLIP;//Use flipped image
          }
        }
        //Otherwise run with frame 1 or 2 depending on animation
        else{
          //If on ground, walk.  If in air, fly.
          if( arduboy.getPixel((uint16_t)entities[i].x/8+4, (uint16_t)entities[i].y/8+8) == WHITE ){
            sprOff = ANIM_WALK;
          }else{
            sprOff = ANIM_FLY;
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
        arduboy.drawBitmap(((uint16_t)entities[i].x)/8, ((uint16_t)entities[i].y)/8, playerSprites+sprOff, 8, 8, WHITE);
        break;
      case TYPE_ENEMY:
        arduboy.drawBitmap(((uint16_t)entities[i].x)/8, ((uint16_t)entities[i].y)/8, playerSprites, 8, 8, WHITE);
        break;
      case TYPE_EGG:
        
        break;
    }
  }
}
