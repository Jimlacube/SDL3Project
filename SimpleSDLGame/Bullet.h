#pragma once
#include "Entity.h"
#include "Rect.h"

class Bullet : public Entity
{
public:
	//Public functions
	Bullet()
	{
		Init();
	}
	
	void Init() override;
	void Update(float delta) override;

	Rect bulletRect = Rect();
};

