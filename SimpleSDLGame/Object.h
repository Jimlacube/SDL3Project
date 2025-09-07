#pragma once
#include "Entity.h"
#include "Vectors.h"

class Object : public Entity
{
public:
	Object();
	~Object() = default;

	Object(Vector2 pos);

	Vector2 position;
};

