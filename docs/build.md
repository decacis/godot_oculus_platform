# Build
After cloning this repository, initialize the submodules by running:
```
git submodule update --init --recursive
```

Then, follow the [Godot documentation](https://docs.godotengine.org/en/stable/tutorials/scripting/gdextension/gdextension_cpp_example.html#building-the-c-bindings) to generate `extension_api.json` for your Godot version, then go to `godot-cpp` directory and run:
```
scons platform=PLATFORM_HERE -j4 custom_api_file=PATH_TO_FILE_HERE
```
Replace `PLATFORM_HERE` with your platform and `PATH_TO_FILE_HERE` with the path to to `extension_api.json` file. The `-j4` is the number of cores to use to build - you can change it to speed up the process.

After that, go back to the root directory and run:

```
scons platform=PLATFORM_HERE target=TARGET_HERE
```

The required compilation parameters are:

- platform: `windows`, `macos`, `linux` or `android`
- target: `template_debug` or `template_release`

For android, you also have to add: `arch=arm64v8`

The files will be placed in: `demo/addons/godot_oculus_platform/bin`

### Android Plugin
This plugin also requires an Android plugin to work with the Quest platform. To build the android plugin you have to navigate to `tools/godotoculusplatform-android-plugin` and run:

On windows:
```
gradlew.bat build
```

On linux:
```
./gradlew build
```