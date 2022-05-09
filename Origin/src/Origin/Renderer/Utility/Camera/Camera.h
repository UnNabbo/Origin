#pragma once

#include "Origin/Core/Core.h"

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"


namespace Origin {

	class ORIGIN_API Camera {
	public:
		virtual ~Camera() = default;

		virtual const glm::mat4& GetProjectionMatrix() const = 0;
	};
}
