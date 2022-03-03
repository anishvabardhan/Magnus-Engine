project "ProtoGame3D"
    location (ProjectFileDir)
    kind "WindowedApp"
    language "C++"
    cppdialect "C++17"

    targetdir (BinaryDir)
    objdir (IntermediateDir .. "/%{prj.name}")

    files
    {
        "ProtoGame3D/Code/**.h",
        "ProtoGame3D/Code/**.cpp",
        "ProtoGame3D/Data/Materials/**.xml",
        "ProtoGame3D/Data/Textures/**.png",
        "ProtoGame3D/Data/Shaders/**.shader"
    }

    includedirs
    {
        "Engine/Code/",
        "ProtoGame3D/Code/",
        "ProtoGame3D/Data/"
    }

    links 
    {
        "Engine",
        "d3d11.lib",
        "dxgi.lib",
        "d3dcompiler.lib"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Development"
        runtime "Release"
        optimize "on"
        symbols "on"

    filter "configurations:Shipping"
        runtime "Release"
        optimize "on"