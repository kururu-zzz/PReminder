#ifndef MAINSCENE
#define MAINSCENE

#include "Sequence.h"

class MainScene : public Sequence
{
private:
	int time = 0;//シーン遷移演出時間の管理用変数
public:
	MainScene();
	void Init(const std::string& beforeSequenceName);
	bool Update(std::unordered_map<std::string, std::shared_ptr<Sequence>>* sequenceContainer);
	void Draw();

};

#endif