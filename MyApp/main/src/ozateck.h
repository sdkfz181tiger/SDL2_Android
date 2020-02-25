//==========
// SDL
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "SDL_log.h"
#include "SDL2_gfxPrimitives.h"

//==========
// Utilities
#include "utility/UtilImagePool.h"
#include "utility/UtilLevelData.h"
#include "utility/UtilLocalSaves.h"
#include "utility/UtilMath.h"
#include "utility/UtilSoundPool.h"
#include "utility/UtilThread.h"
#include "utility/UtilTimer.h"
#include "utility/UtilTtf.h"
#include "utility/Vec2.h"

//==========
// Other
#include "utility/json11/json11.hpp"
#include "utility/tweeny/tweeny.h"

//==========
// C++
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <math.h>
#include <random>
#include <string>
#include <time.h>

using namespace std;
using namespace json11;
using tweeny::easing;