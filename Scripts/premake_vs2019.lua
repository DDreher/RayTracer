require "premake_modules"

local ProjectName = "RayTracer"

function AddSourceFiles(DirectoryPath)
    files
    { 
        ("../" .. DirectoryPath .. "/**.h"),
		("../" .. DirectoryPath .. "/**.hpp"),
        ("../" .. DirectoryPath .. "/**.cpp"),
        ("../" .. DirectoryPath .. "/**.inl"),
		("../" .. DirectoryPath .. "/**.c"),
		("../" .. DirectoryPath .. "/**.cs")
    }
end

function IncludeModule(ModuleNames)
	for Idx, ModuleName in pairs(ModuleNames) do
		includedirs { ("../" .. ProjectName .. "/Source/" .. ModuleName .. "/Public/") }
	end
end

workspace (ProjectName)
	location "../"
	basedir "../"
	language "C++"
	configurations {"Debug", "ReleaseWithDebugInfo", "Release"}
	platforms {"x64"}
	warnings "default"
	characterset ("MBCS")
	rtti "Off"
	toolset "v142"
	cppdialect "C++latest"
	--flags {"FatalWarnings"}
	
	filter { "configurations:Debug" }
		runtime "Debug"
		defines { "_DEBUG" }
		symbols "On"
		optimize "Off"
		debugdir "$(SolutionDir)"

	filter { "configurations:ReleaseWithDebugInfo" }
		runtime "Release"
		defines { "_RELEASE", "NDEBUG" }
		symbols "On"
		optimize "Full"
		debugdir "$(SolutionDir)"
		
	filter { "configurations:Release" }
	 	runtime "Release"
		defines { "_RELEASE", "NDEBUG" }
	 	symbols "Off"
	 	optimize "Full"

project (ProjectName)
	location ("../" .. ProjectName)
	targetdir ("../Build/" .. ProjectName .. "$(Configuration)_$(Platform)")
	objdir "!../Build/Intermediate/$(ProjectName)_$(Configuration)_$(Platform)"
	kind "ConsoleApp"

	AddSourceFiles(ProjectName)
	includedirs { "$(ProjectDir)" }
	IncludeModule {"Core"}
	IncludeModule {"Renderer"}
	
	pchheader ("Core.h")
	pchsource ("../" .. ProjectName .. "/Source/Core/Private/Core.cpp")
	forceincludes  { "Core.h" }

	disablewarnings 
	{
        "4100", -- unreferenced formal paramter
		"4189"  -- local variable initalized but not referenced
	}

	AddSTB()

	filter "files:**/ThirdParty/**.*"
		flags "NoPCH"
		disablewarnings { "4100" }
