#ifndef SPRITE
#define SPRITE

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
#endif

namespace Vertex
{
	struct DefaultVertex
	{
		glm::vec3 pos;
		glm::vec4 color;
		glm::vec3 normal;
		glm::vec2 texel;
	};
}

namespace gl
{
	namespace object
	{
		/**
		* @brief 2D�`��p�X�v���C�g�N���X
		*/
		class Sprite
		{
		private:
			glm::vec3 pos;
			glm::vec2 size;
			glm::vec2 base;
			float degree;
			std::array<std::shared_ptr<Vertex::DefaultVertex>, 4> vertexList;
			std::string fileName;
		public:
			Sprite();

			/**
			* @brief �X�v���C�g�̏�����
			* @param pos:�����ʒu(�X�N���[�����W)
			* @param size:�����T�C�Y
			* @param uv:�ݒ肷��UV�l
			* @param fileName:�ǂݍ��ރe�N�X�`���̃p�X
			UV�̐ݒ�͈ȉ��̒ʂ�
			x�����㒸�_��u
			y�����㒸�_��v
			z���E�����_��u
			w���E�����_��v
			*/
			void Init(
				const glm::vec3& pos,
				const glm::vec2& size,
				const glm::vec4& uv,
				const std::string& fileName);

			/**
			* @brief �X�v���C�g�̍��W�ʒu��ݒ�
			* @param pos:�ݒ肷��ʒu(�X�N���[�����W)
			*/
			void SetPos(const glm::vec3& pos);

			/**
			* @brief �X�v���C�g�̍��W�ʒu���ړ�
			* @param spd:������ړ���
			*/
			void MovePos(const glm::vec3& spd);

			/**
			* @brief �X�v���C�g�̐[�x�l��ݒ�
			* @param depth:�ݒ肷��[�x�l
			*/
			void SetDepth(const float depth);

			/**
			* @brief �X�v���C�g�̑傫����ݒ�
			* @param size:�ݒ肷��傫��
			���̊֐��ł͍��㒸�_����Ɋg�債�Ă���
			*/
			void SetSize(const glm::vec2& size);

			/**
			* @brief �摜���S����ɃX�v���C�g�̑傫����ݒ�
			* @param size:�ݒ肷��傫��
			*/
			void SetSizeFromCenter(const glm::vec2& size);

			/**
			* @brief �X�v���C�g�̊�_��ݒ�
			* @param base:�ݒ肷���_
			��_�̓X�N���[�����W��̈�_���w��
			*/
			void SetBase(const glm::vec2& base);

			/**
			* @brief �X�v���C�g�̉�]�p��ݒ�
			* @param degree:�ݒ肷��p�x
			��_�����Ƃ��ĉ�]����
			*/
			void SetRotate(const float degree);

			/**
			* @brief �X�v���C�g�̉�]�p���摜���S�Őݒ�
			* @param degree:�ݒ肷��p�x
			*/
			void SetRotateFromCenter(const float degree);

			/**
			* @brief �X�v���C�g��UV�l��ݒ�
			* @param uv:�ݒ肷��uv�l
			UV�̐ݒ�͈ȉ��̒ʂ�
			x�����㒸�_��u
			y�����㒸�_��v
			z���E�����_��u
			w���E�����_��v
			*/
			void SetUV(const glm::vec4& uv);

			/**
			* @brief �X�v���C�g�̃A���t�@�l��ݒ�
			* @param alpha:�ݒ肷��A���t�@�l(0�`1)
			*/
			void SetAlpha(const float alpha);

			/**
			* @brief �X�v���C�g�ɓ\��e�N�X�`����ύX����
			* @param fileName:�e�N�X�`���̃p�X
			*/
			void ChangeImage(const std::string& fileName);
			/**
			* @brief �X�v���C�g��`�悷��
			* @param deviceContext:�`��Ɏg�p����f�o�C�X�R���e�L�X�g
			*/
			void Draw();
		};
	}
}
#endif