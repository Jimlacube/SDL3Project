#pragma once
#include "Object.h"
#include "Rect.h"

class Bullet : public Object
{
public:
	//Public functions
	Bullet()
	{
		Init();
	}
	
	void Init() override;
	void Render(SDL_Renderer* renderer) override;
	void Update(float delta) override;

	void SetDirection(Vector2 direction);

	Rect bulletRect = Rect();
	//TODO create a getter for rect size
	float bulletSize = 20.0f;
	float bulletSpeed = 1.01f;

protected:
	bool bIsOutOfBounds();

	Vector2 initDirection = Vector2(1.0f);
	Vector2 newPosition = Vector2(0.0f);

};

