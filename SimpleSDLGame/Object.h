#pragma once
#include <vector>
#include <SDL3/SDL_render.h>

#include "Entity.h"
#include "Vectors.h"

class Rect;

class Object : public Entity
{
public:
	Object();
	Object(Vector2 pos, Vector2 dir);

	Object* CollisionUpdate(Rect collisionRect, Vector2 newPosition, std::string tagToIgnore = "");
	bool checkCollision(const Object* objectA, const Object* objectB);
	virtual void OnHit(Object* hitObject);
	
	Vector2 position;
	Vector2 direction;
	SDL_FRect collider;
};

