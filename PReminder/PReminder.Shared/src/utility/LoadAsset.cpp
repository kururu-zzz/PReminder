#include "pch.h"
#include <algorithm>

#include "LoadAsset.h"
#include <android/asset_manager.h>

namespace ndk
{
	const char* LoadAssetFile(AAssetManager* assetManager, pthread_mutex_t* mutex ,const char* fileName) {
		pthread_mutex_lock(mutex);
		AAsset* assetFile = AAssetManager_open(assetManager, fileName, AASSET_MODE_BUFFER);
		assert(assetFile != nullptr);
		int size = AAsset_getLength(assetFile);
		char* buf = (char*)malloc(size);
		AAsset_read(assetFile, buf, size);
		AAsset_close(assetFile);
		pthread_mutex_unlock(mutex);
		return buf;
	}
}
