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
	namespace event
	{
		static AndroidEvent androidEvent;
		static AndroidEvent oldAndroidEvent;
		static glm::vec2 touchPos;
		void Update()
		{
			oldAndroidEvent = androidEvent;
			androidEvent = AndroidEvent::None;
		}

		void SetEvent(const AndroidEvent& event)
		{ 
			androidEvent = event;
		}

		bool IsEvent(const AndroidEvent& event)
		{
			return androidEvent == event;
		}
		
		bool IsJustEvent(const AndroidEvent& event)
		{
			return (static_cast<unsigned int>(androidEvent) & ~static_cast<unsigned int>(oldAndroidEvent) & static_cast<unsigned int>(event)) != 0;
		}

		void SetTouchPosition(const glm::vec2& pos)
		{
			touchPos = pos;
		}

		void SetTouchPosition(const float& x,const float& y)
		{
			touchPos = glm::vec2(x,y);
		}

		const glm::vec2& GetTouchPosition()
		{
			return touchPos;
		}
	}
}
