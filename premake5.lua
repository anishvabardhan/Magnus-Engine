workspace "ProtoGame3D"
    configurations {"Debug", "Development", "Shipping"}
    architecture "x64"
    startproject "ProtoGame3D"
    warnings "Extra"
    location ("ProtoGame3D/")

    disablewarnings
    {
    	"4100",
        "4201"
    }

    defines
    {
      "OPENGL_API=0",
      "DX11_API=1"
    }

    configuration "Debug"
       defines {"MAGNUS_DEBUG"}

    configuration "Development"
       defines {"MAGNUS_DEV"}
    
    configuration "Shipping"
       defines {"MAGNUS_SHIP"}

BinaryDir="%{wks.location}/Run/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/"
IntermediateDir="%{wks.location}/Temporary/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/"
ProjectFileDir="%{wks.location}/Temporary/" .. "ProjectFiles/"
EngineSrcDir="Engine/Code/"

    flags
    {
    	"FatalWarnings"
    }

    filter "action:VS*" -- MSVC does not update __cplusplus macro by default
	    	buildoptions { "/Zc:__cplusplus" }

include "Engine.Build.lua"
include "ProtoGame3D.Build.lua"