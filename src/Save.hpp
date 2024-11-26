#ifndef SAVE
#define SAVE
#include <iostream>
#include <fstream>
#include "Collidables/Player.hpp"
#include <time.h>
#include <chrono>

typedef struct
{
    int time;       // saved in hex
    const char *name;     // saved in plain text
    Player *player; // every part of the player is saved in plain text
} Save;

void saveGame(Save *save);
Save *loadGame();
Save *createSaveFile();

#endif