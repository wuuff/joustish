#include "game.h"
#include "highscores.h"

struct entity entities[NUM_ENTITIES];

uint8_t wave;
uint8_t wave_timer;
uint8_t wave_spawn_type;
uint8_t wave_spawn_count;
uint8_t survival_bonus = 0;
uint16_t egg_timer = 0;// Timer so that eggs stop spawning after a certain time
#define EGG_LIMIT 900 // Egg spawn time limit (900 frames @ 15 fps = 60 seconds)
uint8_t enemy_speed_bonus = 0;

uint8_t lives;
uint32_t score;

uint8_t game_mode;

uint8_t button_held;
uint8_t a_held;

/*
 * This contains the locations of the spawn locations in the map
 */
struct coord spawn_points[NUM_SPAWNS] = {
  {47,5},
  {6,23},
  {98,18},
  {51,49},
};

/*
 * This contains the locations of egg spawn locations in the map
 */
struct coord egg_spawn_points[NUM_EGG_SPAWNS] = {
  {4,1},
  {57,2},
  {116,1},
  {11,17},
  {52,21},
  {93,11},
  {30,42},
  {82,42},
};

#define POINTS_BIRD 500
#define POINTS_EGG 250
#define POINTS_SURVIVE 1000
#define NEW_BIRD 5000
/*
 * Add a value to the score.  Every NEW_BIRD
 * points, add a life.
 */
void addScore(uint16_t amount){
  if( score/NEW_BIRD < (score+amount)/5000 ){
    lives++;
  }
  score += amount;
}

/*
 * Search for an empty slot to spawn an entity
 */
int8_t trySpawn(uint8_t type){
  int8_t i;
  for( i = 0; i < NUM_ENTITIES; i++ ){
    if( entities[i].type == TYPE_NULL ){
      entities[i].type = type;
      return i;
    }
  }
  return -1;
}

/*
 * Spawn a player or enemy by choosing a spawn location
 */
void spawnBird(uint8_t index){
  uint8_t loc = rand()%NUM_SPAWNS;// Choose spawn location randomly
  entities[index].x = spawn_points[loc].x*8;
  entities[index].y = spawn_points[loc].y*8;
  entities[index].xvel = 0;
  entities[index].yvel = 0;
  entities[index].status = STATUS_UNDYING;// Invulnerable when it first spawns
  entities[index].anim = 0;// Reset animation, as we use this to animate the spawning
}

/*
 * Spawn an egg by choosing a spawn location
 */
void spawnEgg(uint8_t index){
  uint8_t loc = rand()%NUM_EGG_SPAWNS;// Choose spawn location randomly
  entities[index].x = egg_spawn_points[loc].x*8;
  entities[index].y = egg_spawn_points[loc].y*8;
  entities[index].xvel = 0;
  entities[index].yvel = 0;
  entities[index].status = STATUS_UNDYING;// Unvulnerable when it first spawns
  entities[index].anim = 0;// Reset animation, as we use this to animate the spawning
}

/*
 * Test entity/entity collision
 */
