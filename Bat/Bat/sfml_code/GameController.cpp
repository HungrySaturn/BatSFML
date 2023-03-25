#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <vector>
#include "ResourcePath.hpp"


#include "GameController.hpp"
using namespace sf;
using namespace std;




GameController::GameController()
    : mWindow(VideoMode(1000, 600), "Bat")
{
}
//metoda je hlavní herní smyčka, která se spouští při otevřeném okně hry.
//V každém snímku aktualizuje skóre, netopýra, sloupy a lajny a poté zpracovává události
//a vykresluje hru.
void GameController::run()
{
    
    setupGame();
    
    while (mWindow.isOpen()) {
        updateScore();
        updateBat();
        generatePipes();
        movePipes();
        moveLines();
        handleEvents();
        draw();
    }
}

//metoda nastaví počáteční stav hry, načte textury a texty
void GameController::setupGame()
{
    mWindow.setFramerateLimit(60);
    mWindow.setKeyRepeatEnabled(false);
    
    // načtení textur
    loadTextures();
    loadSounds();
    initBat();
    mGame.font.loadFromFile(resourcePath() + "bat.ttf");
    
    // nastavení pozadí
    mGame.background.setTexture(mTextures.background);

    // gameover text
    mGame.gameover.setTexture(mTextures.gameover);
    mGame.gameover.setPosition(280, 200);
    mGame.gameover.setScale(2, 2);

    // restart text
    mGame.restart.setFont(mGame.font);
    mGame.restart.setString("Press N to start");
    mGame.restart.setCharacterSize(30);
    mGame.restart.setPosition(350, 300);

    // nastavení - skore text
    mGame.scoreText.setFont(mGame.font);
    mGame.scoreText.setCharacterSize(50);
    mGame.scoreText.setPosition(10, 10);

    // nastaveni - highscore text
    mGame.highscoreText.setFont(mGame.font);
    mGame.highscoreText.setCharacterSize(30);
    mGame.highscoreText.setPosition(30, 80);

    // pocateni stav hry
    mGame.gameState = waiting;

    // gen. náhodných čísel
    srand(time(NULL));
}

//metoda načte všechny herní textury
void GameController::loadTextures()
{
    mTextures.bat[0].loadFromFile(resourcePath() + "bat1.png");
    mTextures.bat[1].loadFromFile(resourcePath() + "bat2.png");
    mTextures.bat[2].loadFromFile(resourcePath() + "bat3.png");
    mTextures.pipe.loadFromFile(resourcePath() + "stalagmite.png");
    mTextures.background.loadFromFile(resourcePath() + "cave.jpg");
    mTextures.gameover.loadFromFile(resourcePath() +"gameover.png");
}

//metoda načte všechny herní zvuky
void GameController::loadSounds()
{
    mSounds.scoreBuffer.loadFromFile(resourcePath() +"score.wav");
    mSounds.flapBuffer.loadFromFile(resourcePath() +"flap.wav");
    mSounds.crashBuffer.loadFromFile(resourcePath() +"crash.wav");
    mSounds.score.setBuffer(mSounds.scoreBuffer);
    mSounds.flap.setBuffer(mSounds.flapBuffer);
    mSounds.crash.setBuffer(mSounds.crashBuffer);
}

//metoda inicializuje objekt netopýra nastavením jeho počáteční rychlosti, snímku, spritu, pozice a měřítka.
void GameController::initBat()
{
    mBat.v = 0;
    mBat.frame = 0;
    mBat.sprite.setTexture(mTextures.bat[0]);
    mBat.sprite.setPosition(250, 300);
    mBat.sprite.setScale(2, 2);
    
}
//metoda aktualizuje objekt netopýra
//mění jeho texturu, posune ho podle jeho rychlosti a aktualizuje jeho rychlost podle gravitace.
//Kontroluje také kolize se stropem a zemí a nastaví stav hry na konec, pokud netopýr narazí na zem
void GameController::updateBat()

{
    // update flappy
    float by = mBat.sprite.getPosition().y;
   
    
    if (mGame.gameState == waiting || mGame.gameState == started) {

        // mění texturu každých 6 snímků
        if (mGame.frames % 6 == 0) {
            mBat.frame += 1;
        }
        //
        if (mBat.frame == 3) {
            mBat.frame = 0;
        }
    }
    
    mBat.sprite.setTexture(mTextures.bat[mBat.frame]);

    // move flappy
    if (mGame.gameState == started) {
        mBat.sprite.move(0, mBat.v);
        mBat.v += 0.6;
    }
    
    if (mGame.gameState == started) {
        if (by < 0) {
            mBat.sprite.setPosition(250, 0);
            mBat.v = 0;
        } else if (by > 600) {
            mBat.v = 0;
            mGame.gameState = gameover;
            mSounds.crash.play();
        }
    }
    
        
          
            
        
}
    


    
//metoda aktualizuje texty skóre a nejvyššího skóre a změní texturu netopýra na 2. snímek.

void GameController::updateScore()
{
    mBat.sprite.setTexture(mTextures.bat[1]);
    mGame.scoreText.setString(to_string(mGame.score));
    mGame.highscoreText.setString("Highscore: " + to_string(mGame.highscore));
}

//metoda generuje každých 150 snímků nové sloupy vytvořením dvou sloupových sprites
//dále metoda generuje pomocné přímky, které jsou k detekci kolize
//a jejich přidáním do vektoru mPipes.
//Trubky jsou umístěny náhodně a mají mezi sebou mezeru, která je pevně stanovena na 160 pixelů.
//Horní trubka je převrácena vertikálně pomocí metody setScale se záporným měřítkem Y.
//

