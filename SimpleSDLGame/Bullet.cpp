#include "Bullet.h"
#include "Utilities.h"

void Bullet::Init()
{
	bulletRect.SetRectSize(bulletSize);
	bulletRect.SetRectLocation(50.0f);
}

void Bullet::Render(SDL_Renderer* renderer)
{
	if (!renderer)
	{
		return;
	}

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 1);

	SDL_FRect localBullet{};
	localBullet = Utilities::ConvertRect(bulletRect);
	SDL_RenderRect(renderer, &localBullet);
}

void Bullet::Update(float delta)
{
	bulletRect.SetRectLocation(Vector2(bulletRect.X, bulletRect.Y + 5.0f));
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
	if (position.Y < -boundsOuter || position.Y > bounds.Y + boundsOuter || position.X < -boundsOuter || position.X > bounds.X + boundsOuter)
	{
		return true;
	}

	return false;
}
