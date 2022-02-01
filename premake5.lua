workspace "Origin"
    architecture "x64"
    startproject "Sandbox"


    configurations{
        "Debug",
        "Release",
        "Dist"
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    project "Origin"
        location "Origin"
        kind "SharedLib"
        language "C++"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

        files{
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
        }

        includedirs{
            "%{prj.name}/vendor/spdlog/include",
            "Origin/src"
        }

        filter "system:windows"
            cppdialect "C++17"
            staticruntime "On"
            systemversion "latest"

            defines{
                "ORIGIN_PLATFORM_WINDOWS",
                "ORIGIN_BUILD_DLL",
            }
            
            postbuildcommands{
                ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sanbox/ ")
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
            "Origin/src"
        }

        links{
            "Origin"
        }

        filter "system:windows"
            cppdialect "C++17"
            staticruntime "On"
            systemversion "latest"

            defines{
                "ORIGIN_PLATFORM_WINDOWS",
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
