#ifndef PLAYER
#define PLAYER

#include "Character.h"

namespace GameObject
{
	class Shield;
	class Player : public Character
	{
		std::shared_ptr<gl::object::Sprite> targetMarker;
		std::shared_ptr<Shield> shield;
	public:
		Player();
		void Init();
		void Update(std::vector<std::shared_ptr<Character>>* targets);
		void Draw();
	};
}
#endif