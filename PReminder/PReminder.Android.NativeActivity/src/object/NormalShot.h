#ifndef NORMALSHOT
#define NORMALSHOT

#include <memory>

namespace gl
{
	namespace object
	{
		class Sprite;
	}
}

class NormalShot
{
	std::shared_ptr<gl::object::Sprite> sprite;
	float degree = 0;
public:
	NormalShot(const float& playerAngle);
	void Init();
	void Update();
	void Draw();
};

#endif