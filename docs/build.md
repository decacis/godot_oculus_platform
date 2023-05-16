# Build
After cloning [the repository](https://github.com/decacis/godot_oculus_platform), initialize the submodules by running:
```
git submodule update --init --recursive
```

Then run:
```
scons platform=PLATFORM_HERE target=TARGET_HERE
```

The required compilation parameters are:

- platform: `windows`, `macos`, `linux` or `android`
- target: `template_debug` or `template_release`

For android, you also have to add: `arch=arm64v8`

You can optionally add `-j<cores>` to use a set number of cores to build this asset. For example: `-j4`

The files will be placed in: `demo/addons/godot_oculus_platform/bin`

## Android Plugin
This plugin also requires an Android plugin to work with the Quest platform. To build the android plugin you have to navigate to `tools/godotoculusplatform-android-plugin` and run:

On windows:
```
gradlew.bat build
```

On linux:
```
./gradlew build
```

Finally, you have to copy the files into place:

| Source                              | Destination                |
|-------------------------------------|----------------------------|
| `demo/addons/godot_oculus_platform` | Your projet's addon folder |
| `tools/godotoculusplatform-android-plugin/godotoculusplatform-android-plugin/build/outputs/aar/godotoculusplatform-android-plugin-release.aar` | `android/plugins/godotoculusplatform` |
| `demo/android/plugins/godotoculusplatform-android-plugin.gdap` | `android/plugins` |

/// admonition | Note
    type: warning
Make sure to enable the `Godot Oculus Platform Android Plugin` in your export template. Also, make sure to enable the `Godot Oculus Platform` plugin in your Project Settings.
///