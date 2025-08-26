#include "EntityManager.h"

vector<Entity*> EntityManager::Entities;

EntityManager::EntityManager()
{
    
}

//Entity* EntityManager::SpawnEntity()
//{
//    Entity* newEntity = new Entity();
//    Entities.push_back(newEntity);
//    return newEntity;
//}

void EntityManager::AddEntity(Entity* newEntity)
{
    Entities.push_back(newEntity);
}

void EntityManager::CheckForPendingDestroy()
{
    for (int i = 0; i < Entities.size(); ++i)
    {
        Entity* currentEntity = Entities[i];
        if (currentEntity->bIsPendingDestroy)
        {
            delete currentEntity;
            currentEntity = nullptr;
            Entities[i] = Entities[Entities.size() - 1];
            Entities.pop_back();
            --i;
        }
    }
}

vector<Entity*> EntityManager::GetEntities()
{
    return Entities;
}