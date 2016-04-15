#include "player.h"
#include "../../PReminder.Shared/src/object/Sprite.h"
#include "../../PReminder.Shared/src/utility/DeviceInfo.h"


Player::Player()
{
	sprite = std::make_shared<gl::object::Sprite>();
}

void Player::Init()
{
	const auto windowSize = device::info::GetWindowSize();
	sprite->Init(glm::vec3(windowSize.x / 2.f - 100.f, windowSize.y / 2.f - 100.f, 0.f), glm::vec2(200.f, 200.f), glm::vec4(0.f, 0.f, 1.f, 1.f), "texture/unit.png");

	degree = 0;
}

void Player::Update()
{
	degree += 1.f;
	sprite->SetRotateFromCenter(degree);
}

void Player::Draw()
{
	sprite->Draw();
}