#include "Player.h"
#include "../../../PReminder.Shared/src/object/Sprite.h"

namespace GameObject
{
	Character::Character()
	{
		sprite = std::make_shared<gl::object::Sprite>();
	}
	void Character::CalcDamage(int damage)
	{
		param.hp -= damage;
	}
	bool Character::IsDeath()
	{
		return param.hp == 0;
	}
}