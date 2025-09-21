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
	SDL_RenderFillRect(localRenderer, &localBullet);
	SDL_RenderRect(localRenderer, &localBullet);
}

void Bullet::Update(float delta)
{
	if (lifetime <= 0.0f)
	{
		Explode(delta);
		return;
	}
	lifetime -= delta;
	
	position += velocity * delta;
	bulletRect.SetRectLocation(position);

	velocity *= 0.99f;

	if (bIsOutOfBounds())
	{
		Destroy();
	}
}

void Bullet::Explode(float delta)
{
	if (explodeTime <= 0.0f)
	{
		Destroy();
		return;
	}
	explodeTime -= delta;
	
	bulletSize += 200.0f * delta;
	bulletRect.SetRectSizeCenter(bulletSize);	
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