void testCollision(uint8_t index){
  uint8_t i;
  int8_t egg;
  for( i = 0; i < NUM_ENTITIES; i++ ){
    //Do not check for collision with self or null entities
    if( i != index && entities[i].type != TYPE_NULL && entities[i].status != STATUS_DEAD && entities[i].status != STATUS_UNDYING){
      //If they are colliding on the x axis (bounding box of 6, not 8) NOW 8
      if( entities[i].x-5*8 < entities[index].x && entities[i].x+5*8 > entities[index].x ){
        //If they are colliding on the y axis (bounding box of 7, not 8) NOW 8
        if( entities[i].y-5*8 < entities[index].y && entities[i].y+5*8 > entities[index].y ){
          //If travelling towards other entity (if travelling away, do nothing)
          if( (entities[index].xvel > 0 && entities[i].x > entities[index].x) ||
              (entities[index].xvel < 0 && entities[i].x < entities[index].x) ){
            entities[index].xvel /= -2;//Bounce
          }
          //If the colliding entities are the player and an enemy
          if( (entities[index].type == TYPE_PLAYER && entities[i].type == TYPE_ENEMY) ){
            //If player is higher, enemy dies
            if( entities[index].y/8 < entities[i].y/8 ){
              arduboy.print(F("ENEM"));
              entities[i].status = STATUS_DEAD;
              addScore(POINTS_BIRD);
              egg = -1;
              if( egg_timer < EGG_LIMIT ){
                egg = trySpawn(TYPE_EGG);
              }
              //If egg successfully spawned (if not, just silently fail to spawn egg)
              if( egg != -1 ){
                //Give egg same position as parent bird, but double x velocity
                entities[egg].x = entities[i].x;
                entities[egg].y = entities[i].y;
                entities[egg].xvel = entities[i].xvel*2;
                entities[egg].yvel = entities[i].yvel;
                entities[egg].status = STATUS_UNDYING;// Just a normal egg
                entities[egg].anim = 0;// Reset animation, as we use this to animate the spawning
              }
            }//If enemy is higher, player dies
            else if( entities[index].y/8 > entities[i].y/8 ){
              arduboy.print(F("PLAY"));
              entities[index].status = STATUS_DEAD;
              lives--;
              survival_bonus = 0;
            }
            //If they are even, they just bounce
          }
          //If the colliding entities are the enemy and the player
          else if( (entities[i].type == TYPE_PLAYER && entities[index].type == TYPE_ENEMY) ){
            //If enemy is higher, player dies
            if( entities[index].y/8 < entities[i].y/8 ){
              arduboy.print(F("PLAY"));
              entities[i].status = STATUS_DEAD;
              lives--;
              survival_bonus = 0;
            }//If player is higher, enemy dies
            else if( entities[index].y/8 > entities[i].y/8 ){
              arduboy.print(F("ENEM"));
              entities[index].status = STATUS_DEAD;
              addScore(POINTS_BIRD);
              egg = -1;
              if( egg_timer < EGG_LIMIT ){
                egg = trySpawn(TYPE_EGG);
              }
              //If egg successfully spawned (if not, just silently fail to spawn egg)
              if( egg != -1 ){
                //Give egg same position as parent bird, but double x velocity
                entities[egg].x = entities[index].x;
                entities[egg].y = entities[index].y;
                entities[egg].xvel = entities[index].xvel*2;
                entities[egg].yvel = entities[index].yvel;
                entities[egg].status = STATUS_UNDYING;// Just a normal egg
                entities[egg].anim = 0;// Reset animation, as we use this to animate the spawning
              }
            }
            //If they are even, they just bounce
          }
          //If the colliding entities are the player and an egg
          else if( (entities[index].type == TYPE_PLAYER && entities[i].type == TYPE_EGG) ){
            entities[i].type = TYPE_NULL;//Immediately despawn the egg
            addScore(POINTS_EGG);
          }
          if(index == 0) arduboy.print(F("HIT"));
        }
      }
    }
  }
}

/*
 * Check if player is colliding with world geometry from its x movement
 */
uint8_t checkWorldX(uint8_t i){
  uint8_t y;
  uint16_t x;
  //Check y coordinates 1 pixel in from top and bottom
  for( y = 1; y <= 7; y++ ){
    //Check collision 2 pixels in from each side (but don't check collision if it's offscreen)
    x = (uint16_t)(entities[i].x + entities[i].xvel)/8;
    if( x+8 < 128 && x-8 < 256 && ( arduboy.getPixel(x+2, (uint16_t)entities[i].y/8+y) == WHITE ||
        arduboy.getPixel(x+6, (uint16_t)entities[i].y/8+y) == WHITE ) ){
          return 1;
    }
  }
  return 0;
}

/*
 * Check if player is colliding with world geometry from its y movement
 */
