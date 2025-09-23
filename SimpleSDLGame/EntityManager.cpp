#include "EntityManager.h"

std::vector<Entity*> EntityManager::entities;

EntityManager::EntityManager()
{
    
}

void EntityManager::CheckForPendingDestroy()
{
    for (int i = 0; i < entities.size(); ++i)
    {
        Entity* currentEntity = entities[i];
        if (currentEntity->bIsPendingDestroy)
        {
            delete currentEntity;
            currentEntity = nullptr;
            entities[i] = entities[entities.size() - 1];
            entities.pop_back();
            --i;
        }
    }
}

std::vector<Entity*> EntityManager::GetEntities()
{
    return entities;
}

std::vector<Entity*> EntityManager::SearchEntities(std::string tag)
{
    //TODO make more efficient
    std::vector<Entity*> entitiesWithTag;
    for (Entity* Entities : entities)
    {
        if (Entities->EntityTag == tag)
        {
            entitiesWithTag.push_back(Entities);
        }
    }
    return entitiesWithTag;
}