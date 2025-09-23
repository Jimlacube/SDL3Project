#pragma once
#include "Object.h"
#include "Rect.h"

class Enemy : public Object
{
public:
    Enemy();
    
    //Public functions
    void Render(struct SDL_Renderer& renderer) override;
    void Update(float delta) override;

    //Public variables
    Rect enemyRect = Rect();
};
