#pragma once

#include "Character.h"

class Enemy : public Character
{
public:
    Enemy();
    
    //Public functions
    void Render(struct SDL_Renderer& renderer) override;
    void Update(float delta) override;
    virtual void OnHit(Object* hitObject) override;

private:
    float enemyLifeSpan = 0.0f;
    float rectSize = 100.0f;
};
