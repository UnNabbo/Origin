#pragma once

#include "Origin/Core/Core.h"
#include "Origin/Renderer/Primitives/Texture.h"
#include "Origin/Core/Math/Math.h"
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "Origin/Renderer/Utility/Camera/SceneCamera.h"

namespace Origin 
	{

	struct TagComponent {
		std::string Tag;

		operator std::string() {
			return Tag;
		}
	};

	struct TransformComponent {
		glm::mat4 Transform;
		glm::vec3 Position;
		glm::vec3 Rotation;
		glm::vec3 Scale;


		TransformComponent(glm::vec3& position = glm::vec3{0,0,0}, glm::vec3& rotation = glm::vec3{ 0,0,0 }, glm::vec3& scale = glm::vec3{ 0,0,0 }) : Position(position), Rotation(rotation), Scale(scale){}



		operator glm::mat4() const {
			return ((Position != glm::vec3{ 0,0,0 }) ? glm::translate(glm::mat4(1), Position) : glm::mat4(1))
				* ((Rotation != glm::vec3{ 0,0,0 }) ? glm::toMat4(EulerToQuat(Rotation)) : glm::mat4(1))
				* ((Scale != glm::vec3{ 1,1,1 }) ? glm::scale(glm::mat4(1), Scale) : glm::mat4(1));;
		}
	};

	struct SpriteRenderComponent {
		glm::vec4 color{1,1,1,1};
		Reference<Texture2D> texture;
	};

	struct CameraComponent {
		SceneCamera camera;
		bool Main = false;
		bool FixedViewPort = false;

		glm::vec4 ClearColor;

		operator glm::mat4() const {
			return camera.GetProjectionMatrix();
		}

		CameraComponent(uint32_t x, uint32_t y, glm::vec4& clearColor = glm::vec4{ 0.1f, 0.1f, 0.1f, 1.0f }, bool isMain = false) : camera(x, y), ClearColor(clearColor), Main(isMain) {}
	};
}