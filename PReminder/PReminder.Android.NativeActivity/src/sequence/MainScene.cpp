#include "MainScene.h"
#include "Title.h"
#include "../../PReminder.Shared/src/object/Sprite.h"
#include "../../PReminder.Shared/src/utility/DeviceInfo.h"
#include <future>

#include "../object/Player.h"

static std::mutex mutex;

MainScene::MainScene() : Sequence(typeid(MainScene).name())
{
	imageMap.emplace("back", std::make_shared<gl::object::Sprite>());
	player = std::make_shared<Player>();
}

void MainScene::Init(const std::string& beforeSequenceName){
	priority = 1;

	sequenceState = State::active;

	player->Init();

	time = 0;

	auto windowSize = device::info::GetWindowSize();
	imageMap.at("back")->Init(glm::vec3(0.f, 0.f, 1.f), windowSize, glm::vec4(0.f, 0.f, 1.f, 1.f), "texture/sky.png");

	this->beforeSequenceName = beforeSequenceName;
}

bool MainScene::Update(std::unordered_map<std::string, std::shared_ptr<Sequence>>* sequenceContainer)
{
	sequenceState = State::active;
	player->Update();

	if (device::event::IsEvent(device::AndroidEvent::DoubleTouch))
	{
		EmplaceSequence<Title>(sequenceContainer);
		sequenceContainer->at(typeid(Title).name())->Init(this->GetSequenceName());
		sequenceState = Sequence::State::wait;
	}
	return true;
}

void MainScene::Draw()
{
	for (auto& image : imageMap)
	{
		image.second->Draw();
	}
	player->Draw();
}

