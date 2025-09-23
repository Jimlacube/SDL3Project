#pragma once
#include <vector>

#include "Entity.h"

class EntityManager
{
	static std::vector<Entity*> entities;
public:
	EntityManager();
	~EntityManager() = default;

	static void CheckForPendingDestroy();

	static std::vector<Entity*> GetEntities();

	///TODO add inline file
	template<class T, class... Args>
	static T* Create(Args... args);
	
	static std::vector<Entity*> SearchEntities(std::string tag);
	
};

template <class T, class... Args>
T* EntityManager::Create(Args... args)
{
	T* ent = new T(args...);
	entities.push_back(ent);
	return ent;
}