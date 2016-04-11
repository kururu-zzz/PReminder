#include "MainScene.h"
#include "Title.h"
#include "../object/Sprite.h"
#include "../utility/DeviceInfo.h"
#include <future>

static std::mutex mutex;

MainScene::MainScene() : Sequence(typeid(MainScene).name())
{
	imageMap.emplace("image0", std::make_shared<gl::object::Sprite>());
	imageMap.emplace("image1", std::make_shared<gl::object::Sprite>());
	imageMap.emplace("image2", std::make_shared<gl::object::Sprite>());
}

void MainScene::Init(const std::string& beforeSequenceName){
	priority = 1;

	sequenceState = State::active;

	auto windowSize = device::info::GetWindowSize();
	imageMap.at("image0")->Init(glm::vec3(0.f, 0.f, 0.f), glm::vec2(windowSize.x,windowSize.y / 3.f), glm::vec4(0.f, 0.f, 1.f, 1.f), "texture/yamada1.png");
	imageMap.at("image1")->Init(glm::vec3(0.f, windowSize.y / 3.f, 0.f), glm::vec2(windowSize.x, windowSize.y / 3.f), glm::vec4(0.f, 0.f, 1.f, 1.f), "texture/yamada2.png");
	imageMap.at("image2")->Init(glm::vec3(0.f, windowSize.y * 2 / 3.f, 0.f), glm::vec2(windowSize.x, windowSize.y / 3.f), glm::vec4(0.f, 0.f, 1.f, 1.f), "texture/yamada3.png");

	this->beforeSequenceName = beforeSequenceName;
}

bool MainScene::Update(std::unordered_map<std::string, std::shared_ptr<Sequence>>* sequenceContainer)
{
	sequenceState = State::active;
	time++;
	if (device::event::IsEvent(device::AndroidEvent::DoubleTouch))
	{
		EmplaceSequence<Title>(sequenceContainer);
		sequenceContainer->at(typeid(Title).name())->Init(this->GetSequenceName());
		sequenceState = Sequence::State::wait;
		time = 0;
	}
	return true;
}

void MainScene::Draw()
{
	for (auto& image : imageMap)
	{
		image.second->Draw();
	}
}

