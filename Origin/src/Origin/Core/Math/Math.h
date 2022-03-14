#pragma once

#include "Origin/Core/Core.h"

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

namespace Origin {
	glm::quat EulerToQuat(const glm::vec3& euler);
}