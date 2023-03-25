#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <vector>
#include "ResourcePath.hpp"

#include "Bat.hpp"
#include "Game.hpp"
#include "Sounds.hpp"
#include "Textures.hpp"


using namespace sf;
using namespace std;

struct Pipe {
    Sprite sprite;


    // Get the bounding box of the pipe
    sf::FloatRect getBoundingBox() const;
    
    
};

struct Line {
    Sprite sprite;
    sf::RectangleShape line;

    Line(sf::Vector2f size, sf::Vector2f position, float rotation) {
        line.setSize(size);
        line.setPosition(position);
        line.setRotation(rotation);
    }

    sf::FloatRect getBoundingBox() const {
        return line.getGlobalBounds();
    }
    void move(float dx, float dy) {
        line.move(dx, dy);
    }
};

//třída řídí průběh hry a obsahuje všechny herní objekty a logiku.
//Třída má několik metod, které jsou zodpovědné za chod hry
//nastavení hry, aktualizace stavu hry, generování a pohyb sloupů,  a vykreslování hry.
class GameController {
public:
    GameController();
    void run();

private:
    void setupGame();
    void loadSounds();
    void loadTextures();
    void initBat();
    void updateBat();
    void updateScore();
    void generatePipes();
    void movePipes();
    void moveLines();
    void draw();
    void handleEvents();
    //bool checkCollision(Sprite sprite1, Sprite sprite2);

    RenderWindow mWindow;
    vector<Pipe> mPipes;
    vector<Line> mLines;
    Game mGame;
    Textures mTextures;
    Bat mBat;
    Sounds mSounds;
    
};

