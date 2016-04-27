#include <algorithm>

#include "Sprite.h"
#include "../manager/Shader.h"
#include "../manager/Texture.h"
#include "../utility/DeviceInfo.h"

namespace gl
{
	namespace object
	{
		void SetVertexPos(std::array<std::shared_ptr<Vertex::DefaultVertex>, 4>& vertexList, glm::vec3 pos, glm::vec2 base,glm::vec2 size, float degree)
		{
			auto baseSize = size * base;
			vertexList[0]->pos = glm::vec3(-baseSize.x, -baseSize.y, 0.f);
			vertexList[1]->pos = glm::vec3(size.x - baseSize.x, -baseSize.y, 0.f);
			vertexList[2]->pos = glm::vec3(-baseSize.x,  size.y - baseSize.y, 0.f);
			vertexList[3]->pos = glm::vec3(size.x - baseSize.x,size.y - baseSize.y, 0.f);

			const float rad = glm::radians(degree);
			const glm::mat3x3 matRotate = glm::mat3x3(glm::cos(rad), glm::sin(rad),0.f, -glm::sin(rad), glm::cos(rad),0.f,0.f,0.f,0.f);
			std::for_each(vertexList.begin(), vertexList.end(), [pos, matRotate](std::shared_ptr<Vertex::DefaultVertex>& vertex)
			{
				vertex->pos = vertex->pos * matRotate;
				vertex->pos = vertex->pos + pos;
			});
		}

		/*void UpdateVertex(const std::array<std::shared_ptr<Vertex::DefaultVertex>, 4>& vertexList, ID3D11DeviceContext* deviceContext)
		{
			std::array<Vertex::DefaultVertex, 4> v;
			for (int i = 0; i < 4; i++)
			{
				v[i] = *vertexList[i];
			}
			D3D11_MAPPED_SUBRESOURCE resource;
			auto hr = deviceContext->Map(vb.get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
			if (SUCCEEDED(hr)) {
				auto param = (Vertex::DefaultVertex*)(resource.pData);
				for (int i = 0; i < 4; ++i)
				{
					param[i] = v[i];
				}
				deviceContext->Unmap(vb.get(), 0);
			}
		}*/

		Sprite::Sprite()
		{
			for (auto& vertex : vertexList)
			{
				vertex = std::make_shared<Vertex::DefaultVertex>();
			}
			/*if (vb == nullptr)
			{
				ID3D11Buffer* vbuf;
				DX11::Resource::CreateBuffer(&vbuf, (void*)vertexList.data(), sizeof(Vertex::DefaultVertex)* vertexList.size(), D3D11_CPU_ACCESS_WRITE, D3D11_BIND_VERTEX_BUFFER);
				vb = std::shared_ptr<ID3D11Buffer>(vbuf, [](ID3D11Buffer* p)
				{
					p->Release();
				});
			}*/
		}

		void Sprite::Init(const glm::vec3& pos, const glm::vec2& base, const glm::vec2& size, const glm::vec4& texel, const std::string& fileName)
		{
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
		}

		void Sprite::ChangeImage(const std::string& fileName)
		{
			if (fileName != "")
			{
				this->fileName = fileName;
				manager::Texture::Get()->CreateTexture(fileName);
			}
		}

		void Sprite::SetUV(const glm::vec4& texel) {
			vertexList[0]->texel = glm::vec2(texel.x, texel.y);
			vertexList[1]->texel = glm::vec2(texel.z, texel.y);
			vertexList[2]->texel = glm::vec2(texel.x, texel.w);
			vertexList[3]->texel = glm::vec2(texel.z, texel.w);
		}

		void Sprite::SetPos(const glm::vec3& pos) {
			this->pos = pos;
			if (this->pos.z >= 1.0f)
				this->pos.z = 0.99999f;
		}

		void Sprite::MovePos(const glm::vec3& spd)
		{
			this->pos = this->pos + spd;
		}

		void Sprite::SetDepth(const float depth)
		{
			this->pos.z = depth;
			if (this->pos.z >= 1.0f)
				this->pos.z = 0.99999f;
		}

		void Sprite::SetBase(const glm::vec2& base)
		{
			if(base.x <= 1.f && base.x >= 0.f && base.y <= 1.f && base.y >= 0.f)
				this->base = base;
		}

		void Sprite::SetRotate(const float degree)
		{
			this->degree = degree;
		}

		void Sprite::SetSizeFromCenter(const glm::vec2& size)
		{
			glm::vec2 difference = glm::vec2((size.x - this->size.x) / 2.f, (size.y - this->size.y) / 2.f);
			this->pos = glm::vec3(this->pos.x - difference.x, this->pos.y - difference.y, this->pos.z);
			this->size = size;
		}

		void Sprite::SetAlpha(const float alpha)
		{
			std::for_each(vertexList.begin(), vertexList.end(), [alpha](std::shared_ptr<Vertex::DefaultVertex>& vertex)
			{
				if (alpha <= 0.f)
				{
					vertex->color = glm::vec4(0.f, 0.f, 0.f, 0.f);
				}
				else if (alpha >= 1.f)
				{
					vertex->color = glm::vec4(1.f, 0.f, 0.f, 1.f);
				}
				else
				{
					vertex->color = glm::vec4(alpha, 0.f, 0.f, alpha);
				}
			});
		}

		void Sprite::SetSize(const glm::vec2& size)
		{
			this->size = size;
		}

		void Sprite::Draw()
		{
			auto shaderManager = manager::Shader::Get();
			auto program = shaderManager->CreateProgram(
				"sprite", 
				shaderManager->CreateShader(GL_VERTEX_SHADER, "sprite", "shader/sprite.vert"),
				shaderManager->CreateShader(GL_FRAGMENT_SHADER, "sprite", "shader/sprite.frag"));

			GLuint gvPositionHandle = glGetAttribLocation(program, "position");
			GLuint gvUVHandle = glGetAttribLocation(program, "attr_uv");
			static glm::mat4x4 viewportMatrix = glm::mat4x4();
			viewportMatrix[0][0] = 2.f / device::info::GetWindowSize().x;
			viewportMatrix[1][1] = -2.0f / device::info::GetWindowSize().y;
			viewportMatrix[3][0] = -1.f;
			viewportMatrix[3][1] = 1.0f;
			GLuint viewportHandle = glGetUniformLocation(program, "viewportMatrix");

			SetVertexPos(vertexList, this->pos, this->base, this->size, this->degree);
			const std::array<glm::vec3, 4> vertices =
			{
				{
				vertexList[0]->pos,
				vertexList[1]->pos,
				vertexList[2]->pos,
				vertexList[3]->pos,
				}
			};

			const std::array<glm::vec2, 4> uvs =
			{
				{
					vertexList[0]->texel,
					vertexList[1]->texel,
					vertexList[2]->texel,
					vertexList[3]->texel,
				}
			};
			
			glUseProgram(program);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			gl::manager::Texture::Get()->SetTexture(this->fileName);
			glVertexAttribPointer(gvPositionHandle, 3, GL_FLOAT, false, 0, vertices.data());
			glVertexAttribPointer(gvUVHandle, 2, GL_FLOAT, false, 0, uvs.data());
			glEnableVertexAttribArray(gvPositionHandle);
			glEnableVertexAttribArray(gvUVHandle);
			glUniformMatrix4fv(viewportHandle, 1, false, &(viewportMatrix[0][0]));
			
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		}
	}
}
