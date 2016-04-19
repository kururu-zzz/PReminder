#include "Character.h"
#include "NormalShot.h"
#include "../../../PReminder.Shared/src/object/Sprite.h"
#include "../../../PReminder.Shared/src/utility/DeviceInfo.h"

namespace GameObject
{
	inline bool IsHit(const glm::vec3& shotPos, const glm::vec3& targetPos, const float& shotRadius, const float& targetRadius)
	{
		return glm::length(shotPos - targetPos) <= shotRadius + targetRadius;
	}

	NormalShot::NormalShot(const float& playerAngle)
	{
		param.degree = playerAngle;
	}

	void NormalShot::Init()
	{
		const auto windowSize = device::info::GetWindowSize();
		const auto spriteSize = glm::vec2(50.f, 50.f);
		param.damage = 1;
		param.radius = 20.f;
		param.pos = glm::vec3(
			windowSize.x / 2.f + cosf(glm::radians(param.degree)),
			windowSize.y / 2.f - sinf(glm::radians(param.degree)), 0.f);
		sprite->Init(param.pos, glm::vec2(0.5f, 0.5f), spriteSize, glm::vec4(0.f, 0.f, 1.f, 1.f), "texture/normalShot.png");
	}

	void NormalShot::Update(std::vector<std::shared_ptr<Character>>* targets)
	{
		const auto windowSize = device::info::GetWindowSize();
		const auto shotSpeed = 5.f;
		param.pos += glm::vec3(
			cosf(glm::radians(param.degree)) * shotSpeed,
			-sinf(glm::radians(param.degree)) * shotSpeed,
			0.f);

		for (auto& target : *targets)
		{
			auto targetParam = target->GetParam();
			if (IsHit(param.pos, targetParam.pos, param.radius, targetParam.radius))
			{
				target->CalcDamage(param.damage);
				deleteFlag = true;
				break;
			}
		}

		if (param.pos.x < 0.f || param.pos.x > windowSize.x ||
			param.pos.y < 0.f || param.pos.y > windowSize.y)
		{
			deleteFlag = true;
		}
		sprite->SetPos(param.pos);
		sprite->SetRotate(param.degree);
	}

	void NormalShot::Draw()
	{
		sprite->Draw();
	}
}