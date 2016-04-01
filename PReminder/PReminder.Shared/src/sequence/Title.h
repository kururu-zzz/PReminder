#ifndef TITLE
#define TITLE

#include "Sequence.h"

class Title : public Sequence
{
private:
	int time = 0;//シーン遷移演出時間の管理用変数
public:
	Title();
	void Init(const std::string& beforeSequenceName);
	bool Update(std::unordered_map<std::string, std::shared_ptr<Sequence>>* sequenceContainer);
	void Draw();

};

#endif