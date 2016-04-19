#ifndef CHARACTER
#define CHARACTER

#include <vector>
#include <memory>
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
	class Shot;
	class Character
	{
	protected:
		struct Parameter
		{
			int hp = 0;
			int radius = 0;
			glm::vec3 pos = glm::vec3();
			float degree;
		} param;
	protected:
		std::shared_ptr<gl::object::Sprite> sprite;
		std::vector<std::shared_ptr<Shot>> shots;
	public:
		const Parameter& GetParam() const { return param; }
	public:
		virtual void CalcDamage(int damage);
		virtual bool IsDeath();
	public:
		Character();
		virtual void Init() = 0;
		virtual void Update(std::vector<std::shared_ptr<Character>>* targets) = 0;
		virtual void Draw() = 0;
	};
}
#endif