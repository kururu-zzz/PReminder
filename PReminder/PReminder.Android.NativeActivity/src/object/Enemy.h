#ifndef ENEMY
#define ENEMY

#include "Character.h"

namespace GameObject
{
	class Enemy : public Character
	{
	public:
		Enemy(const glm::vec3& pos);
		void Init();
		void Update(std::vector<std::shared_ptr<Character>>* targets);
		void Draw();
	};
}
#endif