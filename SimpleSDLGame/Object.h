#pragma once
#include <SDL3/SDL_render.h>

#include "Entity.h"
#include "Vectors.h"

class Object : public Entity
{
public:
	Object();
	Object(Vector2 pos, Vector2 dir);
	
	Vector2 position;
	Vector2 direction;
	SDL_FRect collider;
};

