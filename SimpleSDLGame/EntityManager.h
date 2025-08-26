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

	static void AddEntity(Entity* newEntity);

	static void CheckForPendingDestroy();

	static vector<Entity*> GetEntities();
};

