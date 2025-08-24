#include "Player.h"

#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_keyboard.h>

#include "Vectors.h"
#include "EntityManager.h"
#include "Bullet.h"

void Player::Init()
{
    playerRect.SetRectSize(rectSize);
    position = Vector2(200.0f);
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
        Bullet* bullet = (Bullet*)EntityManager::SpawnEntity();
        bullet->bulletRect.SetRectLocation(playerRect.GetRectLocation());
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