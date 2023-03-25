#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <vector>
#include "ResourcePath.hpp"

using namespace sf;
using namespace std;

// waiting = ceka na input
// started = bezi
// gameover = bude cekta na input

enum GameState { waiting, started, gameover };

class Game {
public:
    int score = 0;
    int highscore = 0;
    int frames = 0;
    
    GameState gameState = waiting;
    Sprite background;
    Sprite gameover;
    Text restart;
    Text scoreText;
    Text highscoreText;
    Font font;
};

