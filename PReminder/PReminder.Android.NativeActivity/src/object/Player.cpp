#include "Player.h"
#include "Shield.h"
#include "NormalShot.h"
#include "../../../PReminder.Shared/src/object/Sprite.h"
#include "../../../PReminder.Shared/src/utility/DeviceInfo.h"

#include <algorithm>

namespace GameObject
{
	float RotatePlayer(const glm::vec2& direction)
	{
		auto directionX = direction.x;
		auto charaDegree = glm::degrees(acosf(directionX));
		return charaDegree * ((direction.y >= 0.f) ? -1 : 1);
	}

	Player::Player()
	{
		shield = std::make_shared<Shield>();
		targetMarker = std::make_shared<gl::object::Sprite>();
	}

	void Player::Init()
	{
		const auto windowSize = device::info::GetWindowSize();
		const auto spriteSize = glm::vec2(200.f, 200.f);
		
		param.pos = glm::vec3(windowSize.x / 2.f, windowSize.y / 2.f, 0.f);
		param.hp = 50;
		param.degree = 90.f;

		sprite->Init(param.pos, glm::vec2(0.5f, 0.5f), spriteSize, glm::vec4(0.f, 0.f, 1.f, 1.f), "texture/unit.png");
		sprite->SetRotate(param.degree);

		targetMarker->Init(glm::vec3(-100.f,0.f,0.f), glm::vec2(0.5f, 0.5f), spriteSize / 2.f, glm::vec4(0.f, 0.f, 1.f, 1.f), "texture/target.png");

		shield->Init();
		shots.clear();
	}

	void Player::Update(std::vector<std::shared_ptr<Character>>* targets)
	{
		shield->Update();
		if (device::event::IsJustEvent(device::AndroidEvent::Touch))
		{
			auto touchPos = device::event::GetTouchPosition();
			targetMarker->SetPos(glm::vec3(touchPos.x, touchPos.y, 0.f));
			param.degree = RotatePlayer(glm::normalize(touchPos - glm::vec2(param.pos.x,param.pos.y)));
			auto shot = std::make_shared<NormalShot>(param.degree);
			shot->Init();
			shots.emplace_back(shot);
		}
		for (auto& shot : shots)
		{
			shot->Update(targets);
		}
		shots.erase(std::remove_if(shots.begin(), shots.end(), [](std::shared_ptr<Shot> shot) {return shot->IsDelete(); }), shots.end());

		sprite->SetRotate(param.degree);
	}

	void Player::Draw()
	{
		shield->Draw();
		targetMarker->Draw();
		for (auto& shot : shots)
		{
			shot->Draw();
		}
		sprite->Draw();
	}
}