#include "Character.h"

Character::Character()
{
}

void Character::OnCharacterHit(Object* Instigator)
{
	if (!Instigator)
	{
		return;
	}

	//Apply damage on hit
	OnDamage(10.0f);
}

void Character::OnDamage(float damageAmount)
{
	float OldHealth = characterHealth;

	characterHealth = OldHealth - damageAmount;

	printf("Old health: %f , New health: %f \n", OldHealth, characterHealth);

	if (characterHealth <= 0.0f)
	{
		OnDeath();
	}
}

void Character::OnDeath()
{
	Destroy();
}
