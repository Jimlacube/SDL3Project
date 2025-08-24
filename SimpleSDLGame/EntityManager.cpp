#include "EntityManager.h"

vector<Entity*> EntityManager::Entities;

EntityManager::EntityManager()
{
    
}

Entity* EntityManager::SpawnEntity()
{
    Entity* newEntity = new Entity();
    Entities.push_back(newEntity);
    return newEntity;
}

vector<Entity*> EntityManager::GetEntities()
{
    return Entities;
}
