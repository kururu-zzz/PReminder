#include "NormalShot.h"
#include "../../PReminder.Shared/src/object/Sprite.h"
#include "../../PReminder.Shared/src/utility/DeviceInfo.h"


NormalShot::NormalShot(const float& playerAngle)
{
	sprite = std::make_shared<gl::object::Sprite>();
	degree = playerAngle;
	Init();
}

void NormalShot::Init()
{
	const auto windowSize = device::info::GetWindowSize();
	sprite->Init(glm::vec3(
		windowSize.x / 2.f + cosf(glm::radians(degree)),
		windowSize.y / 2.f - sinf(glm::radians(degree)),0.f), 
		glm::vec2(50.f, 50.f), glm::vec4(0.f, 0.f, 1.f, 1.f), "texture/normalShot.png");
}

void NormalShot::Update()
{
	sprite->MovePos(glm::vec3(
		cosf(glm::radians(degree)) * 5.f,
		-sinf(glm::radians(degree)) * 5.f,
		0.f));
	sprite->SetRotateFromCenter(degree);
}

void NormalShot::Draw()
{
	sprite->Draw();
}