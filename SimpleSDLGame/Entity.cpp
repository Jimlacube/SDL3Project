#include "Entity.h"

Entity::Entity()
{
}

void Entity::Render(struct SDL_Renderer& renderer)
{
}

void Entity::Update(float delta)
{

}

void Entity::Destroy()
{
	bIsPendingDestroy = true;
}
