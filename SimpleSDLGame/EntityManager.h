#pragma once
#include <vector>

#include "Entity.h"

using std::vector;

class EntityManager
{
	static vector<Entity*> Entities;
public:
	EntityManager();
	~EntityManager() = default;

	static Entity* SpawnEntity();

	static vector<Entity*> GetEntities();
};

