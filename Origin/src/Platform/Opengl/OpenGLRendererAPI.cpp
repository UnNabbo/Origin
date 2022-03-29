#include "OGpch.h"

#include "OpenGLRendererAPI.h"

#include "glad/glad.h"

namespace Origin {
	void OpenGLMessageCallback(
		uint32_t source,
		uint32_t type,
		uint32_t id,
		uint32_t severity,
		int length,
		const char* message,
		const void* userParam){
		switch (severity) {
		case GL_DEBUG_SEVERITY_HIGH:         ORIGIN_ASSERT(false, message); return;
		case GL_DEBUG_SEVERITY_MEDIUM:       ORIGIN_ERROR(message); return;
		case GL_DEBUG_SEVERITY_LOW:          ORIGIN_WARN(message); return;
		case GL_DEBUG_SEVERITY_NOTIFICATION: ORIGIN_TRACE(message); return;
		}

		ORIGIN_ASSERT(false, "Unknown severity level!");
	}


	void OpenGLRendererAPI::Init() {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
	}
	
	void OpenGLRendererAPI::SetWireFrameView(bool state) {
		if (state) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		} else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}

	void OpenGLRendererAPI::ResizeWindow(uint32_t width, uint32_t height) {
		glViewport(0, 0, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color) {
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Reference<VertexArray>& vertexArray, const uint32_t count) {
		uint32_t indexCount = count ? vertexArray->GetIndexBuffers()->GetCount() : count;
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
	}
}