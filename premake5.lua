workspace "BrickBreaker"
    configurations {"Debug", "Development", "Shipping"}
    architecture "x64"
    startproject "BrickBreaker"
    warnings "Extra"
    location ("BrickBreaker/")

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
       defines {"MAGNUS_DEBUG=1"}

    configuration "Development"
       defines {"MAGNUS_DEV=1"}
    
    configuration "Shipping"
       defines {"MAGNUS_SHIP=1"}

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
include "BrickBreaker.Build.lua"