#pragma once
#include <SDL3/SDL_render.h>

#include "Entity.h"
#include "Vectors.h"

class Object : public Entity
{
public:
	Object();
	Object(Vector2 pos, Vector2 dir);

	void CollisionUpdate(float delta, Rect collisionRect, Vector2 newPosition);
	//TODO move to object class
	bool checkCollision(const Object* objectA, const Object* objectB);
	
	Vector2 position;
	Vector2 direction;
	SDL_FRect collider;
};

