#include "DeviceInfo.h"

namespace device
{
	namespace info
	{ 
		static glm::vec2 windowSize;
		void SetWindowSize(unsigned int width, unsigned int height)
		{
			windowSize.x = width;
			windowSize.y = height;
		}
		const glm::vec2& GetWindowSize()
		{
			return windowSize;
		}
	}
}
