//==========
// Vec2
#include "Vec2.h"

//==========
// SDL
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_thread.h"
#include "SDL_timer.h"
#include "SDL_ttf.h"
#include "SDL_log.h"
#include "SDL2_gfxPrimitives.h"

//==========
// Other
#include "json11/json11.hpp"
#include "tweeny/tweeny.h"

//==========
// C++
#include <algorithm>
#include <ctime>
#include <chrono>
#include <functional>
#include <locale>
#include <map>
#include <math.h>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>

using namespace std;
using namespace json11;
using tweeny::easing;