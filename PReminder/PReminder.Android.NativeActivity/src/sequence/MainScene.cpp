#include "MainScene.h"
#include "Title.h"
#include "../../../PReminder.Shared/src/object/Sprite.h"
#include "../../../PReminder.Shared/src/object/Font.h"
#include "../../../PReminder.Shared/src/utility/DeviceInfo.h"

#include "../object/Player.h"
#include "../object/Enemy.h"

#include <future>
#include <algorithm>

static std::mutex mutex;

MainScene::MainScene() : Sequence(typeid(MainScene).name())
{
	imageMap.emplace("back", std::make_shared<gl::object::Sprite>());
	players.reserve(1);
	players.emplace_back(std::make_shared<GameObject::Player>());

	enemys.reserve(3);
	enemys.emplace_back(std::make_shared<GameObject::Enemy>(glm::vec3(50.f, 50.f, 0.5f)));
	enemys.emplace_back(std::make_shared<GameObject::Enemy>(glm::vec3(30.f, 800.f, 0.5f)));
	enemys.emplace_back(std::make_shared<GameObject::Enemy>(glm::vec3(400.f, 900.f, 0.5f)));
}

void MainScene::Init(const std::string& beforeSequenceName){
	priority = 1;

	sequenceState = State::active;

	players[0]->Init();
	for (auto& enemy : enemys)
	{
		enemy->Init();
	}

	time = 0;

	auto windowSize = device::info::GetWindowSize();
	imageMap.at("back")->Init(glm::vec3(0.f, 0.f, 1.f), glm::vec2(0.f, 0.f), windowSize, glm::vec4(0.f, 0.f, 1.f, 1.f), "texture/sky.png");

	this->beforeSequenceName = beforeSequenceName;

	auto font = std::make_shared<gl::object::Font>();
}

bool MainScene::Update(std::unordered_map<std::string, std::shared_ptr<Sequence>>* sequenceContainer)
{
	sequenceState = State::active;
	players[0]->Update(&enemys);

	for (auto& enemy : enemys)
	{
		enemy->Update(&players);
	}
	enemys.erase(std::remove_if(enemys.begin(), enemys.end(), [](std::shared_ptr<GameObject::Character> enemy) {return enemy->IsDeath(); }), enemys.end());

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
	for (auto& enemy : enemys)
	{
		enemy->Draw();
	}
	players[0]->Draw();
}