uint8_t checkWorldY(uint8_t i){
  uint8_t y;
  //Check y coordinates 1 pixel in from top and bottom
  for( y = 1; y <= 7; y++ ){
    //Check collision 2 pixels in from each side
    if( arduboy.getPixel((uint16_t)entities[i].x/8+2, (uint16_t)(entities[i].y + entities[i].yvel)/8+y) == WHITE ||
        arduboy.getPixel((uint16_t)entities[i].x/8+6, (uint16_t)(entities[i].y + entities[i].yvel)/8+y) == WHITE ){
          return 1;
    }
  }
  return 0;
}

/*
 * Step movement for entities, checking world and entity collision.
 * This does not include the inputs by the entity (AI or player input).
 */
void stepEntity(uint8_t index){
  //Check if currently spawning.  If so, do not interact with other entities.
  if( entities[index].type != TYPE_EGG && entities[index].status == STATUS_UNDYING ){
    return;//No collision tests while spawning
  }

  //Check if entity is dead.  If so, ignore collision with other entities
  if( entities[index].status == STATUS_DEAD ){
    //If dead, attempt to run to the edge of the screen
    //Random flaps
    if( rand()%6 == 0 ){
      entities[index].yvel -= 16;
    }
    if( entities[index].x < (SCREEN_WIDTH*8)/2 ){
      entities[index].xvel -= 2;
    }else{
      entities[index].xvel += 2;
    }
  }else{
    //Test for collision with other entities
    testCollision(index);
  }
  
  //Cap off velocity so we can't go through things
  if( entities[index].yvel > VEL_MAX ) entities[index].yvel = VEL_MAX;
  else if( entities[index].yvel < -VEL_MAX ) entities[index].yvel = -VEL_MAX;
  if( entities[index].xvel > VEL_MAX ) entities[index].xvel = VEL_MAX;
  else if( entities[index].xvel < -VEL_MAX ) entities[index].xvel = -VEL_MAX;

  //Test world collision (x)
  while( entities[index].xvel != 0 && checkWorldX(index) ){
    entities[index].xvel /= -2;
  }
  
  //Test world collision (y)
  while( entities[index].yvel != 0 && ( checkWorldY(index) ||
      (entities[index].y + entities[index].yvel)/8 > (SCREEN_HEIGHT-10) ||
      (entities[index].y + entities[index].yvel) < 0 ) ){
    //Bounce if travelling upwards, but just stop if going down (so you don't bounce on landing)
    if( entities[index].yvel < 0 ){
      entities[index].yvel /= -2;
    }else{
      entities[index].yvel /= 2;
    }
  }

  //Free if get stuck (but only if not offscreen, because offscreen we can't reliably check collision)
  if( entities[index].x > 0 && entities[index].x < (128-8)*8 && checkWorldY(index) ){
     entities[index].yvel -= 4;
   }
  
  entities[index].x += (int16_t)entities[index].xvel;
  entities[index].y += (int16_t)entities[index].yvel;

   //If get stuck above screen, force into screen
   if( (entities[index].y) < 0 ){
     entities[index].y = 0;
   }

  //Wrap left and right
  if( entities[index].x > (SCREEN_WIDTH-4)*8 ){
    if( entities[index].status == STATUS_DEAD ){
      if( entities[index].type == TYPE_PLAYER ){
        if( lives > 0 ){
          spawnBird(index); //Respawn player
        }else{
          game_mode = MODE_DEAD; //GAME OVER
        }
      }else{
        entities[index].type = TYPE_NULL;//Despawn
      }
    }else{
      entities[index].x -= (SCREEN_WIDTH)*8;
    }
  }
  else if( entities[index].x+(8*4) < 0 ){
    if( entities[index].status == STATUS_DEAD ){
      if( entities[index].type == TYPE_PLAYER ){
        if( lives > 0 ){
          spawnBird(index); //Respawn player
        }else{
          game_mode = MODE_DEAD; //GAME OVER
        }
      }else{
        entities[index].type = TYPE_NULL;//Despawn
      }
    }else{
      entities[index].x += (SCREEN_WIDTH)*8;
    }
  }
}

/*
 * Check player inputs and determine how they will attempt
 * to influence the player's velocity.  This may be overridden
 * by stepEntity if the player cannot move to where they are attempting.
 */
