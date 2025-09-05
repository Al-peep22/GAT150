#pragma once

// Core
#include "Core/Factory.h"
#include "Core/File.h"
#include "Core/Json.h"
#include "Core/Logger.h"
#include "Core/Random.h"
#include "Core/Singleton.h"
#include "Core/StringHelper.h"
#include "Core/Time.h"

// Framework
#include "Framework/Actor.h"
#include "Framework/Game.h"
#include "Framework/Object.h"
#include "Framework/Scene.h"

// Math
#include "Math/Math.h"
#include "Math/Rect.h"
#include "Math/Transform.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"

// Physics
#include "Physics/Collidable.h"
#include "Physics/Physics.h"
#include "Physics/PhysicsBody.h"

// Resources
#include "Resources/Resource.h"
#include "Resources/ResourceManager.h"

// Third-party Library
#include <fmod.hpp>
#include <fmod_errors.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

// Standard Library
#include <algorithm>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <map>
#include <memory>
#include <random>
#include <vector>

// Event Manager
#include "Event/Event.h"
#include "Event/EventManager.h"
#include "Event/Observer.h"