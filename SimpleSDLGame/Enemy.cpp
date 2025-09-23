#include "Enemy.h"

#include <SDL3/SDL_render.h>

#include "Utilities.h"

Enemy::Enemy()
{
    enemyRect.SetRectSizeCenter(50.0f);
    
    position = Vector2((float)(Utilities::GetScreenBounds().X) * SDL_randf(), (float)(Utilities::GetScreenBounds().Y) * SDL_randf());
    enemyRect.SetRectLocation(position);
}

void Enemy::Render(struct SDL_Renderer& renderer)
{
    SDL_Renderer* localRenderer = &renderer;
    if (!localRenderer)
    {
        return;
    }

    SDL_SetRenderDrawColor(localRenderer, 0, 0, 255, 1);

    SDL_FRect enemy{};
    enemy = Utilities::ConvertRect(enemyRect);
    SDL_RenderFillRect(localRenderer, &enemy);
    SDL_RenderRect(localRenderer, &enemy);
}

void Enemy::Update(float delta)
{
    
}
