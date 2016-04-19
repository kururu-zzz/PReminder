#include "Shot.h"
#include "../../../PReminder.Shared/src/object/Sprite.h"

namespace GameObject
{
	Shot::Shot()
	{
		sprite = std::make_shared<gl::object::Sprite>();
	}
}