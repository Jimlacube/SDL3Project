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

	///TODO add inline file
	template<class T, class... Args>
	static T* Create(Args... args);
	
};

template <class T, class... Args>
T* EntityManager::Create(Args... args)
{
	T* ent = new T(args...);
	Entities.push_back(ent);
	return ent;
}

