#!/usr/bin/env python
import os
import sys

env = SConscript("godot-cpp/SConstruct")

# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["src/", "src/include/"])
sources = Glob("src/*.cpp")

if env["platform"] == "macos":
    if env["target"] != "template_debug":
        library = env.SharedLibrary(
            "demo/addons/godot_oculus_platform/bin/libgodotoculusplatformM",
            source=sources,
        )
    else:
        library = env.SharedLibrary(
            "demo/addons/godot_oculus_platform/bin/libgodotoculusplatformMD",
            source=sources,
        )

elif env["platform"] == "windows":
    if env["target"] != "template_debug":
        library = env.SharedLibrary(
            "demo/addons/godot_oculus_platform/bin/libgodotoculusplatformW",
            source=sources,
        )
    else:
        library = env.SharedLibrary(
            "demo/addons/godot_oculus_platform/bin/libgodotoculusplatformWD",
            source=sources,
        )
    
elif env["platform"] == "linux":
    if env["target"] != "template_debug":
        library = env.SharedLibrary(
            "demo/addons/godot_oculus_platform/bin/libgodotoculusplatformL",
            source=sources,
        )
    else:
        library = env.SharedLibrary(
            "demo/addons/godot_oculus_platform/bin/libgodotoculusplatformLD",
            source=sources,
        )
    
elif env["platform"] == "android":
    env.Append(LIBPATH=["demo/addons/godot_oculus_platform/bin/android/libs/arm64-v8a/"])
    env.Append(LIBS=["libovrplatformloader"])

    if env["target"] != "template_debug":
        library = env.SharedLibrary(
            "demo/addons/godot_oculus_platform/bin/libgodotoculusplatformA",
            source=sources,
        )
    else:
        # Unused
        library = env.SharedLibrary(
            "demo/addons/godot_oculus_platform/bin/libgodotoculusplatformAD",
            source=sources,
        )

Default(library)
