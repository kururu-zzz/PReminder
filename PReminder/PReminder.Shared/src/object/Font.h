#ifndef FONT
#define FONT

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
#include <ft2build.h>
#include FT_FREETYPE_H
#include <array>
#include <string>
#include <memory>

#include "Sprite.h"
#endif

namespace gl
{
	namespace object
	{
		/**
		* @brief 2D描画用フォントクラス
		*/
		class Font
		{
		private:
			std::shared_ptr<Sprite> sprite;
			FT_Face face;
			//std::shared_ptr<FT_FaceRec_> face;
			std::string text;
			/*
			glm::vec3 pos;
			glm::vec2 size;
			glm::vec2 base;
			float degree;
			std::array<std::shared_ptr<Vertex::DefaultVertex>, 4> vertexList;
			std::string fileName;*/
		public:
			Font();

			/**
			* @brief スプライトの初期化
			* @param pos:初期位置(スクリーン座標)
			* @param base:回転や位置の基準点(x,y座標を0〜1で指定)
			* @param size:初期サイズ
			* @param uv:設定するUV値
			* @param text:初期の文章
			UVの設定は以下の通り
			x→左上頂点のu
			y→左上頂点のv
			z→右下頂点のu
			w→右下頂点のv
			*/
			void Init(
				const glm::vec3& pos,
				const glm::vec2& base,
				const glm::vec2& size,
				const glm::vec4& uv,
				const std::string& text);

			/**
			* @brief スプライトの座標位置を設定
			* @param pos:設定する位置(スクリーン座標)
			*/
			//void SetPos(const glm::vec3& pos);

			/**
			* @brief スプライトの座標位置を移動
			* @param spd:加える移動量
			*/
			//void MovePos(const glm::vec3& spd);

			/**
			* @brief スプライトの深度値を設定
			* @param depth:設定する深度値
			*/
			//void SetDepth(const float depth);

			/**
			* @brief スプライトの大きさを設定
			* @param size:設定する大きさ
			この関数では左上頂点を基準に拡大していく
			*/
			//void SetSize(const glm::vec2& size);

			/**
			* @brief 画像中心を基準にスプライトの大きさを設定
			* @param size:設定する大きさ
			*/
			//void SetSizeFromCenter(const glm::vec2& size);

			/**
			* @brief スプライトの基準点を設定
			* @param base:設定する基準点
			基準点は画像上の一点を指定
			*/
			//void SetBase(const glm::vec2& base);

			/**
			* @brief スプライトの回転角を設定
			* @param degree:設定する角度
			基準点を軸として回転する
			*/
			//void SetRotate(const float degree);

			/**
			* @brief スプライトの回転角を画像中心で設定
			* @param degree:設定する角度
			*/
			//void SetRotateFromCenter(const float degree);

			/**
			* @brief スプライトのUV値を設定
			* @param uv:設定するuv値
			UVの設定は以下の通り
			x→左上頂点のu
			y→左上頂点のv
			z→右下頂点のu
			w→右下頂点のv
			*/
			//void SetUV(const glm::vec4& uv);

			/**
			* @brief スプライトのアルファ値を設定
			* @param alpha:設定するアルファ値(0〜1)
			*/
			//void SetAlpha(const float alpha);

			/**
			* @brief スプライトに貼るテクスチャを変更する
			* @param fileName:テクスチャのパス
			*/
			//void ChangeImage(const std::string& fileName);
			/**
			* @brief スプライトを描画する
			* @param deviceContext:描画に使用するデバイスコンテキスト
			*/
			void Draw();
		};
	}
}
#endif