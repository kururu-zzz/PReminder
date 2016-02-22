#ifndef TEXTURE
#define TEXTURE

#include "Singleton.h"
#include <unordered_map>
#include <string>
#include <memory>

namespace gl
{
	namespace manager
	{
		/**
		* @brief �e�N�X�`���̃R���e�i�N���X
		*/
		class Texture : public Singleton<Texture>
		{
		private:
			std::unordered_map<std::string, std::shared_ptr<GLuint>> textureContainer;
		private:
			friend class Singleton<Texture>;
			Texture() {}
		public:
			/**
			* @brief �e�N�X�`���̍쐬�A�R���e�i�ɓo�^
			* @param fileName:�e�N�X�`���̃t�@�C����(�p�X��)
			*/
			void CreateTexture(const std::string& fileName);

			/**
			* @brief �e�N�X�`���̍쐬�A�R���e�i�ɓo�^
			* @param deviceContext:�e�N�X�`�����Z�b�g����R���e�L�X�g
			* @param fileName:�e�N�X�`���̃t�@�C����(�p�X��)
			* @param slotNum:�V�F�[�_�[�̃��W�X�^�ԍ�
			*/
			void SetTexture(const std::string& fileName);
		};
	}
}

#endif