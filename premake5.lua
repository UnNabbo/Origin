workspace "Origin"
    architecture "x64"
    startproject "Sandbox"


    configurations{
        "Debug",
        "Release",
        "Dist"
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    IncludeDir = {}
    IncludeDir["GLFW"] = "Origin/vendor/glfw/include"
    IncludeDir["Glad"] = "Origin/vendor/Glad/include"
    IncludeDir["ImGui"] = "Origin/vendor/ImGui"
    IncludeDir["glm"] = "Origin/vendor/glm"



    include "Origin/vendor/GLFW"
    include "Origin/vendor/Glad"
    include "Origin/vendor/ImGui"



    project "Origin"
        location "Origin"
        kind "StaticLib"
        staticruntime "on"
        language "C++"
        cppdialect "C++17"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

        pchheader "OGpch.h"
        pchsource "Origin/src/OGpch.cpp"

        files{
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
        }

        includedirs{
            "%{prj.name}/vendor/spdlog/include",
            "Origin/src",
            "%{IncludeDir.GLFW}",
            "%{IncludeDir.Glad}",
            "%{IncludeDir.ImGui}",
            "%{IncludeDir.glm}",

        }

        links{
            "GLFW",
            "Glad",
            "ImGui",
            "opengl32.lib"
        }

        defines{
		    "_CRT_SECURE_NO_WARNINGS"
	    }

            

        filter "system:windows"
            systemversion "latest"

            defines{
                "OG_PLATFORM_WINDOWS",
                "OG_STATIC_LINK",
                "OG_CORE",
                "GLFW_INCLUDE_NONE"
            }

        filter "configurations:Debug"
            defines "ORIGIN_DEBUG"
            symbols "on"

        filter "configurations:Release"
            defines "ORIGIN_RELEASE"
            optimize "on"

        filter "configurations:Dist"
            defines "ORIGIN_DIST"
            optimize "on"


    project "Sandbox"
        location "Sandbox"
        kind "ConsoleApp"
        staticruntime "on"
        language "C++"
        cppdialect "C++17"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

        files{
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
        }

        includedirs{
            "Origin/vendor/spdlog/include",
            "Origin/src",
            "%{IncludeDir.GLFW}",
            "Origin/vendor",
            "%{IncludeDir.glm}",

        }

        links{
            "Origin"
        }

        filter "system:windows"
            cppdialect "C++17"
            staticruntime "On"
            systemversion "latest"

            defines{
                "OG_PLATFORM_WINDOWS",
            }

        filter "configurations:Debug"
            defines "ORIGIN_DEBUG"
            symbols "On"

        filter "configurations:Release"
            defines "ORIGIN_RELEASE"
            optimize "On"

        filter "configurations:Dist"
            defines "ORIGIN_DIST"
            optimize "On"
