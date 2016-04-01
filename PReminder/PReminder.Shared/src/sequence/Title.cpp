#include "Title.h"
#include "MainScene.h"
#include "../object/Sprite.h"
#include "../utility/DeviceInfo.h"
#include <future>

static std::mutex mutex;

Title::Title() : Sequence(typeid(Title).name())
{
	imageMap.emplace("image0", std::make_shared<gl::object::Sprite>());
	imageMap.emplace("image1", std::make_shared<gl::object::Sprite>());
	imageMap.emplace("image2", std::make_shared<gl::object::Sprite>());
}

void Title::Init(const std::string& beforeSequenceName){
	priority = 1;

	sequenceState = Sequence::State::active;

	auto windowSize = device::info::GetWindowSize();
	imageMap.at("image0")->Init(glm::vec3(0.f, 0.f, 0.f), glm::vec2(windowSize.x,windowSize.y / 3.f), glm::vec4(0.f, 0.f, 1.f, 1.f), "texture/nazuna1.png");
	imageMap.at("image1")->Init(glm::vec3(0.f, windowSize.y / 3.f, 0.f), glm::vec2(windowSize.x, windowSize.y / 3.f), glm::vec4(0.f, 0.f, 1.f, 1.f), "texture/nazuna2.png");
	imageMap.at("image2")->Init(glm::vec3(0.f, windowSize.y * 2 / 3.f, 0.f), glm::vec2(windowSize.x, windowSize.y / 3.f), glm::vec4(0.f, 0.f, 1.f, 1.f), "texture/nazuna3.png");

	this->beforeSequenceName = beforeSequenceName;
}

bool Title::Update(std::unordered_map<std::string, std::shared_ptr<Sequence>>* sequenceContainer)
{
	sequenceState = Sequence::State::active;
	time++;
	if (time > 180)
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

