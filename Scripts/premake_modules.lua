function AddSTB()  
    defines { "MODULE_STB" }
    includedirs {
        "$(SolutionDir)/ThirdParty/stb/include/",
    } 

    filter {}
end

function AddSpdlog()  
    defines { "MODULE_SPDLOG" }
    includedirs {
        "$(SolutionDir)/ThirdParty/spdlog/include/",
    } 
        
    filter {}
end

function AddAssimp()  
    defines { "MODULE_ASSIMP" }
	includedirs "$(SolutionDir)/ThirdParty/Assimp/include/"
    libdirs	"$(SolutionDir)/ThirdParty/Assimp/lib/x64"
    
    filter  "configurations:Debug"
        postbuildcommands
        { 
            "{COPY} \"$(SolutionDir)ThirdParty\\Assimp\\bin\\%{cfg.platform}\\assimp-vc143-mtd.dll\" \"$(OutDir)\"",
            "{COPY} \"$(SolutionDir)ThirdParty\\Assimp\\bin\\%{cfg.platform}\\assimp-vc143-mtd.pdb\" \"$(OutDir)\""
        }
        links
        {
            "assimp-vc143-mtd.lib"
        }

    filter  "configurations:ReleaseWithDebugInfo"
        postbuildcommands
        { 
            "{COPY} \"$(SolutionDir)ThirdParty\\Assimp\\bin\\%{cfg.platform}\\assimp-vc143-mtd.dll\" \"$(OutDir)\"",
            "{COPY} \"$(SolutionDir)ThirdParty\\Assimp\\bin\\%{cfg.platform}\\assimp-vc143-mtd.pdb\" \"$(OutDir)\""
        }
        links
        {
            "assimp-vc143-mtd.lib"
        }

    filter  "configurations:Release"
        postbuildcommands
        { 
            "{COPY} \"$(SolutionDir)ThirdParty\\Assimp\\bin\\%{cfg.platform}\\assimp-vc143-mt.dll\" \"$(OutDir)\""
        }
        links
        {
            "assimp-vc143-mt.lib"
        }
end