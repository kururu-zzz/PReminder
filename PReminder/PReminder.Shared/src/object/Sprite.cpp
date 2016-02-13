#include "pch.h"
#include <algorithm>

#include "Sprite.h"

GLuint loadShader(GLenum shaderType, const char* pSource) {
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &pSource,0);
	glCompileShader(shader);
	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	return shader;
}

GLuint createProgram(const char* pVertexSource, const char* pFragmentSource) {
	GLuint vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
	GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, pixelShader);
	glLinkProgram(program);
	GLint linkStatus = GL_FALSE;
	glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
	return program;
}

namespace gl
{

	void SetVertexPos(std::array<std::shared_ptr<Vertex::DefaultVertex>,4>& vertexList,glm::vec3 pos,glm::vec2 base,glm::vec2 size,float degree)
	{
		vertexList[0]->pos = glm::vec3(pos.x, pos.y , pos.z);
		vertexList[1]->pos = glm::vec3(pos.x + size.x, pos.y, pos.z);
		vertexList[2]->pos = glm::vec3(pos.x, pos.y + size.y, pos.z);
		vertexList[3]->pos = glm::vec3(pos.x + size.x, pos.y + size.y, pos.z);
		std::for_each(vertexList.begin(), vertexList.end(), [base](std::shared_ptr<Vertex::DefaultVertex>& vertex)
		{
			vertex->pos = vertex->pos - glm::vec3(base.x, base.y, 0.f);
		});
		glm::mat3x3 matRotate;
		
		float rad = glm::radians(degree);
		matRotate[0][0] = matRotate[1][1] = glm::cos(rad);
		matRotate[0][1] = glm::sin(rad);
		matRotate[1][0] = -glm::sin(rad);
		std::for_each(vertexList.begin(), vertexList.end(), [base,matRotate](std::shared_ptr<Vertex::DefaultVertex>& vertex)
		{
			vertex->pos = vertex->pos * matRotate;
			vertex->pos = vertex->pos + glm::vec3(base.x, base.y, 0.f);
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

	void Sprite::Init(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& texel, const std::string& fileName)
	{
		ChangeImage(fileName);

		SetPos(pos);
		SetSize(size);
		SetUV(texel);

		this->degree = 0.f;

		vertexList[0]->color = vertexList[1]->color = vertexList[2]->color = vertexList[3]->color = glm::vec4(1.f,0.f,0.f,1.f);

		this->base = glm::vec2(size.x / 2.f, size.y / 2.f);

		glm::vec3 faceEdgeA = vertexList[1]->pos - vertexList[0]->pos;
		glm::vec3 faceEdgeB = vertexList[2]->pos - vertexList[0]->pos;

		glm::vec3 faceNormal = glm::cross(faceEdgeA, faceEdgeB);

		vertexList[0]->normal = vertexList[1]->normal = vertexList[2]->normal = vertexList[3]->normal = faceNormal;
	}

	void Sprite::ChangeImage(const std::string& fileName)
	{
		this->fileName = fileName;
		//CreateTexture(fileName);
	}

	void Sprite::SetUV(const glm::vec4& texel){
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
		this->base = base;
	}

	void Sprite::SetRotate(const float degree)
	{
		this->degree = degree;
	}

	void Sprite::SetRotateFromCenter(const float degree)
	{
		this->degree = degree;
		this->base = glm::vec2(this->pos.x + this->size.x / 2, this->pos.y + this->size.y/2);
	}

	void Sprite::SetSizeFromCenter(const glm::vec2& size)
	{
		glm::vec2 difference = glm::vec2((size.x - this->size.x) / 2.f, (size.y - this->size.y) / 2.f);
		this->pos = glm::vec3(this->pos.x - difference.x, this->pos.y - difference.y, this->pos.z);
		this->size = size;
		this->base = glm::vec2(this->pos.x + this->size.x / 2, this->pos.y + this->size.y / 2);
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
		const char gVertexShader[] =
			"attribute vec4 position;\n"
			"uniform mat4 viewportMatrix;"
			"void main() {\n"
			"  gl_Position = viewportMatrix * position;\n"
			"}\n";


		const char gFragmentShader[] =
			"precision mediump float;\n"
			"void main() {\n"
			"  gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
			"}\n";

		GLuint gProgram = createProgram(gVertexShader, gFragmentShader);
		GLuint gvPositionHandle = glGetAttribLocation(gProgram, "position");

		const GLfloat vertices[] = {
			-0.5f,  0.5f,
			 0.5f,  0.5f,
			-0.5f, -0.5f,
			 0.5f, -0.5f,
		};
		glUseProgram(gProgram);
		glVertexAttribPointer(gvPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, vertices);
		glEnableVertexAttribArray(gvPositionHandle);
		//SetVertexPos(vertexList, this->pos, this->base,this->size, this->degree);
		//UpdateVertex(vertexList, deviceContext);
		//SetTexture(deviceContext,fileName);
		
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
}
