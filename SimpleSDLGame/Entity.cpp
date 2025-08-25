#include "Entity.h"

void Entity::Init()
{

}

void Entity::Render(SDL_Renderer* renderer)
{
}

void Entity::Update(float delta)
{

}

void Entity::Destroy()
{
	bIsPendingDestroy = true;
}
