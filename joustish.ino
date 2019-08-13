#include <Arduboy2.h>

#include "game.h"
#include "draw.h"
#include "highscores.h"

Arduboy2 arduboy;

void setup() {
  arduboy.begin();

  // Framerate at 15 fps, which hopefully is smooth enough, because
  // the game speed is tied to framerate, so changing it would alter
  // the gameplay significantly
  arduboy.setFrameRate(60);

  loadHighscores();
  
  game_mode = MODE_TITLE;
}

void loop() {
  if (!(arduboy.nextFrame()))
    return;

  arduboy.clear();
  arduboy.pollButtons();
  
  //Render background first so we can use it for collision
  drawBackground();
  stepGame();
  drawGame();

  arduboy.display();
}
