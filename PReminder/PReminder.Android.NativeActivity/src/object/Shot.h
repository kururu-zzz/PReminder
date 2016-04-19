#ifndef SHOT
#define SHOT

#include <memory>
#include <vector>
#include <glm/glm.hpp>

namespace gl
{
	namespace object
	{
		class Sprite;
	}
}

namespace GameObject
{
	class Character;
	class Shot
	{
	protected:
		struct Parameter
		{
			int damage = 0;
			float radius = 0;
			glm::vec3 pos = glm::vec3();
			float degree;
		} param;
	protected:
		std::shared_ptr<gl::object::Sprite> sprite;
		bool deleteFlag = false;
	public:
		bool IsDelete() { return deleteFlag; }
	public:
		Shot();
		virtual void Init() = 0;
		virtual void Update(std::vector<std::shared_ptr<Character>>* targets) = 0;
		virtual void Draw() = 0;
	};
}

#endif