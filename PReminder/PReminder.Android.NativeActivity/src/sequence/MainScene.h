#ifndef MAINSCENE
#define MAINSCENE

#include "Sequence.h"

namespace GameObject
{
	class Character;
}

namespace gl
{
	namespace object
	{
		class Font;
	}
}

class MainScene : public Sequence
{
private:
	int time = 0;
	std::vector<std::shared_ptr<GameObject::Character>> players;
	std::vector<std::shared_ptr<GameObject::Character>> enemys;

	std::shared_ptr<gl::object::Font> font;
public:
	MainScene();
	void Init(const std::string& beforeSequenceName);
	bool Update(std::unordered_map<std::string, std::shared_ptr<Sequence>>* sequenceContainer);
	void Draw();

};

#endif