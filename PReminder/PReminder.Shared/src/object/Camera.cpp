#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace gl
{
	namespace object
	{
		void Camera::Init(const glm::vec3& pos, const glm::vec3& focus, const glm::vec2& screenSize)
		{
			this->pos = pos;
			this->focus = focus;

			this->upDirection.x = this->upDirection.z = 0;
			this->upDirection.y = 1;

			cameraBuffer.matView = glm::transpose(glm::lookAtRH(
				this->pos,
				this->focus,
				this->upDirection));

			cameraBuffer.matProjection = glm::transpose(glm::perspectiveFovRH(
				glm::radians(projectionDegree),
				screenSize.x,
				screenSize.y,
				10.0f,
				15000.0f));

		}

		const ConstantBuffer::CameraBuffer& Camera::GetBuffer() {
			cameraBuffer.eyePos = glm::vec4(this->pos.x, this->pos.y, this->pos.z, 1.0f);
			return cameraBuffer;
		}

		void Camera::SetPos(const glm::vec3& pos)
		{
			this->pos = pos;
			if ((this->pos.x == this->focus.x) && (this->pos.y == this->focus.y) && (this->pos.z == this->focus.z))//LookAtRH—p‚Ì•â³
				this->pos.z += 0.01f;
			cameraBuffer.matView = glm::transpose(glm::lookAtRH(
				this->pos,
				this->focus,
				this->upDirection));
		}

		void Camera::SetFocus(const glm::vec3& focus)
		{
			this->focus = focus;
			if ((this->pos.x == this->focus.x) && (this->pos.y == this->focus.y) && (this->pos.z == this->focus.z))//LookAtRH—p‚Ì•â³
				this->pos.z += 0.01f;
			cameraBuffer.matView = glm::transpose(glm::lookAtRH(
				this->pos,
				this->focus,
				this->upDirection));
		}

		void Camera::SetOrtho(const glm::vec3& pos, const glm::vec3& focus)
		{
			glm::mat4x4 matLightProjection, matLightView = glm::mat4x4(1.f);
			matLightProjection = glm::ortho(0.f, 1000.f, 0.f, 1000.f, 1.f, 10000.f);

			cameraBuffer.matView = glm::transpose(glm::lookAtRH(
				this->pos,
				this->focus,
				this->upDirection));
			cameraBuffer.matLVP = glm::transpose(matLightView*matLightProjection);
		}

		void Camera::RockOn(const glm::vec3& focus)
		{
			float rockSpd = 10.0f;
			glm::vec3 spd = glm::vec3(0.f, 0.f, 0.f);
			this->pos = focus - this->focus;
			spd.x /= rockSpd; spd.y /= rockSpd; spd.z /= rockSpd;
			this->focus = this->focus + spd;
		}
	}
}