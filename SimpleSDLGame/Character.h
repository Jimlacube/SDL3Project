#pragma once

#include <SDL3/SDL_rect.h>

#include "Object.h"
#include "Rect.h"

class Character : public Object
{
public:

	Character();

	void OnCharacterHit(Object* Instigator);
	void OnDamage(float damageAmount);
	void OnDeath();

	Rect CharacterRect = Rect();

	float characterHealth = 100.0f;
};