void stepPlayer(uint8_t index){
  entities[index].skid = 0;

  if( entities[index].status == STATUS_DEAD ){
    return;//No moving while dead
  }

  //If player is touching the lava, they die
  if( entities[index].y >= (62-8)*8 ){
    entities[index].status = STATUS_DEAD;
    lives--;
    survival_bonus = 0;
  }

  uint8_t state = arduboy.buttonsState();

  if( entities[index].status == STATUS_UNDYING ){
    // No moving while spawning until after the animation finishes.
    // After that, stay invincible until the player presses any button
    if( entities[index].anim >= 32 && state ){
      entities[index].status = STATUS_NORMAL; //Finish spawning
    }else{
      return;
    }
  }

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
    
  if( entities[index].status == STATUS_DEAD ){
    return;//No moving while dead
  }

  if( entities[index].status == STATUS_UNDYING ){
    // No moving while spawning
    // If spawn animation is done, remove invulnerability
    if( entities[index].anim == 32 ){
      entities[index].status = STATUS_NORMAL; // Finish spawning
    }else{
      return;
    }
  }
  
  //Flap hard if close to lava
  if( entities[index].y > (58-8)*8 ){
    entities[index].yvel -= 32;
  }
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
    if( entities[index].xvel > -ENEMY_VEL_MAX - enemy_speed_bonus ){
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
    if( entities[index].xvel < ENEMY_VEL_MAX + enemy_speed_bonus ){
      entities[index].xvel += 2;
    }
  }
  entities[index].yvel += GRAVITY;
}

void stepEgg(uint8_t index){
  entities[index].yvel += GRAVITY;
  //Apply friction to egg
  if( entities[index].xvel > 0 ){
    entities[index].xvel--;
  }else if( entities[index].xvel < 0 ){
    entities[index].xvel++;
  }
  //If the animation indicates that egg invulnerability should have worn off
  if( entities[index].anim >= 16 ){
    entities[index].status = STATUS_NORMAL;
  }
  //If the animation indicates the egg should hatch
  if( entities[index].anim == 255 ){
    entities[index].type = TYPE_ENEMY;//Despawn egg, spawn enemy
    entities[index].status = STATUS_NORMAL;
  }
}

void stepWave(uint8_t all_dead){
  int8_t spawned, w;
  wave_timer++;
  if( wave_spawn_count > 0 ){
    if( wave_timer%10 == 0 ){
      spawned = trySpawn(wave_spawn_type);
      if( spawned != -1 ){ //If it found a slot for the entity
        if( entities[spawned].type == TYPE_ENEMY ){
          spawnBird(spawned);
        }else{
          spawnEgg(spawned);
        }
        wave_spawn_count--;
      }
    }
  }
  /*
   * If all enemies are dead and we're not already spawning,
   * time to start the new spawn
   */
  else if( all_dead ){
    //Check if the player survived the previous wave without dying
    //If so, give them bonus points!
    if( survival_bonus ){
      addScore(POINTS_SURVIVE);
    }
    wave_timer = 0;
    egg_timer = 0;
    w = wave % 10;
    //If it's the first wave of a new set of waves,
    //And if we are above wave 39 (displayed as wave 40)
    if( wave >= 40 && w == 0 ){
      enemy_speed_bonus += 2;// Give enemies speed boost
    }
    switch( w ){
      case 5:
      case 7:
        //Reduce amount of enemies after egg waves by 1
        //So that we have the progression: 1,2,3,4,5 eggs,5,6,7,8,8 eggs
        w--;
      case 0:
      case 2:
        //Standard wave
        wave_spawn_type = TYPE_ENEMY;
        wave_spawn_count = w > 7 ? 8 : w+1;
        survival_bonus = 0;
        break;
      case 6:
      case 8:
        //Reduce amount of enemies after egg waves by 1
        //So that we have the progression: 1,2,3,4,5 eggs,5,6,7,8,8 eggs
        w--;
      case 1:
      case 3:
        //Survival wave
        wave_spawn_type = TYPE_ENEMY;
        wave_spawn_count = w > 7 ? 8 : w+1;
        survival_bonus = 1;
        break;
      case 4:
      case 9:
        //Egg wave
        wave_spawn_type = TYPE_EGG;
        wave_spawn_count = wave > 7 ? 8 : wave+1;
        survival_bonus = 0;
        break;
    }
    wave++;
  }
}

