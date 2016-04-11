#ifndef DEVICEINFO
#define DEVICEINFO

#ifdef __APPLE__
#define GLM_FORCE_PURE
#include <unistd.h>
#include <sys/resource.h>
#include <glm/glm.hpp>
#include <OpenGLES/ES2/gl.h>
#else
#define GLM_FORCE_PURE
#include <GLES2/gl2.h>
#include <glm/glm.hpp>
#include <array>
#include <string>
#include <memory>
#include <pthread.h>
#endif

namespace device
{
	enum class AndroidEvent
	{
		None,
		Touch,
		Move,
		DoubleTouch,
	};
	namespace info
	{

		void SetWindowSize(unsigned int width,unsigned int height);
		/**
		* @brief デバイスのウィンドウサイズを取得
		* @return x:ウィンドウの幅,y:ウィンドウの高さ
		*/
		const glm::vec2& GetWindowSize();
	}
	namespace event
	{
		void Update();
		void SetEvent(const AndroidEvent& event);
		bool IsEvent(const AndroidEvent& event);
		bool IsJustEvent(const AndroidEvent& event);
		void SetTouchPosition(const glm::vec2& pos);
		void SetTouchPosition(const float& x,const float& y);
		const glm::vec2& GetTouchPosition();
	}
}
#endif