workspace "Paperworks"
architecture "x64"
startproject "DrawingBoard"

configurations {
    "Debug",
    "Release",
    "Dist"
}

flags {
    "MultiProcessorCompile"
}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Paperworks/vendor/GLFW/include"
IncludeDir["GLAD"] = "Paperworks/vendor/GLAD/include"
IncludeDir["ImGui"] = "Paperworks/vendor/ImGui"
IncludeDir["glm"] = "Paperworks/vendor/glm"
IncludeDir["spdlog"] = "Paperworks/vendor/spdlog/include"
IncludeDir["stb_image"] = "Paperworks/vendor/stb_image"
IncludeDir["Vulkan"] = "C:/VulkanSDK/1.1.114.0/Include"

group "Dependencies"
include "Paperworks/vendor/GLFW"
include "Paperworks/vendor/GLAD"
include "Paperworks/vendor/ImGui"
group ""

project "Paperworks"
location "Paperworks"
kind "StaticLib"
language "C++"
cppdialect "C++17"
staticruntime "on"

targetdir("bin/" .. outputdir .. "/%{prj.name}")
objdir("bin-int/" .. outputdir .. "/%{prj.name}")

pchheader "pwpch.h"
pchsource "Paperworks/src/pwpch.cpp"

files {
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.cpp",
    "%{prj.name}/vendor/stb_image/**.h",
    "%{prj.name}/vendor/stb_image/**.cpp",
    "%{prj.name}/vendor/glm/glm/**.hpp",
    "%{prj.name}/vendor/glm/glm/**.inl"
}


defines {
    "_CRT_SECURE_NO_WARNINGS"
}

includedirs {
    "%{prj.name}/src",
    "%{IncludeDir.spdlog}",
    "%{IncludeDir.GLFW}",
    "%{IncludeDir.GLAD}",
    "%{IncludeDir.ImGui}",
    "%{IncludeDir.glm}",
    "%{IncludeDir.stb_image}",
	"%{IncludeDir.Vulkan}",
}

libdirs {
	"C:/VulkanSDK/1.1.114.0/Lib"
}

links {
    "GLFW",
    "GLAD",
    "ImGui",
	"opengl32.lib",
	"vulkan-1.lib"
}

filter "system:linux"
pic "on"

links {
    "Xrandr",
    "Xi",
    "GLEW",
    "GLU",
    "GL",
    "X11"
}

defines {
    "PW_BUILD_DLL",
    "GLFW_INCLUDE_NONE"
}

filter "system:windows"
systemversion "latest"
toolset "v142"

links {
    "opengl32.lib"
}

defines {
    "PW_BUILD_DLL",
    "GLFW_INCLUDE_NONE"
}

filter "configurations:Debug"
defines "PW_DEBUG"
runtime "Debug"
symbols "on"

filter "configurations:Release"
defines "PW_RELEASE"
runtime "Release"
optimize "on"

filter "configurations:Dist"
defines "PW_DIST"
runtime "Release"
optimize "on"

project "Sandbox"
location "Sandbox"
kind "ConsoleApp"
language "C++"
cppdialect "C++17"
staticruntime "on"

targetdir("bin/" .. outputdir .. "/%{prj.name}")
objdir("bin-int/" .. outputdir .. "/%{prj.name}")

files {
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.cpp"
}

includedirs {
    "Paperworks/src",
    "Paperworks/vendor",
    "%{IncludeDir.glm}",
    "%{IncludeDir.spdlog}"
}

links {
    "Paperworks"
}

filter "system:linux"

links {
    "GLFW",
    "GLAD",
    "ImGui",
    "GLEW",
    "GLU",
    "GL",
    "X11",
    "dl",
    "pthread"
}

filter "system:windows"
systemversion "latest"
toolset "v142"

filter "configurations:Debug"
defines "PW_DEBUG"
runtime "Debug"
symbols "on"

filter "configurations:Release"
defines "PW_RELEASE"
runtime "Release"
optimize "on"

filter "configurations:Dist"
defines "PW_DIST"
runtime "Release"
optimize "on"

project "DrawingBoard"
location "DrawingBoard"
kind "ConsoleApp"
language "C++"
cppdialect "C++17"
staticruntime "on"

targetdir("bin/" .. outputdir .. "/%{prj.name}")
objdir("bin-int/" .. outputdir .. "/%{prj.name}")

files {
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.cpp"
}

includedirs {
    "Paperworks/src",
    "Paperworks/vendor",
    "%{IncludeDir.glm}",
    "%{IncludeDir.spdlog}"
}

links {
    "Paperworks"
}

filter "system:linux"

links {
    "GLFW",
    "GLAD",
    "ImGui",
    "GLEW",
    "GLU",
    "GL",
    "X11",
    "dl",
    "pthread"
}

filter "system:windows"
systemversion "latest"
toolset "v142"

filter "configurations:Debug"
defines "PW_DEBUG"
runtime "Debug"
symbols "on"

filter "configurations:Release"
defines "PW_RELEASE"
runtime "Release"
optimize "on"

filter "configurations:Dist"
defines "PW_DIST"
runtime "Release"
optimize "on"
