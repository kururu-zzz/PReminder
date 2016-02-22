#ifndef BASEMANAGER
#define BASEMANAGER

#include <GLES2/gl2.h>
#include <pthread.h>
#include <android/asset_manager.h>

namespace gl
{
	namespace manager
	{
		/**
		*@brief OpenGL ES2.0用シングルトン基底クラス
		*/
		template<typename T>
		class Singleton {
		protected:
			AAssetManager* assetManager; ///< engineからInitで取得
			pthread_mutex_t* mutex; ///< engineからInitで取得
		protected:
			Singleton() {};
			Singleton(const Singleton& rhs)=delete;
			Singleton& operator=(const Singleton& rhs)=delete;
		public:
			static T* Get() 
			{
				static T instance;
				return &instance;
			}
			/**
			* @brief シングルトンクラスの初期化
			* @param assetManager:engineのAAssetManager
			* @param mutex:engine内のmutex
			*/
			void Init(AAssetManager* assetManager, pthread_mutex_t* mutex)
			{
				this->assetManager = assetManager;
				this->mutex = mutex;
			}
		};
	}
}

#endif