#ifndef MAINSCENE
#define MAINSCENE

#include "Sequence.h"

namespace GameObject
{
	class Character;
}
class MainScene : public Sequence
{
private:
	int time = 0;
	std::vector<std::shared_ptr<GameObject::Character>> players;
	std::vector<std::shared_ptr<GameObject::Character>> enemys;
public:
	MainScene();
	void Init(const std::string& beforeSequenceName);
	bool Update(std::unordered_map<std::string, std::shared_ptr<Sequence>>* sequenceContainer);
	void Draw();

};

#endif