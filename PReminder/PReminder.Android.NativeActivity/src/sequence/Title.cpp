#include "Title.h"
#include "MainScene.h"
#include "../../PReminder.Shared/src/object/Sprite.h"
#include "../../PReminder.Shared/src/utility/DeviceInfo.h"
#include <future>

static std::mutex mutex;

Title::Title() : Sequence(typeid(Title).name())
{
	imageMap.emplace("title", std::make_shared<gl::object::Sprite>());
}

void Title::Init(const std::string& beforeSequenceName){
	priority = 1;

	sequenceState = Sequence::State::active;

	auto windowSize = device::info::GetWindowSize();
	imageMap.at("title")->Init(glm::vec3(0.f, 0.f, 0.f), windowSize, glm::vec4(0.f, 0.f, 1.f, 1.f), "texture/title.png");

	this->beforeSequenceName = beforeSequenceName;
}

bool Title::Update(std::unordered_map<std::string, std::shared_ptr<Sequence>>* sequenceContainer)
{
	sequenceState = Sequence::State::active;
	time++;
	if (device::event::IsJustEvent(device::AndroidEvent::Touch) && 
		(device::event::GetTouchPosition().y < device::info::GetWindowSize().y / 2))
	{
		EmplaceSequence<MainScene>(sequenceContainer);
		sequenceContainer->at(typeid(MainScene).name())->Init(this->GetSequenceName());
		sequenceState = Sequence::State::wait;
		time = 0;
	}
	return true;
}

void Title::Draw()
{
	for (auto& image : imageMap)
	{
		image.second->Draw();
	}
}

