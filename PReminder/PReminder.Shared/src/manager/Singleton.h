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
		*@brief OpenGL ES2.0�p�V���O���g�����N���X
		*/
		template<typename T>
		class Singleton {
		protected:
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
			* @brief �V���O���g���N���X�̏�����
			* @param assetManager:engine��AAssetManager
			* @param mutex:engine����mutex
			*/
			void Init()
			{
			}
		};
	}
}

#endif