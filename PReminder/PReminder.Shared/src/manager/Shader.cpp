#include "Shader.h"
#include "../utility/LoadAsset.h"
#include <algorithm>

namespace gl
{
	namespace manager
	{
		GLuint CompileShader(AAssetManager* assetManager, pthread_mutex_t* mutex, GLenum shaderType, const std::string& fileName) {
			auto resource = ndk::LoadAssetFile(assetManager, mutex, fileName.c_str());
			GLuint shader = glCreateShader(shaderType);
			glShaderSource(shader, 1, &resource, 0);
			glCompileShader(shader);
			GLint result;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

			if (result == 0)
			{
				GLint infoLogLength;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

				std::vector<GLchar> infoLog(infoLogLength);
				glGetShaderInfoLog(shader, (GLsizei)infoLog.size(), NULL, infoLog.data());

				std::string errorMessage = std::string("Shader compilation failed: ");
				errorMessage += std::string(infoLog.begin(), infoLog.end());

				throw std::runtime_error(errorMessage.c_str());
			}
			//free(resource);
			return shader;
		}
		Shader::Shader()
		{
			shaderContainer.reserve(2);
			shaderContainer.emplace(GL_VERTEX_SHADER, std::unordered_map<std::string, GLuint>());
			shaderContainer.emplace(GL_FRAGMENT_SHADER, std::unordered_map<std::string, GLuint>());
		}

		Shader::~Shader()
		{
			for (auto& container : shaderContainer)
			{
				for (auto& shader : container.second)
				{
					glDeleteShader(shader.second);
				}
			}
			for (auto& program : programContainer)
			{
				glDeleteProgram(program.second);
			}
		}

		const GLuint& Shader::CreateProgram(const std::string& programName, GLuint vertexShader, GLuint fragmentShader) {
			if (programContainer.find(programName) == programContainer.end())
			{
				auto program = glCreateProgram();
				assert(program != 0);
				programContainer.emplace(programName, program);
				if (vertexShader != 0 && fragmentShader != 0)
				{
					glAttachShader(programContainer[programName], vertexShader);
					glAttachShader(programContainer[programName], fragmentShader);
					glLinkProgram(programContainer[programName]);
				}
			}
			return programContainer[programName];
		}

		const GLuint& Shader::CreateShader(const GLenum shaderType, const std::string& shaderName, const std::string& fileName)
		{
			if (shaderContainer.find(shaderType) != shaderContainer.end() && shaderContainer[shaderType].find(shaderName) == shaderContainer[shaderType].end())
			{
				GLuint shader = CompileShader(assetManager, mutex, shaderType, fileName);
				shaderContainer[shaderType].emplace(shaderName, shader);
			}
			return shaderContainer[shaderType][shaderName];
		}
	}
}