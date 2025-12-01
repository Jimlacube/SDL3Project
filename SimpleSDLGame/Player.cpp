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
    
    //Debug draw desired position
    Vector2 centrePos = position + Vector2(rectSize * 0.5f);
    SDL_RenderLine(&renderer, centrePos.X, centrePos.Y, desiredPosition.X, desiredPosition.Y);
}

void Player::Update(float delta)
{
    if (bIsDashing)
    {
        inputXY = lastDash;
    }

    KeyStateUpdate();
    dashSpeed = UpdateDashSpeed(delta);
    
    position += inputXY * (dashSpeed * speed * delta);
    playerRect.SetRectLocation(position);

    Object* hitObject = nullptr;
    std::vector<Entity*> localEntities = EntityManager::GetEntities();
    for (Entity* entity : localEntities)
    {
        if (entity == this)
            continue;
        
        Object* otherObject = static_cast<Object*>(entity);
        if (!otherObject)
        {
            continue;
        }
        
        if (checkCollision(this, otherObject))
        {
            hitObject = otherObject;
            break;
        }        
    }
    if (hitObject)
    {        
        position -= inputXY * (dashSpeed * speed * delta);
        playerRect.SetRectLocation(position);
    }

    UpdateFiringCooldown(delta);
}

bool Player::checkCollision(const Object* objectA, const Object* objectB)
{
    SDL_FRect colliderA = objectA->collider;
    Vector2 positionA = objectA->position;
    //Calculate the sides of object A
    float leftA = colliderA.x + positionA.X;
    float rightA = colliderA.x + colliderA.w + positionA.X;
    float topA = colliderA.y + positionA.Y;
    float bottomA = colliderA.y + colliderA.h + positionA.Y;

    SDL_FRect colliderB = objectB->collider;
    Vector2 positionB = objectB->position;
    //Calculate the sides of object B
    float leftB = colliderB.x;
    float rightB = colliderB.x + colliderB.w;
    float topB = colliderB.y;
    float bottomB = colliderB.y + colliderB.h;

    //Check if any of the sides of A are outside of B
    if (bottomA <= topB)
        return false;        
    if (topA >= bottomB)
        return false;
    if (rightA <= leftB)
        return false;
    if (leftA >= rightB)
        return false;

    //If none of the sides from A are outside B
    return true;
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
