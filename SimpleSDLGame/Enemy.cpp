#include "Enemy.h"

#include <SDL3/SDL_render.h>

#include "Utilities.h"

Enemy::Enemy()
{
    enemyRect.SetRectSize(50.0f);
    
    //position = Vector2((float)(Utilities::GetScreenBounds().X) * SDL_randf(), (float)(Utilities::GetScreenBounds().Y) * SDL_randf());
    position = Vector2(200.0f);
    enemyRect.SetRectLocation(position);
    collider = Utilities::ConvertRect(enemyRect);
}

void Enemy::Render(struct SDL_Renderer& renderer)
{
    SDL_Renderer* localRenderer = &renderer;
    if (!localRenderer)
    {
        return;
    }

    SDL_SetRenderDrawColor(localRenderer, 0, 0, 255, 1);
    
    SDL_FRect localEnemy = Utilities::ConvertRect(enemyRect);
    SDL_RenderFillRect(localRenderer, &localEnemy);
    SDL_RenderRect(localRenderer, &localEnemy);
}

void Enemy::Update(float delta)
{
    
}
