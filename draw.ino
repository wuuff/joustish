#include "game.h"
#include "draw.h"

const unsigned char playerSprites[] PROGMEM = {
  //Walk1
  0xa, 0xb, 0x8e, 0x78, 0x2e, 0x7f, 0x90, 0x8,
  //Walk1Flip
  0x8, 0x90, 0x7f, 0x2e, 0x78, 0x8e, 0xb, 0xa,
  //Walk2
  0xa, 0xb, 0xe, 0xb8, 0xee, 0xbf, 0x10, 0x8,
  //Walk2Flip 
  0x8, 0x10, 0xbf, 0xee, 0xb8, 0xe, 0xb, 0xa,
  //Skid 
  0xa, 0x8b, 0x4e, 0xb8, 0x6e, 0x3f, 0x10, 0x8, 
  //SkidFlip
  0x8, 0x10, 0x3f, 0x6e, 0xb8, 0x4e, 0x8b, 0xa, 
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
  //Walk1
  0xa, 0x8b, 0x4f, 0x38, 0x1f, 0x3e, 0x50, 0x88, 
  //Walk1Flip
  0x88, 0x50, 0x3e, 0x1f, 0x38, 0x4f, 0x8b, 0xa, 
  //Walk2
  0xa, 0xb, 0xf, 0xb8, 0x5f, 0xbe, 0x10, 0x8, 
  //Walk2Flip
  0x8, 0x10, 0xbe, 0x5f, 0xb8, 0xf, 0xb, 0xa, 
  //Skid
  0xa, 0x8b, 0x4f, 0xb8, 0x5f, 0x3e, 0x10, 0x8, 
  //SkidFlip
  0x8, 0x10, 0x3e, 0x5f, 0xb8, 0x4f, 0x8b, 0xa, 
  //Fly1
  0xa, 0xb, 0xf, 0x38, 0x7f, 0xfe, 0x90, 0x8, 
  //Fly1Flip
  0x8, 0x90, 0xfe, 0x7f, 0x38, 0xf, 0xb, 0xa, 
  //Fly2
  0xa, 0xb, 0xf, 0x18, 0x3f, 0x3e, 0x16, 0xb, 
  //Fly2Flip
  0xb, 0x16, 0x3e, 0x3f, 0x18, 0xf, 0xb, 0xa, 
};

/*
 * Get the offset of the correct sprite for the character
 * depending on their speed, direction, etc.
 */
uint8_t getSpriteOffset(uint8_t i){
  uint8_t sprOff = 0;//Use sprite offset to indicate which sprite to draw
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
  return sprOff;
}

void drawGame(){
  uint8_t i, sprOff;
  for( i = 0; i < NUM_ENTITIES; i++ ){
    switch( entities[i].type ){
      case TYPE_PLAYER:
        sprOff = getSpriteOffset(i);
        arduboy.drawBitmap(((uint16_t)entities[i].x)/8, ((uint16_t)entities[i].y)/8, playerSprites+sprOff, 8, 8, WHITE);
        break;
      case TYPE_ENEMY:
        sprOff = getSpriteOffset(i);
        arduboy.drawBitmap(((uint16_t)entities[i].x)/8, ((uint16_t)entities[i].y)/8, enemySprites+sprOff, 8, 8, WHITE);
        break;
      case TYPE_EGG:
        
        break;
    }
  }
}
