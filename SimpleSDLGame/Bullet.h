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

	Rect bulletRect = Rect();
	float bulletSize = 20.0f;
};

