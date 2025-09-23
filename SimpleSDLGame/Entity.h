#pragma once
#include <string>

class Entity
{
public:
	Entity();
	~Entity() = default;

	bool bIsPendingDestroy = false;

	virtual void Render(struct SDL_Renderer& renderer);
	virtual void Update(float delta);
	virtual void Destroy();

	std::string EntityTag = "None";
};
