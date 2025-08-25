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

	SDL_RenderPresent(renderer);
}

void Bullet::Update(float delta)
{
	//Vector2 newPosition = bulletRect.GetRectLocation() - Vector2(0.0f, 1.0f);
	//bulletRect.SetRectLocation(newPosition);
}
