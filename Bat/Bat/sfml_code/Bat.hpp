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


class Bat {
public:
    double v = 0;
    int frame = 0;
    Sprite sprite;
    
};

