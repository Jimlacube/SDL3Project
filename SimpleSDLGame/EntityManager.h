#pragma once
#include <vector>

#include "Entity.h"


class EntityManager
{
	static std::vector<Entity*> Entities;
public:
	EntityManager();
	~EntityManager() = default;

	static void CheckForPendingDestroy();

	static std::vector<Entity*> GetEntities();

	template<class T>
	static T* Spawn()
	{
		//TODO change for smart pointer
		T* ent = new T();
		AddEntity(ent);
		return ent;
	}

private:
	static void AddEntity(Entity* newEntity);
};

