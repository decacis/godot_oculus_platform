# Godot Oculus Platform

An open-source implementation of the Oculus Platform SDK intended to be used with the Quest platform.

Please note you have to be familiarized with the documentation of the [Oculus Platform](https://developer.oculus.com/documentation/native/ps-platform-intro/), because there are many requirements to be able to use this asset.

Quick links:

- [Documentation](https://decacis.github.io/godot_oculus_platform/)
- [Oculus Platform Documentation](https://developer.oculus.com/documentation/native/ps-platform-intro/)

## Quick start

After you have everything setup, you can start interacting with the Oculus Platform with the singleton `GDOculusPlatform`. Here's an example of an [Entitlement Check](https://developer.oculus.com/documentation/native/ps-entitlement-check/):

```python
GDOP.initialize(false) # We have to initialize this singleton

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

You can read more in the [Godot Oculus Platform documentation](https://decacis.github.io/godot_oculus_platform/).

NOTE: The demo included in this repository won't work on its own. You still have to setup an app in the Oculus Dashboard, upload a release version and request all the required [Data Use Checkup](https://developer.oculus.com/resources/publish-data-use/) permissions to test, otherwise most fields will be empty/null. Also, it's missing the [OpenXR Loaders](https://github.com/GodotVR/godot_openxr_loaders).

## Building this asset

After cloning this repository, initialize the submodules by running:
```
git submodule update --init --recursive
```

Then run:
```
scons platform=PLATFORM_HERE target=TARGET_HERE generate_bindings=yes -j4
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

The result ARR will be placed in `tools/godotoculusplatform-android-plugin/godotoculusplatform-android-plugin/build/outputs/aar/godotoculusplatform-android-plugin-release.aar` and you'll find the `gdap` file in `demo/android/plugins`

## Using this asset

It is assumed that you already have a working project that deploys to the Oculus Quest. You also have to have proper [Data Use Checkup](https://developer.oculus.com/resources/publish-data-use/) permissions approved, depending on your needs. Take a look at the [getting started](https://decacis.github.io/godot_oculus_platform/getting-started/) from the documentation to see a list of requirements.

You can download the precompiled stable version from the [releases](https://github.com/decacis/godot_oculus_platform/releases) page or an in-development version from the [actions page](https://github.com/decacis/godot_oculus_platform/actions). In the case of the actions, look for an artifact with a name similar to `OculusPlatformSDK-51-for-godot-4.0.2-stable-0.0.1-alpha`.

**NOTE:** only in-development (artifact) versions are available at the moment.

If you instead decided to build this asset, you'll have to copy the files into place yourself.

### Copying the addon into place

You just have to copy the `demo/addons/godot_oculus_platform` folder to your project's addon folder.

### Copying the plugin into place

The AAR of the Android plugin is located in `tools/godotoculusplatform-android-plugin/godotoculusplatform-android-plugin/build/outputs/aar` copy the file there (`godotoculusplatform-android-plugin-release.aar`) to `android/plugins/godotoculusplatform` in your project.

Also copy `demo/android/plugins/godotoculusplatform-android-plugin.gdap` to `android/plugins` in your project.

**Make sure to enable the `Godot Oculus Platform Android Plugin` in your export template. Also, make sure to enable the `Godot Oculus Platform` plugin in your Project Settings.**

## License

Unless specified otherwise, sources in this repository are licensed under MIT, see `LICENSE` for more information.

Note that some vendor-specific (Meta Platform Technologies, LLC) components are licensed under separate license terms, which are listed in their corresponding folders.

## About this repository

This repository was created and maintained by Daniel Castellanos (decacis).
