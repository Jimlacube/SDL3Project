#include "Player.h"

#include <algorithm>
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
    position = Vector2(Utilities::GetScreenBounds().X * 0.5f, Utilities::GetScreenBounds().Y * 0.5f);
    EntityTag = "player";
    collider = Utilities::ConvertRect(playerRect);
}

Vector2 desiredPosition = Vector2(0.0f);

void Player::Render(struct SDL_Renderer& renderer)
{
    SDL_Renderer* localRenderer = &renderer;
    if (!localRenderer)
    {
        return;
    }

    SDL_SetRenderDrawColor(localRenderer, 255, 0, 0, 1);
    
    SDL_FRect localPlayer = Utilities::ConvertRect(playerRect);
    SDL_RenderFillRect(localRenderer, &localPlayer);
    SDL_RenderRect(localRenderer, &localPlayer);
}

void Player::Update(float delta)
{
    if (bIsDashing)
    {
        inputXY = lastDash;
    }

    KeyStateUpdate();
    dashSpeed = UpdateDashSpeed(delta);

    //Collision update
    //X
    Vector2 newInput = Vector2(inputXY.X, 0) * (dashSpeed * speed * delta);
    position += newInput;
    playerRect.SetRectLocation(position);
    CollisionUpdate(playerRect, newInput, "bullet");
    //Y
    newInput = Vector2(0, inputXY.Y) * (dashSpeed * speed * delta);
    position += newInput;
    playerRect.SetRectLocation(position);
    CollisionUpdate(playerRect, newInput, "bullet");

    //Firing
    UpdateFiringCooldown(delta);
}
void Player::KeyStateUpdate()
{
    const bool* currentKeyStates = SDL_GetKeyboardState(nullptr);

    inputXY = Vector2();

    if (currentKeyStates[SDL_SCANCODE_UP])      inputXY.Y -= 1.0f;
    if (currentKeyStates[SDL_SCANCODE_DOWN])    inputXY.Y += 1.0f;
    if (currentKeyStates[SDL_SCANCODE_LEFT])    inputXY.X -= 1.0f;
    if (currentKeyStates[SDL_SCANCODE_RIGHT])   inputXY.X += 1.0f;

    if (!(inputXY.X == 0.0f && inputXY.Y == 0.0f))
    {
        lastInputDir = inputXY;
    }
    //Trigger dash when pressed. Reset dash when the key is released
    if (currentKeyStates[SDL_SCANCODE_SPACE])
    {
        StartDash();
    }
    else
    {
        bIsDashReady = true;
    }
    //Fire bullet
    if (currentKeyStates[SDL_SCANCODE_Z])
    {
        if (!bIsFiring)
        {
            EntityManager::Create<Bullet>(playerRect.GetRectLocation(),lastInputDir);
            bIsFiring = true;
        }
    }
}

void Player::StartDash()
{
    if (bIsDashReady)
    {
        if (!bIsDashing)
        {
            lastDash = inputXY;

            dashDistance = 100.0f;
            bIsDashReady = false;
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
    
    dashTimeRemaining = timeToComplete;
    return dSpeed = 1.0f;
}

void Player::UpdateFiringCooldown(float delta)
{
    if (firingTimeRemaining <= 0.0f)
    {
        bIsFiring = false;
    }
    if (bIsFiring)
    {
        firingTimeRemaining -= delta;
    }
    else
    {
        firingTimeRemaining = firingCooldown;
    }
}
