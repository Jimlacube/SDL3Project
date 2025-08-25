#pragma once
#include <SDL3/SDL_render.h>

class Entity
{
public:

	Entity()
	{
		Init();
	}
	~Entity() = default;

	bool bIsPendingDestroy = false;

	virtual void Init();
	virtual void Render(SDL_Renderer* renderer);
	virtual void Update(float delta);
	virtual void Destroy();

};