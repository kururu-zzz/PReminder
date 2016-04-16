#ifndef SHIELD
#define SHIELD

#include <memory>

namespace gl
{
	namespace object
	{
		class Sprite;
	}
}

class Shield
{
	std::shared_ptr<gl::object::Sprite> sprite;
	float degree;
	const float radius = 200.f;
public:
	Shield();
	void Init();
	void Update();
	void Draw();
};

#endif