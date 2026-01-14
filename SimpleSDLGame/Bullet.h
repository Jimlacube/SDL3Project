#pragma once
#include "Object.h"
#include "Rect.h"
#include "Utilities.h"

class Bullet : public Object
{
	//Public functions
public:
	Bullet() = delete;
	Bullet(Vector2 pos, Vector2 dir) : Object(pos, dir)
	{
		bulletRect.SetRectSize(bulletSize);
		collider = Utilities::ConvertRect(bulletRect);
		
		bulletRect.SetRectLocation(pos);
		const float bulletSpeed = 300.0f;
		velocity = dir * bulletSpeed;
		position = pos;
		
		EntityTag = "bullet";
	}

	void Render(struct SDL_Renderer& renderer) override;
	void Update(float delta) override;
	void OnHit() override;

	void Explode(float delta);

	Rect bulletRect = Rect();
	float bulletSize = 20.0f;
	
	float lifetime = 3.0f;
	float explodeTime = 0.3f;

protected:
	bool bIsOutOfBounds();
	
	Vector2 velocity;
};