void stepDead(){
  uint8_t state = arduboy.buttonsState();
  if( A_BUTTON & state ){
    a_held = 1;
  }else{
    // Only register A button if it was previously held but is not held now
    // If A was pressed, either enter highscore entry mode if player has a highscore,
    // or go straight to title if not.
    if( a_held ){
      if( isHighscore(score) ){
        game_mode = MODE_HIGHSCORE;
      }else{
        game_mode = MODE_TITLE;
        title_animation = 128; // Jump to highscores part of title
      }
    }
    a_held = 0;
  }
}

void stepHighscoreEntry(){
  uint8_t state = arduboy.buttonsState();

  if( state ){
    button_held++;
  }
  if( A_BUTTON & state ){
    a_held = 1;
  }else{
    // Only register A button if it was previously held but is not held now
    // Advance cursor, but if we are on the last initial, accept initials and return to title
    if( a_held ){
      initials_cursor++;
      if( initials_cursor == 3 ){
        initials_cursor = 0;
        addHighscore( score, score_initials );
        saveHighscores(); // Save to EEPROM
        game_mode = MODE_TITLE;
        a_held = 0;
        button_held = 0;
        title_animation = 128; // Jump to highscores part of title
        return;
      }
    }
    a_held = 0;
  }
  //Button must be held for at least two frames
  if( button_held < 2 ){
    return;
  }
  button_held = 0;

  // Cycle through letters
  if( UP_BUTTON & state ){
    score_initials[initials_cursor]--;
  }else if( DOWN_BUTTON & state ){
    score_initials[initials_cursor]++;
  }

  // Cycle through initials position
  if( LEFT_BUTTON & state ){
    initials_cursor = initials_cursor > 0 ? initials_cursor - 1 : 2;
  }else if( RIGHT_BUTTON & state ){
    initials_cursor++;
    initials_cursor %= 3;
  }

}

void stepTitle(){
  uint8_t i;
  uint8_t state = arduboy.buttonsState();
  if( A_BUTTON & state ){
    // Reset lives and score
    lives = 5;
    score = 0;
    // Reset player
    entities[0].type = TYPE_PLAYER;
    entities[0].status = STATUS_NORMAL;
    entities[0].x = 8*52;
    entities[0].y = 8*25;
    entities[0].xvel = 0;
    entities[0].yvel = 0;
    // Reset waves
    wave = 0;
    wave_spawn_count = 0;
    // Reset entities
    for( i = 1; i < NUM_ENTITIES; i++ ){
      entities[i].type = TYPE_NULL;
    }
    //Reset enemy speed bonus
    enemy_speed_bonus = 0;
    
    game_mode = MODE_GAME;
  }
}

void stepGame(){
  uint8_t i,all_dead;
  switch( game_mode ){
    case MODE_TITLE:
      stepTitle();
      break;
    case MODE_GAME:
      all_dead = 1;
      if( egg_timer < EGG_LIMIT ){
        egg_timer++;
      }
      for( i = 0; i < NUM_ENTITIES; i++ ){
        switch( entities[i].type ){
          case TYPE_PLAYER:
            stepPlayer(i);
            stepEntity(i);
            break;
          case TYPE_ENEMY:
            stepEnemy(i);
            stepEntity(i);
            all_dead = 0;
            break;
          case TYPE_EGG:
            stepEgg(i);
            stepEntity(i);
            all_dead = 0;
            break;
        }
      }
      stepWave(all_dead);
      break;
    case MODE_DEAD:
      stepDead();
      break;
    case MODE_HIGHSCORE:
      stepHighscoreEntry();
      break;
  }
}
