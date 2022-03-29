#pragma once

#include "Origin/Core/Application.h"
#include "Origin/Utility/Log/Log.h"
#include "Origin/Utility/Time/Time.h"

#include "Origin/Layer/Layer.h"
#include "Origin/Utility/Imgui/ImGuiLayer.h"

#include "Origin/Renderer/Renderer.h"
#include "Origin/Renderer/Renderer2D.h"
#include "Origin/Renderer/RenderCommand.h"

#include "Origin/Renderer/Primitives/Buffers.h"
#include "Origin/Renderer/Primitives/Shader.h"
#include "Origin/Renderer/Primitives/VertexArray.h"
#include "Origin/Renderer/Primitives/TextureAtlas.h"
#include "Origin/Renderer/Primitives/Texture.h"

#include "Origin/Renderer/Utility/Camera/CameraControllers/EditorCamera.h"
#include "Origin/Renderer/Utility/Camera/OrthographicCamera.h"

#include "Origin/Core/Math/Math.h"

#ifdef OG_ENTRYPOINT
#include "Origin/Core/EntryPoint.h"
#endif