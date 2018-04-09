#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#define NUM_HIGHSCORES 5

extern char score_initials[3];
extern uint8_t initials_cursor;

struct highscore_table{
  char initials[NUM_HIGHSCORES][3];
  uint32_t scores[NUM_HIGHSCORES];
};
extern struct highscore_table highscores;

void loadHighscores();
void saveHighscores();
uint8_t isHighscore(uint32_t score);
void addHighscore(uint32_t score, char inits[3]);

#endif
