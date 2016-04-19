#include "Font.h"
#include <include/ft2build.h>
#include FT_FREETYPE_H
#include "../manager/Shader.h"
#include "../manager/Texture.h"
#include "../utility/DeviceInfo.h"

#include <algorithm>

namespace gl
{
	namespace object
	{
		Font::Font()
		{
			sprite = std::make_shared<Sprite>();
			FT_Library ft;

			if (FT_Init_FreeType(&ft)) {
				fprintf(stderr, "Could not init freetype library\n");
				std::exception();
			}

			FT_Face face;

			if (FT_New_Face(ft, "FreeSans.ttf", 0, &face)) {
				fprintf(stderr, "Could not open font\n");
			}
		}

		void Font::Init(const glm::vec3& pos, const glm::vec2& base, const glm::vec2& size, const glm::vec4& texel, const std::string& fileName)
		{
			/*
			ChangeImage(fileName);

			SetPos(pos);
			SetBase(base);
			SetSize(size);
			SetUV(texel);

			this->degree = 0.f;

			vertexList[0]->color = vertexList[1]->color = vertexList[2]->color = vertexList[3]->color = glm::vec4(1.f, 0.f, 0.f, 1.f);

			glm::vec3 faceEdgeA = vertexList[1]->pos - vertexList[0]->pos;
			glm::vec3 faceEdgeB = vertexList[2]->pos - vertexList[0]->pos;

			glm::vec3 faceNormal = glm::cross(faceEdgeA, faceEdgeB);

			vertexList[0]->normal = vertexList[1]->normal = vertexList[2]->normal = vertexList[3]->normal = faceNormal;
			*/
		}

		void Font::Draw()
		{
			sprite->Draw();
		}
	}
}
