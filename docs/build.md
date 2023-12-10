# Build
If you choose to build the plugin yourself, first clone [the repository](https://github.com/decacis/godot_oculus_platform).

After that, initialize the submodules by running:
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

For android, you also have to add: `arch=arm64v8` and you only need to generate the `template_release` since `template_debug` is not used.

You can optionally add `-j<cores>` to use a set number of cores to build this asset. For example: `-j4`

The files will be placed in: `demo/addons/godot_oculus_platform/bin`

## Android Plugin
This plugin also requires an Android plugin to work with the Quest platform. To build the android plugin you have to navigate to `tools/godotoculusplatform-android-plugin` and run:

On windows:
```
.\gradlew.bat build
```

On linux:
```
./gradlew build
```

Finally, you have to copy the files into place:

| Source                              | Destination                |
|-------------------------------------|----------------------------|
| `demo/addons/godot_oculus_platform` | Your projet's addon folder |
| `tools/godotoculusplatform-android-plugin/godotoculusplatform-android-plugin/build/outputs/aar/godotoculusplatform-android-plugin-release.aar` | `addons/godot_oculus_platform/android_plugin` |
| `tools/godotoculusplatform-android-plugin/godotoculusplatform-android-plugin/build/outputs/aar/godotoculusplatform-android-plugin-debug.aar` | `addons/godot_oculus_platform/android_plugin` |

/// admonition | Note
    type: warning
Make sure to enable the `Godot Oculus Platform` plugin in your Project Settings.
///