#include "Object.h"

#include "vector"
#include "EntityManager.h"
#include "Rect.h"

Object::Object()
{
}

Object::Object(Vector2 pos, Vector2 dir)
{
	position = pos;
}

void Object::CollisionUpdate(float delta, Rect collisionRect, Vector2 newPosition)
{
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
        //TODO make the player slide off collision surfaces
        position -= newPosition;
        collisionRect.SetRectLocation(position);
    }
}

bool Object::checkCollision(const Object* objectA, const Object* objectB)
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