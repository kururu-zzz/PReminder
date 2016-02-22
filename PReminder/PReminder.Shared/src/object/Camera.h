#ifndef __CAMERA__
#define __CAMERA__

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
#include <unordered_map>
#endif
namespace gl
{
	namespace ConstantBuffer
	{
		/**
		* @brief �J�����̒萔�o�b�t�@
		*/
		struct CameraBuffer
		{
			glm::mat4x4	matView = glm::mat4x4(1.f);
			glm::mat4x4	matProjection = glm::mat4x4(1.f);
			glm::mat4x4  matViewPort = glm::mat4x4(1.f);
			glm::mat4x4	matLVP = glm::mat4x4(1.f);
			glm::vec4 eyePos = glm::vec4(1.f);
		};
	}
	namespace object
	{
		/**
		* @brief DirectX���W�n�ɑΉ������J�����N���X
		*/
		class Camera {
		private:
			ConstantBuffer::CameraBuffer cameraBuffer;
			glm::vec3 pos;
			glm::vec3 focus;
			glm::vec3 upDirection;

			const float projectionDegree = 45.f;
		public:
			/**
			* @brief �J�����̏�����
			* @param pos:�J�����̈ʒu
			* @param focus:�J�����̏œ_�ʒu
			* @param screenSize:�A�v���̉�ʃT�C�Y
			*/
			void Init(const glm::vec3& pos, const glm::vec3& focus, const glm::vec2& screenSize);

			/**
			* @brief �J�����̈ʒu��ݒ�
			* @param pos:�J�����̈ʒu
			*/
			void SetPos(const glm::vec3& pos);

			/**
			* @brief �J�����̏œ_�ʒu��ݒ�
			* @param focus:�J�����̏œ_�ʒu
			*/
			void SetFocus(const glm::vec3& focus);

			/**
			* @brief �J�����̕��s���e�s����v�Z����(��ɕ��U�e�Ɏg��)
			* @param pos:�J�����̈ʒu
			* @param focus:�J�����̏œ_
			*/
			void SetOrtho(
				const glm::vec3& pos,
				const glm::vec3& focus = glm::vec3(0.f, 0.f, 0.f));

			/**
			* @brief �J����������_�ɒ��ڂ�����
			* @param focus:�����_
			*/
			void RockOn(const glm::vec3& focus);

			/**
			* @brief �J�����̒萔�o�b�t�@���擾
			*/
			const ConstantBuffer::CameraBuffer& GetBuffer();

			/**
			* @brief �J�����̈ʒu���擾
			*/
			const glm::vec3& GetPos() const {
				return pos;
			}

			/**
			* @brief �J�����̏œ_�ʒu���擾
			*/
			const glm::vec3& GetFocus() const {
				return focus;
			}
		};
	}
}

#endif