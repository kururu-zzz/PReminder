#ifndef __CAMERA__
#define __CAMERA__

#ifdef __APPLE__
#define GLM_FORCE_PURE
#include <unistd.h>
#include <sys/resource.h>
#include <glm/glm.hpp>
#include <OpenGLES/ES2/gl.h>
#else
#define GLM_FORCE_PURE
#include <GLES2/gl2.h>
#include <glm/glm.hpp>
#include <unordered_map>
#endif
namespace gl
{
	namespace ConstantBuffer
	{
		/**
		* @brief カメラの定数バッファ
		*/
		struct CameraBuffer
		{
			glm::mat4x4	matView = glm::mat4x4(1.f);
			glm::mat4x4	matProjection = glm::mat4x4(1.f);
			glm::mat4x4  matViewPort = glm::mat4x4(1.f);
			glm::mat4x4	matLVP = glm::mat4x4(1.f);
			glm::vec4 eyePos = glm::vec4(1.f);
		};
	}
	namespace object
	{
		/**
		* @brief DirectX座標系に対応したカメラクラス
		*/
		class Camera {
		private:
			ConstantBuffer::CameraBuffer cameraBuffer;
			glm::vec3 pos;
			glm::vec3 focus;
			glm::vec3 upDirection;

			const float projectionDegree = 45.f;
		public:
			/**
			* @brief カメラの初期化
			* @param pos:カメラの位置
			* @param focus:カメラの焦点位置
			* @param screenSize:アプリの画面サイズ
			*/
			void Init(const glm::vec3& pos, const glm::vec3& focus, const glm::vec2& screenSize);

			/**
			* @brief カメラの位置を設定
			* @param pos:カメラの位置
			*/
			void SetPos(const glm::vec3& pos);

			/**
			* @brief カメラの焦点位置を設定
			* @param focus:カメラの焦点位置
			*/
			void SetFocus(const glm::vec3& focus);

			/**
			* @brief カメラの平行投影行列を計算する(主に分散影に使う)
			* @param pos:カメラの位置
			* @param focus:カメラの焦点
			*/
			void SetOrtho(
				const glm::vec3& pos,
				const glm::vec3& focus = glm::vec3(0.f, 0.f, 0.f));

			/**
			* @brief カメラをある点に注目させる
			* @param focus:注視点
			*/
			void RockOn(const glm::vec3& focus);

			/**
			* @brief カメラの定数バッファを取得
			*/
			const ConstantBuffer::CameraBuffer& GetBuffer();

			/**
			* @brief カメラの位置を取得
			*/
			const glm::vec3& GetPos() const {
				return pos;
			}

			/**
			* @brief カメラの焦点位置を取得
			*/
			const glm::vec3& GetFocus() const {
				return focus;
			}
		};
	}
}

#endif