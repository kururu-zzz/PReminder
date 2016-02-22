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
		* @brief テクスチャのコンテナクラス
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
			* @brief テクスチャの作成、コンテナに登録
			* @param fileName:テクスチャのファイル名(パス込)
			*/
			void CreateTexture(const std::string& fileName);

			/**
			* @brief テクスチャの作成、コンテナに登録
			* @param deviceContext:テクスチャをセットするコンテキスト
			* @param fileName:テクスチャのファイル名(パス込)
			* @param slotNum:シェーダーのレジスタ番号
			*/
			void SetTexture(const std::string& fileName);
		};
	}
}

#endif