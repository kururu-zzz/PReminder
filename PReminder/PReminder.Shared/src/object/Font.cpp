#include "Font.h"
#include "../manager/Shader.h"
#include "../manager/Texture.h"
#include "../utility/DeviceInfo.h"
#include "../utility/LoadAsset.h"

#include <algorithm>

namespace gl
{
	namespace object
	{
		void CreateFontData(const std::string& text,FT_Face face,int* widthSum)
		{
			std::vector<FT_Bitmap> bitmaps;
			std::vector<std::vector<unsigned char>> bitmapBuffers;

			bitmaps.reserve(text.size());
			bitmapBuffers.reserve(text.size());
			
			int maxRows = 0;
			for (auto& chara : text)
			{
				FT_UInt glyph_index = FT_Get_Char_Index(face,  chara);
				if (FT_Load_Glyph(face, glyph_index, FT_LOAD_RENDER)) {
					fprintf(stderr, "Could not load character\n");
				}
				auto bitmap = face->glyph->bitmap;
				bitmaps.emplace_back(bitmap);
				std::vector<unsigned char> buffer(bitmap.rows * bitmap.width);
				for (int count = 0; count < bitmap.rows * bitmap.width; ++count)
				{
					buffer[count] = bitmap.buffer[count];
				}
				bitmapBuffers.emplace_back(buffer);
				*widthSum += bitmap.width;
				maxRows = (bitmap.rows > maxRows) ? bitmap.rows : maxRows;
			}

			std::vector<unsigned char> textureData;
			textureData.reserve(*widthSum*maxRows);
			for (int row = 0;row < maxRows;++row)
			{
				for (int bitmapCount = 0;bitmapCount < bitmaps.size();++bitmapCount)
				{
					int width = bitmaps[bitmapCount].width;
					int diffRows = row - maxRows + bitmaps[bitmapCount].rows;
					for (int column = 0; column < width; ++column)
					{
						textureData.emplace_back(
							(diffRows >= 0) ? 
							bitmapBuffers[bitmapCount][diffRows * width + column] : 
							0);
					}
				}
			}

			gl::manager::Texture::Get()->CreateTextureFromMemory(
				text,
				textureData.data(),
				*widthSum,
				maxRows,
				GL_ALPHA);
		}

		static std::shared_ptr<FT_LibraryRec_> ftLib;
		Font::Font()
		{
			sprite = std::make_shared<Sprite>();
			
			if (ftLib == nullptr)
			{
				FT_Library lib;
				if (FT_Init_FreeType(&lib)) {
					fprintf(stderr, "Could not init freetype library\n");
				}
				ftLib = std::shared_ptr<FT_LibraryRec_>(lib, [](FT_Library lib)
				{
					FT_Done_FreeType(lib);
				});
			}
		}

		void Font::Init(const glm::vec3& pos, const glm::vec2& base, const glm::vec2& size, const glm::vec4& uv, const std::string& text)
		{
			sprite->Init(pos, base, size, uv, "");

			this->text = text;
			
			size_t bufferSize = 0;
			auto asset = ndk::LoadAssetFile("font/meiryo.ttc",&bufferSize);
			const FT_Byte* data = static_cast<FT_Byte*>(asset);
			{
				//auto rowFace = face;
				if (FT_New_Memory_Face(ftLib.get(), data, bufferSize, 0, &face))
				{
					fprintf(stderr, "Could not open font\n");
				}
			}
			FT_Set_Pixel_Sizes(face, 0, 48);

			int widthSum = 0;
			CreateFontData(text, face, &widthSum);
			sprite->SetSize(glm::vec2(widthSum, size.y));

			free(asset);
		}

		void Font::Draw()
		{
			gl::manager::Texture::Get()->SetTexture(text);
			sprite->Draw();
		}
	}
}
