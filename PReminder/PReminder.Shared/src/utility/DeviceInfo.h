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
	namespace info
	{
		void SetWindowSize(unsigned int width,unsigned int height);
		/**
		* @brief �f�o�C�X�̃E�B���h�E�T�C�Y���擾
		* @return x:�E�B���h�E�̕�,y:�E�B���h�E�̍���
		*/
		const glm::vec2& GetWindowSize();
	}
}
#endif