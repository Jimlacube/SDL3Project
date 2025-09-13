#pragma once
#include "Entity.h"
#include "Vectors.h"

class Object : public Entity
{
public:
	Object();
	Object(Vector2 pos, Vector2 dir);
	
	Vector2 position;
	Vector2 direction;
};

