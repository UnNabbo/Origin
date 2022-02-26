#include "OGpch.h"

#include "RenderCommand.h"

#include "Platform/Opengl/OpenGLRendererAPI.h"

namespace Origin {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

}