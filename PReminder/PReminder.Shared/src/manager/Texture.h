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
		* @brief テクスチャのコンテナクラス
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
			* @brief テクスチャの作成、コンテナに登録
			* @param fileName:テクスチャのファイル名(パス込)
			*/
			void CreateTexture(const std::string& fileName);

			/**
			* @brief テクスチャをバッファから作成、コンテナに登録
			* @param keyName:テクスチャの登録名
			* @param data:テクスチャの元データ
			*/
			void CreateTextureFromMemory(
				const std::string& keyName, 
				unsigned char* data,
				unsigned int width,
				unsigned int height,
				int format = GL_RGBA
			);

			/**
			* @brief テクスチャの作成、コンテナに登録
			*/
			void SetTexture(const std::string& fileName);
		};
	}
}

#endif