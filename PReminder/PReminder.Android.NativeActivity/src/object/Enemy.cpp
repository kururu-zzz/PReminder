#include "Enemy.h"
#include "Shield.h"
#include "NormalShot.h"
#include "../../../PReminder.Shared/src/object/Sprite.h"
#include "../../../PReminder.Shared/src/utility/DeviceInfo.h"

#include <algorithm>

namespace GameObject
{
	Enemy::Enemy(const glm::vec3& pos)
	{
		param.pos = pos;
	}

	void Enemy::Init()
	{
		const auto spriteSize = glm::vec2(100.f, 100.f);

		param.hp = 5;
		param.degree = 0.f;
		param.radius = 30.f;

		sprite->Init(param.pos, glm::vec2(0.5f, 0.5f), spriteSize, glm::vec4(0.f, 0.f, 1.f, 1.f), "texture/enemy.png");
		sprite->SetRotate(param.degree);

		shots.clear();
	}

	void Enemy::Update(std::vector<std::shared_ptr<Character>>* targets)
	{
		/*
		if (device::event::IsJustEvent(device::AndroidEvent::Touch))
		{
			shots.emplace_back(std::make_shared<NormalShot>(degree));
		}
		for (auto& shot : shots)
		{
			shot->Update();
		}
		shots.erase(std::remove_if(shots.begin(), shots.end(), [](std::shared_ptr<NormalShot> shot) {return shot->IsDelete(); }), shots.end());
		*/
	}

	void Enemy::Draw()
	{
		for (auto& shot : shots)
		{
			shot->Draw();
		}
		sprite->Draw();
	}
}