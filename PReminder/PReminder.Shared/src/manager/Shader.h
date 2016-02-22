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
		*@brief シェーダー管理クラス
		*/
		class Shader : public Singleton<Shader> {
		private:
			std::unordered_map<std::string, GLuint> programContainer;
			std::unordered_map<GLenum, std::unordered_map<std::string, GLuint>> shaderContainer; ///< シェーダー
		private:
			friend class Singleton<Shader>;
			Shader();
		public:
			~Shader();
			/**
			*@brief シェーダーの作成
			*@param shaderType:シェーダーの種類
			*@param functionName:シェーダーの名前
			*@param fileName:シェーダーのファイル名
			*/
			const GLuint& CreateShader(const GLenum shaderType, const std::string& shaderName, const std::string& fileName);

			/**
			*@brief シェーダープログラムの作成
			*@param programName:シェーダープログラムの名前
			*/
			const GLuint& CreateProgram(const std::string& programName,GLuint vertexShader = 0,GLuint fragmentShader = 0);

			/**
			*@brief ジオメトリシェーダーの作成
			*@param keyName:コンテナに登録するキーの名前
			*@param functionName:シェーダーの関数名
			*@param fileName:シェーダーのファイル名
			*/
			//const std::shared_ptr<GLuint>& CreateGeometryShader(const std::string& keyName, const std::string& functionName, const std::string& fileName);


			/**
			*@brief シェーダーの登録
			*@param deviceContext:シェーダーを登録するデバイスコンテキスト
			*@param shaderSet:シェーダーの集合
			*/
			//void SetShader(ID3D11DeviceContext* deviceContext, const ShaderSet& shaderSet);

			/**
			*@brief シェーダーを未登録の状態にする
			*@param deviceContext:シェーダーをリセットするデバイスコンテキスト
			*/
			//void ResetShader(ID3D11DeviceContext* deviceContext);

			/**
			*@brief 頂点レイアウトをセットする
			*@param deviceContext:セットするデバイスコンテキスト
			*/
			//void SetLayout(ID3D11DeviceContext* deviceContext);
		};
	}
}

#endif