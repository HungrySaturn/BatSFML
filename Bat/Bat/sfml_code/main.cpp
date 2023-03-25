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

 
int main()
{
    
    GameController gameController;
    gameController.run();
    return EXIT_SUCCESS;
}
