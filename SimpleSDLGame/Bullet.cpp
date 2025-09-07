#include <SDL3/SDL_render.h>

#include "Bullet.h"
#include "Utilities.h"

void Bullet::Init()
{
	bulletRect.SetRectSize(bulletSize);
	newPosition = bulletRect.GetRectLocation();
}

void Bullet::Render(struct SDL_Renderer& renderer)
{
	SDL_Renderer* localRenderer = &renderer;
	if (!localRenderer)
	{
		return;
	}

	SDL_SetRenderDrawColor(localRenderer, 0, 255, 0, 1);

	SDL_FRect localBullet{};
	localBullet = Utilities::ConvertRect(bulletRect);
	SDL_RenderRect(localRenderer, &localBullet);
}

void Bullet::Update(float delta)
{
	bulletRect.SetRectLocation(newPosition);
	newPosition = bulletRect.GetRectLocation();
	newPosition += initDirection * bulletSpeed;

	if (bIsOutOfBounds())
	{
		Destroy();
	}
}

void Bullet::SetDirection(Vector2 direction)
{
	initDirection = direction;
}

bool Bullet::bIsOutOfBounds()
{
	float boundsOuter = bulletSize + 10.0f;
	Vector2 position = bulletRect.GetRectLocation();
	Vector2_int bounds = Utilities::GetScreenBounds();
	if (position.Y < -boundsOuter || position.Y > bounds.Y + boundsOuter || position.X < -boundsOuter || position.X > bounds.X + boundsOuter)
	{
		return true;
	}

	return false;
}
