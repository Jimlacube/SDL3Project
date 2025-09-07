#pragma once

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
	virtual void Render(struct SDL_Renderer& renderer);
	virtual void Update(float delta);
	virtual void Destroy();

};