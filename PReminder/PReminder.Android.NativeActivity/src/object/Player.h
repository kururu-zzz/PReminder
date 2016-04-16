#ifndef PLAYER
#define PLAYER

#include <vector>
#include <memory>

namespace gl
{
	namespace object
	{
		class Sprite;
	}
}

class Shield;
class NormalShot;

class Player
{
	std::shared_ptr<gl::object::Sprite> sprite;
	std::shared_ptr<Shield> shield;
	std::vector<std::shared_ptr<NormalShot>> shots;
	float degree;
public:
	Player();
	void Init();
	void Update();
	void Draw();
};

#endif