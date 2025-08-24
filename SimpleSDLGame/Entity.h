#pragma once

class Entity
{
public:

	Entity()
	{
		Init();
	}
	~Entity() = default;

	virtual void Init();
	virtual void Update(float delta);

};