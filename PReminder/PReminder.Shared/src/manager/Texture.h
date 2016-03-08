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
		struct TextureData;
		/**
		* @brief �e�N�X�`���̃R���e�i�N���X
		*/
		class Texture : public Singleton<Texture>
		{
		private:
			std::unordered_map<std::string, std::shared_ptr<TextureData>> textureContainer;
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
			*/
			void SetTexture(const std::string& fileName, const GLuint program, const std::string& name);
		};
	}
}

#endif