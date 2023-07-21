workspace "LinuxWindow"
    configurations { "Debug", "Release" }

    -- Configure the "Debug" configuration
    filter "configurations:Debug"
    defines { "DEBUG" }
    symbols "On"

    -- Configure the "Release" configuration
    filter "configurations:Release"
    defines { "NDEBUG" }
    optimize "On"

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "LinuxWindow/vendor/Glad"

project "LinuxWindow"
    kind "ConsoleApp"
    language "C++"
    location "%{prj.basedir}/LinuxWindow"
    files { "**.h", "**.cpp" }

    links { "X11", "Glad", "GL" }
    includedirs { 
        "/usr/include", 
        "%{prj.location}/src",
        "%{prj.location}/vendor/Glad/include"
    }

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")