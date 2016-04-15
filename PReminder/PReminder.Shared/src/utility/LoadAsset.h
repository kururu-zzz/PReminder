#ifndef LOADASSET
#define LOADASSET

#ifdef __APPLE__
#define GLM_FORCE_PURE
#include <unistd.h>
#include <sys/resource.h>
#include <glm/glm.hpp>
#include <OpenGLES/ES2/gl.h>
#else
#define GLM_FORCE_PURE
#include <GLES2/gl2.h>
#include <include/glm/glm.hpp>
#include <array>
#include <string>
#include <memory>
#include <pthread.h>
#endif

struct AAssetManager;

namespace ndk
{
	void* LoadAssetFile(AAssetManager* assetManager, pthread_mutex_t* mutex , const char* fileName);
}
#endif