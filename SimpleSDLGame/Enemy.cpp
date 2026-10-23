#include "Enemy.h"

#include <SDL3/SDL_render.h>

#include "Character.h"
#include "Utilities.h"

Enemy::Enemy()
{
    CharacterRect.SetRectSize(50.0f);
    EntityTag = "enemy";
    position = Vector2(100.0f);
    collider = Utilities::ConvertRect(CharacterRect);
}

void Enemy::Render(struct SDL_Renderer& renderer)
{
    SDL_Renderer* localRenderer = &renderer;
    if (!localRenderer)
    {
        return;
    }

    SDL_SetRenderDrawColor(localRenderer, 0, 0, 255, 1);
    
    SDL_FRect localEnemy = Utilities::ConvertRect(CharacterRect);
    SDL_RenderFillRect(localRenderer, &localEnemy);
    SDL_RenderRect(localRenderer, &localEnemy);
}

void Enemy::Update(float delta)
{
    //TODO fix this bug
    if (delta > 10)
        return;

    enemyLifeSpan += delta;

    Vector2 positionUpdate = Vector2(sin(enemyLifeSpan), 0) * (100 * delta);
    position += positionUpdate;
    CharacterRect.SetRectLocation(position);
    
    Object* hitObject = CollisionUpdate(CharacterRect, positionUpdate, "");
    

   

    //Collision update
     //X
    //Vector2 newInput = Vector2(1.0f, 0) * 50 * delta;
    //position += newInput;
    //printf("pos: X %f, Y: %f \n", position.X, position.Y);
    //CharacterRect.SetRectLocation(position);
    //Object* hitObject = CollisionUpdate(CharacterRect, newInput, "enemy");
    //Y
    //newInput = Vector2(0, inputXY.Y) * (dashSpeed * speed * delta);
    //position += newInput;
    //CharacterRect.SetRectLocation(position);
    //CollisionUpdate(CharacterRect, newInput, "bullet");

    if (hitObject)
    {
        if (hitObject != this)

        {
            //printf("hit obj: \n");
            Character* hitCharacter = dynamic_cast<Character*>(hitObject);
            if (hitCharacter)
            {
                //hitCharacter->CharacterRect(hitCharacter->position + positionUpdate);
                hitCharacter->CharacterRect.SetRectLocation(hitCharacter->position + positionUpdate);
                printf("hit char: \n");
            }
        }
    }

    
}

void Enemy::OnHit(Object* hitObject)
{
    printf("hit obj: \n");
}
