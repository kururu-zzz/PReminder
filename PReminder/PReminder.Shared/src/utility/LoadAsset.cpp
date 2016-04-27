#include <algorithm>

#include "LoadAsset.h"
#include <android/asset_manager.h>

namespace ndk
{
	static AAssetManager* assetManager;
	static pthread_mutex_t* mutex;

	void PrepareLoadAsset(AAssetManager* assetManager, pthread_mutex_t* mutex)
	{
		ndk::assetManager = assetManager;
		ndk::mutex = mutex;
	}
	void* LoadAssetFile(const char* fileName, size_t* size) {
		pthread_mutex_lock(mutex);
		AAsset* assetFile = AAssetManager_open(assetManager, fileName, AASSET_MODE_BUFFER);
		assert(assetFile != nullptr);
		*size = AAsset_getLength(assetFile);
		void* buf = malloc(*size);
		AAsset_read(assetFile, buf, *size);
		AAsset_close(assetFile);
		pthread_mutex_unlock(mutex);
		return buf;
	}
}
