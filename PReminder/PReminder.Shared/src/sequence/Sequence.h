#ifndef SEQUENCE
#define SEQUENCE

#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include <typeinfo>

namespace gl
{
	namespace object
	{
		class Sprite;
	}
}

class Sequence
{
protected:
	enum class State
	{
		wait = 0x01,
		drawable = 0x02,
		updatable = 0x04,
		active = 0x06,
	};
private:
	std::string sequenceName;
protected:
	std::unordered_map<std::string, std::shared_ptr<gl::object::Sprite>> imageMap;
	State sequenceState = State::wait;
	std::string  nextSequenceName;
	std::string  beforeSequenceName;
	unsigned int priority = 0;
protected:
	template<class T>
	static void EmplaceSequence(std::unordered_map<std::string, std::shared_ptr<Sequence>>* sequenceContainer)
	{
		std::string sequenceName = typeid(T).name();
		for (auto& info : *sequenceContainer)
		{
			if (info.first == sequenceName)
				return;
		}
		auto sequence = std::make_shared<T>();
		sequenceContainer->emplace(sequence->GetSequenceName(),sequence);
	}
public:
	Sequence(const std::string& sequenceName) : sequenceName(sequenceName) {};

	virtual ~Sequence(){}
	virtual void Init(const std::string& beforeSequenceName) = 0;
	virtual bool Update(std::unordered_map<std::string, std::shared_ptr<Sequence>>* sequenceContainer) = 0;
	virtual void Draw() = 0;
public:
	const std::string GetSequenceName() const
	{ 
		return sequenceName;
	}
	const unsigned int GetPriority() const{ return priority; }
	bool isUpdatable(){ return ((static_cast<int>(sequenceState)& static_cast<int>(State::updatable)) != 0); }
	bool isDrawable(){ return ((static_cast<int>(sequenceState)& static_cast<int>(State::drawable)) != 0); }
};

class SequenceManager
{
private:
	std::unordered_map<std::string, std::shared_ptr<Sequence>> sequenceContainer;
public:
	SequenceManager();
	bool Update();
	void Draw();
};

#endif