#include "Player.h"

#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_render.h>

#include "Vectors.h"
#include "EntityManager.h"
#include "Bullet.h"
#include "Utilities.h"

Player::Player()
{
    playerRect.SetRectSize(rectSize);
}

void Player::Render(struct SDL_Renderer& renderer)
{
    SDL_Renderer* localRenderer = &renderer;
    if (!localRenderer)
    {
        return;
    }

    SDL_SetRenderDrawColor(localRenderer, 255, 0, 0, 1);

    SDL_FRect localPlayer{};
    localPlayer = Utilities::ConvertRect(playerRect);

    SDL_RenderRect(localRenderer, &localPlayer);
}

void Player::Update(float delta)
{
    if (bIsDashing)
    {
        InputXY = lastDash;
    }

    KeyStateUpdate();
    dashSpeed = UpdateDashSpeed(delta);
    
    position += InputXY * (dashSpeed * speed * delta);
    playerRect.SetRectLocation(position);
}

void Player::KeyStateUpdate()
{
    const bool* currentKeyStates = SDL_GetKeyboardState(nullptr);

    InputXY = Vector2();

    if (currentKeyStates[SDL_SCANCODE_UP])      InputXY.Y -= 1.0f;
    if (currentKeyStates[SDL_SCANCODE_DOWN])    InputXY.Y += 1.0f;
    if (currentKeyStates[SDL_SCANCODE_LEFT])    InputXY.X -= 1.0f;
    if (currentKeyStates[SDL_SCANCODE_RIGHT])   InputXY.X += 1.0f;

    //Trigger dash when pressed. Reset dash when the key is released
    if (currentKeyStates[SDL_SCANCODE_SPACE])
    {
        StartDash();
    //TODO implement spawning rectangles
        if (!(InputXY.X == 0.0f && InputXY.Y == 0.0f))
        {
            EntityManager::Create<Bullet>(playerRect.GetRectLocation(),InputXY);
        }
    }
    else
    {
        bDashReady = true;
    }

}

void Player::StartDash()
{
    if (bDashReady)
    {
        if (!bIsDashing)
        {
            lastDash = InputXY;

            dashDistance = 100.0f;
            bDashReady = false;
            bIsDashing = true;
        }
    }
}

float Player::UpdateDashSpeed(float delta, float timeToComplete)
{
    float dSpeed;
    if (bIsDashing)
    {
        dashTimeRemaining -= delta;
        const float deltaDashDistance = dashDistance * delta;

        dSpeed = deltaDashDistance / timeToComplete;

        if (dashTimeRemaining <= 0.0f)
        {
            bIsDashing = false;
        }
        return dSpeed;
    }
    else
    {
        dashTimeRemaining = timeToComplete;
        return dSpeed = 1.0f;
    }
}