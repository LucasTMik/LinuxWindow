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

project "LinuxWindow"
    kind "ConsoleApp"
    language "C++"
    location "%{prj.basedir}/LinuxWindow"
    files { "**.h", "**.cpp" }

    links { "X11" }
    includedirs { "/usr/include", "%{prj.location}/src" }

    targetdir "%{prj.location}/bin"
    objdir "%{prj.location}/bin-int"
