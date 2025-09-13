#include <SDL3/SDL_render.h>

#include "Bullet.h"
#include "Utilities.h"

void Bullet::Render(struct SDL_Renderer& renderer)
{
	SDL_Renderer* localRenderer = &renderer;
	if (!localRenderer)
	{
		return;
	}

	SDL_SetRenderDrawColor(localRenderer, 0, 255, 0, 1);

	SDL_FRect localBullet = Utilities::ConvertRect(bulletRect);
	SDL_RenderRect(localRenderer, &localBullet);
}

void Bullet::Update(float delta)
{
	position += velocity * delta;
	bulletRect.SetRectLocation(position);

	if (bIsOutOfBounds())
	{
		Destroy();
	}
}

bool Bullet::bIsOutOfBounds()
{
	float boundsOuter = bulletSize + 10.0f;
	Vector2 position = bulletRect.GetRectLocation();
	Vector2_int bounds = Utilities::GetScreenBounds();
	if (position.Y < -boundsOuter || position.Y > (float)bounds.Y + boundsOuter || position.X < -boundsOuter || position.X > (float)bounds.X + boundsOuter)
	{
		return true;
	}

	return false;
}
