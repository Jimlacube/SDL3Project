#pragma once
#include "Object.h"
#include "Rect.h"

class Bullet : public Object
{
	//Public functions
public:
	Bullet() = delete;
	Bullet(Vector2 pos, Vector2 dir) : Object(pos, dir)
	{
		bulletRect.SetRectSize(bulletSize);
		
		//TODO swap this out for velocity
		const float bulletSpeed = 50.0f;
		velocity = dir * bulletSpeed;
		position = pos;		
	}

	void Render(struct SDL_Renderer& renderer) override;
	void Update(float delta) override;

//	void SetDirection(Vector2 direction);

	Rect bulletRect = Rect();
	const float bulletSize = 20.0f;

protected:
	bool bIsOutOfBounds();

	Vector2 direction = Vector2(1.0f);
	Vector2 velocity = 0.0f;
};

