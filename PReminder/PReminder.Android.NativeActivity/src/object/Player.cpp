#include "Player.h"
#include "Shield.h"
#include "NormalShot.h"
#include "../../PReminder.Shared/src/object/Sprite.h"
#include "../../PReminder.Shared/src/utility/DeviceInfo.h"


Player::Player()
{
	sprite = std::make_shared<gl::object::Sprite>();
	shield = std::make_shared<Shield>();
}

void Player::Init()
{
	const auto windowSize = device::info::GetWindowSize();
	sprite->Init(glm::vec3(windowSize.x / 2.f, windowSize.y / 2.f, 0.f), glm::vec2(200.f, 200.f), glm::vec4(0.f, 0.f, 1.f, 1.f), "texture/unit.png");
	shield->Init();

	degree = 0;
}

void Player::Update()
{
	//degree += 1.f;
	sprite->SetRotateFromCenter(degree);
	shield->Update();
	if (device::event::IsJustEvent(device::AndroidEvent::Touch))
	{
		shots.emplace_back(std::make_shared<NormalShot>(degree));
	}
	for (auto& shot : shots)
	{
		shot->Update();
	}
}

void Player::Draw()
{
	shield->Draw();
	for (auto& shot : shots)
	{
		shot->Draw();
	}
	sprite->Draw();
}