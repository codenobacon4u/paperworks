workspace "Paperworks"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Paperworks/vendor/GLFW/include"
IncludeDir["GLAD"] = "Paperworks/vendor/GLAD/include"
IncludeDir["ImGui"] = "Paperworks/vendor/ImGui"
IncludeDir["glm"] = "Paperworks/vendor/glm"

group "Dependencies"
	include "Paperworks/vendor/GLFW"
	include "Paperworks/vendor/GLAD"
	include "Paperworks/vendor/ImGui"
group ""

project "Paperworks"
	location "Paperworks"
	kind "SharedLib"
	language"C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pwpch.h"
	pchsource "Paperworks/src/pwpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.ImGui}"
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib" 
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"PW_BUILD_DLL",
			"PW_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "PW_DEBUG"
		defines "PW_ASSERT_ENABLE"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "PW_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "PW_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language"C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"Paperworks/vendor/spdlog/include",
		"Paperworks/src",
		"Paperworks/vendor"
		"%%{IncludeDir.glm}"
	}

	links
	{
		"Paperworks"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"PW_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "PW_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "PW_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "PW_DIST"
		runtime "Release"
		optimize "On"