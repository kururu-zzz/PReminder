#include "Texture.h"
#include "../utility/LoadAsset.h"
#include <assert.h>
#include <include/libpng/jni/png.h>

namespace gl
{
	namespace manager
	{
		struct TextureData
		{
			int width = 0;
			int height = 0;
			GLuint index = 0;
			~TextureData()
			{
				glDeleteTextures(1, &index);
			}
		};

		/**
		* @brief コールバック関数
		*/
		static void png_read(png_structp png, png_bytep data, png_size_t length)
		{
			uint8_t** p = (uint8_t **)png_get_io_ptr(png);         // データポインタ

			memcpy(data, *p, length);
			*p += length;
		}

		/**
		* @brief png画像の情報を色情報によって更新
		* @return アルファ情報を含むか否か
		*/
		bool UpdatePNGInfo(png_structp png, png_infop info, unsigned int* width, unsigned int* height, int* bitDepth, int* colorType)
		{
			switch (*colorType)
			{
			case PNG_COLOR_TYPE_RGB:
				return false;
			case PNG_COLOR_TYPE_PALETTE:
				png_set_palette_to_rgb(png);
				png_read_update_info(png, info);
				png_get_IHDR(png, info, width, height, bitDepth, colorType, nullptr, nullptr, nullptr);
				return (*colorType != PNG_COLOR_TYPE_RGB);
			case PNG_COLOR_TYPE_GRAY:
				png_set_gray_to_rgb(png);
				png_read_update_info(png, info);
				return false;

			case PNG_COLOR_TYPE_GRAY_ALPHA:
				png_set_gray_to_rgb(png);
				png_read_update_info(png, info);
				return true;
			default:
				return true;
			}
		}

		GLuint CreateTextureId(uint8_t* data,const unsigned int width,const unsigned int height,int format)
		{
			// テクスチャの生成を行う
			GLuint textureId;
			glGenTextures(1, &textureId);
			assert(textureId != 0);
			assert(glGetError() == GL_NO_ERROR);

			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			assert(glGetError() == GL_NO_ERROR);

			glBindTexture(GL_TEXTURE_2D, textureId);
			assert(glGetError() == GL_NO_ERROR);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			assert(glGetError() == GL_NO_ERROR);
			return textureId;
		}

		void CreateTextureData(TextureData* textureData,const char* data)
		{
			png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
			if (png == nullptr) 
			{
				throw std::runtime_error("png_create_read_struct error");
				return;
			}
			png_infop info = png_create_info_struct(png);
			if (info == nullptr)
			{
				throw std::runtime_error("png_create_info_struct error");
				return;
			}

			png_set_read_fn(png, nullptr, png_read);
			png_init_io(png, (png_FILE_p)&data);
			png_read_info(png, info);
			unsigned int width, height;
			int bitDepth,colorType;
			png_get_IHDR(png, info, &width, &height, &bitDepth, &colorType, nullptr, nullptr, nullptr);
			
			bool isAlpha = UpdatePNGInfo(png, info, &width, &height, &bitDepth, &colorType);

			int rowBytes = width*(3 + isAlpha);
			uint8_t* buffer = (uint8_t*)memalign(4, rowBytes*height);
			png_bytep rows[height];

			assert(buffer != nullptr);
			for (int i = 0; i < height; i++) 
			{
				rows[i] = buffer + i*rowBytes;
			}
			png_read_image(png, rows);

			textureData->width = width;
			textureData->height = height;
			textureData->index = CreateTextureId(buffer, width, height,GL_RGB + isAlpha);

			png_destroy_read_struct(&png, &info, NULL);
		}
		void Texture::CreateTexture(const std::string& fileName)
		{
			if (textureContainer.find(fileName) == textureContainer.end())
			{
				size_t size = 0;
				auto asset = ndk::LoadAssetFile(fileName.c_str(), &size);
				const char* data = static_cast<char*>(asset);

				std::shared_ptr<TextureData> textureData = std::make_shared<TextureData>();
				// 画像ピクセルを読み込む
				CreateTextureData(textureData.get(),data);

				textureContainer.emplace(fileName, textureData);

				free(asset);
			}
		}

		void Texture::CreateTextureFromMemory(
			const std::string& keyName,
			unsigned char* data,
			unsigned int width,
			unsigned int height,
			int format
		)
		{
			if (textureContainer.find(keyName) == textureContainer.end())
			{
				std::shared_ptr<TextureData> textureData = std::make_shared<TextureData>();
				textureData->width = width;
				textureData->height = height;
				// 画像ピクセルを読み込む
				textureData->index = CreateTextureId(data,width,height,format);

				textureContainer.emplace(keyName, textureData);
			}
		}

		void Texture::SetTexture(const std::string& fileName)
		{
			if (fileName != "")
			{
				glBindTexture(GL_TEXTURE_2D, textureContainer.at(fileName)->index);
				assert(glGetError() == GL_NO_ERROR);
			}
		}
	}
}