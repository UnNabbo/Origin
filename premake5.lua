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

    include "Origin/vendor/GLFW"

    project "Origin"
        location "Origin"
        kind "SharedLib"
        language "C++"

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
            "%{IncludeDir.GLFW}"
        }

        links{
            "GLFW",
            "opengl32.lib"
        }


        filter "system:windows"
            cppdialect "C++17"
            staticruntime "On"
            systemversion "latest"

            defines{
                "OG_PLATFORM_WINDOWS",
                "OG_BUILD_DLL",
            }
            
            postbuildcommands{
                ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox/ ")
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


    project "Sandbox"
        location "Sandbox"
        kind "ConsoleApp"
        language "C++"

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
