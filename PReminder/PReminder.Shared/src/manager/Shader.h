#ifndef SHADER
#define SHADER

#include "Singleton.h"
#include <unordered_map>
#include <vector>
#include <memory>
#include <string>

namespace gl
{
	namespace manager
	{
		/**
		*@brief �V�F�[�_�[�Ǘ��N���X
		*/
		class Shader : public Singleton<Shader> {
		private:
			std::unordered_map<std::string, GLuint> programContainer;
			std::unordered_map<GLenum, std::unordered_map<std::string, GLuint>> shaderContainer; ///< �V�F�[�_�[
		private:
			friend class Singleton<Shader>;
			Shader();
		public:
			~Shader();
			/**
			*@brief �V�F�[�_�[�̍쐬
			*@param shaderType:�V�F�[�_�[�̎��
			*@param functionName:�V�F�[�_�[�̖��O
			*@param fileName:�V�F�[�_�[�̃t�@�C����
			*/
			const GLuint& CreateShader(const GLenum shaderType, const std::string& shaderName, const std::string& fileName);

			/**
			*@brief �V�F�[�_�[�v���O�����̍쐬
			*@param programName:�V�F�[�_�[�v���O�����̖��O
			*/
			const GLuint& CreateProgram(const std::string& programName,GLuint vertexShader = 0,GLuint fragmentShader = 0);

			/**
			*@brief �W�I���g���V�F�[�_�[�̍쐬
			*@param keyName:�R���e�i�ɓo�^����L�[�̖��O
			*@param functionName:�V�F�[�_�[�̊֐���
			*@param fileName:�V�F�[�_�[�̃t�@�C����
			*/
			//const std::shared_ptr<GLuint>& CreateGeometryShader(const std::string& keyName, const std::string& functionName, const std::string& fileName);


			/**
			*@brief �V�F�[�_�[�̓o�^
			*@param deviceContext:�V�F�[�_�[��o�^����f�o�C�X�R���e�L�X�g
			*@param shaderSet:�V�F�[�_�[�̏W��
			*/
			//void SetShader(ID3D11DeviceContext* deviceContext, const ShaderSet& shaderSet);

			/**
			*@brief �V�F�[�_�[�𖢓o�^�̏�Ԃɂ���
			*@param deviceContext:�V�F�[�_�[�����Z�b�g����f�o�C�X�R���e�L�X�g
			*/
			//void ResetShader(ID3D11DeviceContext* deviceContext);

			/**
			*@brief ���_���C�A�E�g���Z�b�g����
			*@param deviceContext:�Z�b�g����f�o�C�X�R���e�L�X�g
			*/
			//void SetLayout(ID3D11DeviceContext* deviceContext);
		};
	}
}

#endif