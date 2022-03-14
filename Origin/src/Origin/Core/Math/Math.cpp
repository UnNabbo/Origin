#include "OGpch.h"
#include "Math.h"

namespace Origin {
	glm::quat EulerToQuat(const glm::vec3& euler) {
		glm::quat quat;

		double cy = cos(euler.z * 0.5);
		double sy = sin(euler.z * 0.5);
		double cp = cos(euler.y * 0.5);
		double sp = sin(euler.y * 0.5);
		double cr = cos(euler.x * 0.5);
		double sr = sin(euler.x * 0.5);

		quat.w = cr * cp * cy + sr * sp * sy;
		quat.x = sr * cp * cy - cr * sp * sy;
		quat.y = cr * sp * cy + sr * cp * sy;
		quat.z = cr * cp * sy - sr * sp * cy;
		return quat;
	}
}