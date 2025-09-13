#pragma once
#include "Object.h"
#include "Rect.h"

class Player : public Object
{
public:
	
	//Public functions
	Player();
		
	void Render(struct SDL_Renderer& renderer) override;
	void Update(float delta) override;

	//Public variables
	Rect playerRect = Rect();

private:

	//Private functions
	void KeyStateUpdate();

	void StartDash();
	float UpdateDashSpeed(float delta, float timeToComplete = 0.3f);

	//Private variables
	Vector2 InputXY = Vector2();

	float rectSize = 20.0f;
	float speed = 100.0f;

	//Dash
	bool bIsDashing;
	bool bDashReady;
	float dashSpeed = 1.0f;
	float dashDistance = 0.0f;
	float dashTimeRemaining = 0.0f;
	Vector2 lastDash = Vector2();
};

