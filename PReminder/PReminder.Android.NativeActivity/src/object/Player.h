#ifndef PLAYER
#define PLAYER

#include <memory>

namespace gl
{
	namespace object
	{
		class Sprite;
	}
}

class Player
{
	std::shared_ptr<gl::object::Sprite> sprite;
	float degree;
public:
	Player();
	void Init();
	void Update();
	void Draw();
};

#endif