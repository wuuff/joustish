#include "game.h"

struct entity entities[NUM_ENTITIES];

/*
 * Test entity/entity collision
 */
void testCollision(uint8_t index){
  uint8_t i;
  for( i = 0; i < NUM_ENTITIES; i++ ){
    //Do not check for collision with self or null entities
    if( i != index && entities[i].type != TYPE_NULL ){
      //If they are colliding on the x axis (bounding box of 6, not 8)
      if( entities[i].x-3*8 < entities[index].x && entities[i].x+3*8 > entities[index].x ){
        //If they are colliding on the y axis (bounding box of 7, not 8)
        if( entities[i].y-3*8 < entities[index].y && entities[i].y+4*8 > entities[index].y ){
          //If travelling towards other entity (if travelling away, do nothing)
          if( (entities[index].xvel > 0 && entities[i].x > entities[index].x) ||
              (entities[index].xvel < 0 && entities[i].x < entities[index].x) ){
            entities[index].xvel *= -2;//Bounce
          }
          //If the colliding entities are the player and an enemy
          if( (entities[index].type == TYPE_PLAYER && entities[i].type == TYPE_ENEMY) ){
            //If player is higher, enemy dies
            if( entities[index].y/8 < entities[i].y/8 ){
              entities[i].status = STATUS_DEAD;
            }//If enemy is higher, player dies
            else if( entities[index].y/8 > entities[i].y/8 ){
              entities[index].status = STATUS_DEAD;
            }
            //If they are even, they just bounce
          }
          if(index == 0) arduboy.print(F("HIT"));
        }
      }
    }
  }
}

/*
 * Step movement for entities, checking world and entity collision.
 * This does not include the inputs by the entity (AI or player input).
 */
void stepEntity(uint8_t index){
  //Test for collision with other entities
  testCollision(index);
  
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
    entities[index].xvel /= -2;
  }
  //arduboy.print( arduboy.getPixel((uint16_t)entities[index].x/8, (uint16_t)(entities[index].y + entities[index].yvel)/8) );
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
    //Bounce if travelling upwards, but just stop if going down (so you don't bounce on landing)
    if( entities[index].yvel < 0 ){
      entities[index].yvel /= -2;
    }else{
      entities[index].yvel /= 2;
    }
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

   //If get stuck above screen, force into screen
   if( (entities[index].y) < 0 ){
     entities[index].y = 0;
   }

  //Wrap left and right
  if( entities[index].x > (SCREEN_WIDTH-7)*8 ){
    arduboy.print("AAAAAAA");
    entities[index].x -= (SCREEN_WIDTH-8)*8;
  }
  else if( entities[index].x < 0 ){
    entities[index].x += (SCREEN_WIDTH-8)*8;
    arduboy.print("BBBBBB");
  }

  /*
  arduboy.setCursor(4, 9);
  arduboy.print((int16_t)entities[index].x);
  arduboy.print(F(","));
  arduboy.println((int16_t)entities[index].y);
  
  arduboy.print(entities[index].xvel);
  arduboy.print(F(","));
  arduboy.println(entities[index].yvel);
  */
}

/*
 * Check player inputs and determine how they will attempt
 * to influence the player's velocity.  This may be overridden
 * by stepEntity if the player cannot move to where they are attempting.
 */
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

  //Flap if button is pressed (but not held) or apply gravity
  if( (A_BUTTON & state) && entities[index].status == STATUS_NORMAL ){
    entities[index].status = STATUS_FLAP;
    entities[index].yvel -= 16;
  }else{
    //If player was flapping (and button is no longer pressed), set back to not flapping
    if( !(A_BUTTON & state) && entities[index].status == STATUS_FLAP ){
      entities[index].status = STATUS_NORMAL;
    }
    entities[index].yvel += GRAVITY;
  }

}

/*
 * Check enemy AI and determine how it will attempt
 * to influence the enemy's velocity.  This may be overridden
 * by stepEntity if the AI cannot move to where it is attempting.
 */
void stepEnemy(uint8_t index){
  entities[index].skid = 0;//Assume not skidding
  //Random flaps
  if( rand()%6 == 0 ){
    entities[index].yvel -= 16;
  }
  //Switch direction chance
  if( rand()%64 == 0 ){
    if( entities[index].status == STATUS_NORMAL ){
      entities[index].status = STATUS_RIGHT;
    }else if( entities[index].status == STATUS_RIGHT ){
      entities[index].status = STATUS_NORMAL;
    }
  }
  //Run left or right depending on choice
  if( entities[index].status == STATUS_NORMAL ){
    //If direction differs, then we are skidding
    if( entities[index].xvel > 0 ) entities[index].skid = 1;
    //Flap if stuck
    if( entities[index].xvel > -2 ){
      entities[index].yvel -= 6;
    }
    //Run if not going too fast
    if( entities[index].xvel > -ENEMY_VEL_MAX ){
      entities[index].xvel -= 2;
    }
  }else if( entities[index].status == STATUS_RIGHT ){
    //If direction differs, then we are skidding
    if( entities[index].xvel < 0 ) entities[index].skid = 1;
    //Flap if stuck
    if( entities[index].xvel < 2 ){
      entities[index].yvel -= 6;
    }
    //Run if not going too fast
    if( entities[index].xvel < ENEMY_VEL_MAX ){
      entities[index].xvel += 2;
    }
  }
  entities[index].yvel += GRAVITY;
}

void stepEgg(uint8_t index){
  
}

void stepGame(){
  uint8_t i;
  for( i = 0; i < NUM_ENTITIES; i++ ){
    switch( entities[i].type ){
      case TYPE_PLAYER:
        stepPlayer(i);
        stepEntity(i);
        break;
      case TYPE_ENEMY:
        stepEnemy(i);
        stepEntity(i);
        break;
      case TYPE_EGG:
        stepEgg(i);
        break;
    }
  }
}
