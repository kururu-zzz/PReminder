#include "Shield.h"
#include "../../../PReminder.Shared/src/object/Sprite.h"
#include "../../../PReminder.Shared/src/utility/DeviceInfo.h"

namespace GameObject
{
	Shield::Shield()
	{
		sprite = std::make_shared<gl::object::Sprite>();
	}

	void Shield::Init()
	{
		const auto windowSize = device::info::GetWindowSize();
		const auto spriteSize = glm::vec2(200.f, 300.f);
		degree = 270.f;
		sprite->Init(glm::vec3(
			windowSize.x / 2.f + radius,
			windowSize.y / 2.f, 0.f),
			glm::vec2(0.5f, 0.5f), spriteSize, glm::vec4(0.f, 0.f, 1.f, 1.f), "texture/shield.png");
		sprite->SetRotate(degree);
	}

	void Shield::Update()
	{
		degree += 1.f;
		const auto windowSize = device::info::GetWindowSize();
		sprite->SetPos(
			glm::vec3(
				windowSize.x / 2.f + cosf(glm::radians(degree)) * radius,
				windowSize.y / 2.f - sinf(glm::radians(degree)) * radius, 0.f));
		sprite->SetRotate(degree);
	}

	void Shield::Draw()
	{
		sprite->Draw();
	}
}