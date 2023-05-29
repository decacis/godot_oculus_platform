# Godot Oculus Platform
An open-source implementation of the Oculus Platform SDK intended to be used with the Quest platform.
See the [download](https://decacis.github.io/godot_oculus_platform/download/) page of the documentation for a list of supported Godot Engine and Oculus Platform SDK versions.

While you can use this plugin in the editor to get code suggestions, it **only works with the Meta Quest**, not PCVR. If you plan to develop for both the Quest and PCVR, you should add a platform check and only use this plugin when the platform is Android.

**NOTE:** This project is still a work in progress, you should expect usage API changes in the future.

Quick links:

- [Downloads](#getting-this-asset)
- [Documentation](https://decacis.github.io/godot_oculus_platform/)
- [Oculus Platform Documentation](https://developer.oculus.com/documentation/native/ps-platform-intro/)

## Quick start
After you have everything [setup](https://decacis.github.io/godot_oculus_platform/getting-started/), you can start interacting with the Oculus Platform with the singleton `GDOculusPlatform`. Here's an example of an [Entitlement Check](https://developer.oculus.com/documentation/native/ps-entitlement-check/):

```python
GDOP.initialize(false) # We have to initialize this plugin first

# Initializing android platform with the APP_ID as a parameter
GDOculusPlatform.initialize_android_async("314159265358979")\
.then(func(_initialization_resp):
    print("Oculus Platform initialized!")
    
    # Is the user entitled to this app?
    GDOculusPlatform.get_is_viewer_entitled()\
    .then(func(_is_viewer_entitled_resp):
        print("User is entitled!")
        
    )\
    .error(func(is_viewer_entitled_err):
        print("User not entitled/error! ", is_viewer_entitled_err)
    )
    
)\
.error(func(initialization_err):
    print("Oculus Platform initialization error: ", initialization_err)
)
```

We use a promise-based approach for every request that is asynchronous. The `then` `Callable` will only be called if the request was fulfilled (i.e. successful) and the `error` `Callable` will be called if there was an error with the request.

**NOTE:** The demo included in this repository won't work on its own. You still have to setup an app in the Oculus Dashboard, upload a release version and request all the required [Data Use Checkup](https://developer.oculus.com/resources/publish-data-use/) permissions to test, otherwise most fields will be empty/null. Also, it's missing the [OpenXR Loaders](https://github.com/GodotVR/godot_openxr_loaders).

## Getting this asset
You can find all the releases in the [GitHub releases page](https://github.com/decacis/godot_oculus_platform/releases).

You can also use the [interactive version list](https://decacis.github.io/godot_oculus_platform/download/) in the documentation website to quickly find the version you need.

In-development precompiled versions can be found in the [GitHub actions page](https://github.com/decacis/godot_oculus_platform/actions?query=branch%3Amain).

## Building this asset
After cloning this repository, initialize the submodules by running:
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

### Android Plugin
This addon also requires an Android plugin to work with the Quest platform. To build this plugin you have to navigate to `tools/godotoculusplatform-android-plugin` and run:

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

**Make sure to enable the `Godot Oculus Platform Android Plugin` in your export template. Also, make sure to enable the `Godot Oculus Platform` plugin in your Project Settings.**

## License
Unless specified otherwise, sources in this repository are licensed under MIT, see `LICENSE` for more information.

Note that some vendor-specific components are licensed under separate license terms, which are listed in their corresponding folders.

## About this repository
This repository was created and maintained by Daniel Castellanos (decacis).

Inspiration and code examples were taken from the following projects:

- [Godot XR Reference plugin by Bastiaan "Mux213" Olij](https://github.com/GodotVR/godot_xr_reference)
- [FMOD for Godot by Alessandro Famà](https://github.com/alessandrofama/fmod-for-godot)
- [GDMP by j20001970](https://github.com/j20001970/GDMP)