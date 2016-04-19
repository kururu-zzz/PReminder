#ifndef NORMALSHOT
#define NORMALSHOT

#include "Shot.h"

namespace GameObject
{
	class NormalShot : public Shot
	{
	public:
		NormalShot(const float& playerAngle);
		void Init();
		void Update(std::vector<std::shared_ptr<Character>>* targets);
		void Draw();
	};
}

#endif