void GameController::generatePipes()
{
    
    if (mGame.gameState == started && mGame.frames % 120 == 0) {
        
        int r = rand() % 275 + 75;
        int gap = 160;
        
        // lower pipe
        
        
        Line lineL(sf::Vector2f(335, 5), sf::Vector2f(1150, r+gap+10), 95);
        Line lineP(sf::Vector2f(335, 5), sf::Vector2f(1150, r-10), 265);
        
        // lower pipe
        Pipe pipeL;
        pipeL.sprite.setTexture(mTextures.pipe);
        pipeL.sprite.setPosition(1000, r + gap);
        pipeL.sprite.setScale(2, 2);
        
       
        
        // upper pipe
        Pipe pipeU;
        pipeU.sprite.setTexture(mTextures.pipe);
        pipeU.sprite.setPosition(1000, r);
        pipeU.sprite.setScale(2, -2);

        // push to the array
        
        mPipes.push_back(pipeL);
        mPipes.push_back(pipeU);
        

        
        
        
        // push to the array
        
        
        mLines.push_back(lineL);
        mLines.push_back(lineP);
    }
    
    
        
    }
    
   
        
void GameController::movePipes()
{
    if (mGame.gameState == started) {
        for (vector<Pipe>::iterator itr = mPipes.begin(); itr != mPipes.end(); itr++) {
            (*itr).sprite.move(-3, 0);
            
        }
    
            
        }
    
    // remove pipes if offscreen
    if (mGame.frames % 100 == 0) {
        vector<Pipe>::iterator startitr = mPipes.begin();
        vector<Pipe>::iterator enditr = mPipes.begin();
        

        for (; enditr != mPipes.end(); enditr++) {
            if ((*enditr).sprite.getPosition().x > -140) {
                break;
            }
        }
        

        mPipes.erase(startitr, enditr);
        
    }
}
       
    
void GameController::moveLines()
{
    if (mGame.gameState == started) {
        for (auto& line : mLines) {
            line.move(-3, 0);
            if (249 < line.getBoundingBox().left && line.getBoundingBox().left < 250.822) {
                
                mGame.score++;
                mSounds.score.play();
                cout << line.getBoundingBox().left<< " ";
                
                
            }
            
                
            if (line.getBoundingBox().intersects(mBat.sprite.getGlobalBounds())) {
                    mGame.gameState = gameover;
                    mSounds.crash.play();
                }
            
            if (line.getBoundingBox().left < -line.getBoundingBox().width) {
                mLines.erase(mLines.begin());
                mLines.erase(mLines.begin());
                break;
            }
            
        }
    }
    
}

//metoda je zodpovědná za vykreslování herních objektů a aktualizaci zobrazení herního okna
//Vyčistí okno, vykreslí pozadí, netopýra a sloupy a také skóre a highscore. Pokud je hra ve stavu "game over", zobrazí také zprávu o ukončení hry a zprávu o restartu. Nakonec aktualizuje počet snímků hry a zobrazí aktualizované okno.

void GameController::draw()
{
    mWindow.clear();
    mWindow.draw(mGame.background);
    mWindow.draw(mBat.sprite);

    
    /*
    for (auto& line : mLines) {
            mWindow.draw(line.line);
        }
     
     */
    

    // kresleni sloupu
    
    for (int i = 0; i < mPipes.size(); i++) {
          mWindow.draw(mPipes[i].sprite);
      }
    
    
    
    // skore a highscore
    mWindow.draw(mGame.scoreText);
    mWindow.draw(mGame.highscoreText);

    // gameover
    if (mGame.gameState == gameover) {
        mWindow.draw(mGame.gameover);

        if (mGame.frames % 60 < 30) {
            mWindow.draw(mGame.restart);
        }
    }
    mWindow.display();

    // aktualizuje pocet snimku
    mGame.frames++;
    
}

//metoda je zodpovědná za zpracování vstupních událostí uživatele, jako je stisknutí
//mezerníku pro rozhození netopýra nebo stisknutí klávesy "N" pro restartování hry.
//Pokud uživatel zavře okno, metoda ukončí hru.
//Pokud uživatel stiskne mezerník, když je hra ve stavu "waiting" nebo "started",//
//způsobí klapnutí netopýra a přehraje zvukový efekt. Pokud uživatel stiskne klávesu
//"N", když je hra ve stavu "game over", vynuluje stav hry, skóre a herní objekty.
void GameController::handleEvents()
{
    Event event;
    while (mWindow.pollEvent(event)) {

        // konec
        if (event.type == Event::Closed) {
            mWindow.close();
        }
        
        
        // flap
        else if (event.type == Event::KeyPressed &&
                   event.key.code == Keyboard::Space) {
            if (mGame.gameState == waiting) {
                mGame.gameState = started;
            }
            
            if (mGame.gameState == started) {
                mBat.v = -8;
                mSounds.flap.play();
                
            }
            
            

        // restart
        } else if (event.type == Event::KeyPressed &&
                   event.key.code == Keyboard::N &&
                   mGame.gameState == gameover) {
            mGame.gameState = waiting;
            mBat.sprite.setPosition(250, 300);
            if(mGame.score > mGame.highscore)
                {mGame.highscore = mGame.score;}
            mGame.score = 0;
            mLines.clear();
            mPipes.clear();
        }
    }
}


