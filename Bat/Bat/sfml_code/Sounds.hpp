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


class Sounds {
public:
    SoundBuffer scoreBuffer;
    SoundBuffer flapBuffer;
    SoundBuffer crashBuffer;
    Sound score;
    Sound flap;
    Sound crash;
};
