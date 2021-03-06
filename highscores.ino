#include <EEPROM.h>

#define SAVE_BASE 709

char score_initials[3] = {'A','A','A'};
uint8_t initials_cursor;

struct highscore_table highscores;

void loadHighscores(){
  uint8_t i,j;
  //Magic number J
  if( EEPROM.read(SAVE_BASE) == 'J' ){
    for( i = 0; i < NUM_HIGHSCORES; i++ ){
      for( j = 0; j < 3; j++ ){
        highscores.initials[i][j] = EEPROM.read(SAVE_BASE + 1 + 3*i + j);
      }
    }
    for( i = 0; i < NUM_HIGHSCORES; i++ ){
      EEPROM.get(SAVE_BASE + 1 + (3*NUM_HIGHSCORES) + 4*i, highscores.scores[i]); 
    }
  }
}

void saveHighscores(){
  uint8_t i,j;
  EEPROM.update(SAVE_BASE, 'J');
  for( i = 0; i < NUM_HIGHSCORES; i++ ){
    for( j = 0; j < 3; j++ ){
      EEPROM.update(SAVE_BASE + 1 + 3*i + j, highscores.initials[i][j]);
    }
  }
  for( i = 0; i < NUM_HIGHSCORES; i++ ){
    EEPROM.put(SAVE_BASE + 1 + (3*NUM_HIGHSCORES) + 4*i, highscores.scores[i]); 
  }
}

uint8_t isHighscore(uint32_t score){
  int8_t i;
  for( i = 0; i < NUM_HIGHSCORES; i++ ){
    if( (uint32_t)highscores.scores[i] < score ){
      return 1;
    }
  }
  return 0;
}

void addHighscore(uint32_t score, char inits[3]){
  int8_t i,j;
  for( i = NUM_HIGHSCORES-1; i >= 0; i-- ){
    if( i < NUM_HIGHSCORES-1 ){
      //If not the last score, move the current score down
      for( j = 0; j < 3; j++ ){
        highscores.initials[i+1][j] = highscores.initials[i][j];
      }
      highscores.scores[i+1] = highscores.scores[i];
    }
    if( i == 0 || (uint32_t)highscores.scores[i-1] > score ){
      //Write our score here
      for( j = 0; j < 3; j++ ){
        highscores.initials[i][j] = inits[j];
      }
      highscores.scores[i] = score;
      return;
    }
  }
}

