#pragma once
#include <SDL3/SDL_rect.h>

#include "Object.h"
#include "Rect.h"

class Player : public Object
{
public:
	
	//Public functions
	Player();
		
	void Render(struct SDL_Renderer& renderer) override;
	void Update(float delta) override;

	void CollisionUpdate(float delta, Vector2 axis);

	//TODO move to object class
	bool checkCollision(const Object* objectA, const Object* objectB);
	
	//Public variables
	Rect playerRect = Rect();

private:

	//Private functions
	void KeyStateUpdate();

	void StartDash();
	float UpdateDashSpeed(float delta, float timeToComplete = 0.3f);

	void UpdateFiringCooldown(float delta);

	//Private variables
	Vector2 inputXY = Vector2();

	float rectSize = 20.0f;
	float speed = 50.0f;

	//Dash
	bool bIsDashing;
	bool bIsDashReady;
	float dashSpeed = 1.0f;
	float dashDistance = 0.0f;
	float dashTimeRemaining = 0.0f;
	Vector2 lastDash = Vector2();

	//Direction
	Vector2 lastInputDir = Vector2(1.0f,0.0f);

	//Firing
	bool bIsFiring = false;
	const float firingCooldown = 0.5f;
	float firingTimeRemaining;
};