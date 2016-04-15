#ifndef MAINSCENE
#define MAINSCENE

#include "Sequence.h"

class Player;

class MainScene : public Sequence
{
private:
	int time = 0;
	std::shared_ptr<Player> player;
public:
	MainScene();
	void Init(const std::string& beforeSequenceName);
	bool Update(std::unordered_map<std::string, std::shared_ptr<Sequence>>* sequenceContainer);
	void Draw();

};

#endif