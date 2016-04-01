#ifndef TITLE
#define TITLE

#include "Sequence.h"

class Title : public Sequence
{
private:
	int time = 0;//�V�[���J�ډ��o���Ԃ̊Ǘ��p�ϐ�
public:
	Title();
	void Init(const std::string& beforeSequenceName);
	bool Update(std::unordered_map<std::string, std::shared_ptr<Sequence>>* sequenceContainer);
	void Draw();

};

#endif