# Getting started
There are several steps to follow before using this asset. We assume you already have an app/game even if you have not published to the AppLab or the Quest Store.

## Create a release version
You have to create release version of your app (i.e. with Deploy With Debug disabled) to upload it to AppLab of the Quest Store. This app doesn't have to be the final version of your app, but it should be signed with a release keystore.

The [Exporting for Google Play Store](https://docs.godotengine.org/en/stable/tutorials/export/exporting_for_android.html#exporting-for-google-play-store) section on the Godot documentation explains this process (it's the same for the Quest Store).

## Creating an App Page
First you have to create a page for your app. You can read more about this process in the official [Oculus Platform documentation](https://developer.oculus.com/resources/publish-create-app/), but essentially you have to:

- Log on to the [Developer Dashboard](https://developer.oculus.com/manage/).
- Click Create New App.
- Enter the name of your app. The name is permanent and cannot be changed.
- From Platform, select Meta Quest (App Lab).

## Upload your first build
You have to upload a "first version" of your app, even if it's not complete or even beginning development. This allows oculus to associate the app's package id (com.example.app for example) to the App Page you created before.

We recommend using the [Meta Quest Developer Hub (MQDH)](https://developer.oculus.com/meta-quest-developer-hub/) to manage your apps, release channels and versions, though there are [other ways](https://developer.oculus.com/resources/publish-uploading-mobile/#upload-meta-quest-builds) of uploading a build.

Assuming you are using the MQDH, you have to:

- Go to "App Distribution".
- Select your app.
- Click the upload button on the desired release channel. We recommend you upload your first build to the "ALPHA" release channel.
- Select the APK of your app.
- Finish the upload process.

## Request Data Use Checkup permissions
Depending on what functions you use, you have to request different Data Use Checkup permissions. You can read more about this process [here](https://developer.oculus.com/resources/publish-data-use/).

As long as you are in development (haven't published your app yet), you can request all the permissions you need and they will be approved automatically to ease development. Once you want to publish your app, you will have to re-request these permissions.

## Add this asset to your project
You can download the precompiled stable version from the [releases](https://github.com/decacis/godot_oculus_platform/releases) page or an in-development version from the [actions page](https://github.com/decacis/godot_oculus_platform/actions). In the case of the actions, look for an artifact with a name similar to `OculusPlatformSDK-51-for-godot-4.0.2-stable-0.0.1-alpha`.

Finally, enable the `Godot Oculus Platform Android Plugin` in your export template and enable the `Godot Oculus Platform` plugin in your Project Settings.

## Using this asset
You can take a look at the [examples](/godot_oculus_platform/examples/) to get an idea of how to interact with the Oculus Platform.

A concept we use is the use of promises or more specifically `GDOculusPlatformPromise`s. These promises basically help you perform actions in an asynchronous manner. Take a look at the following example:

```
print("Godot")

GDOP.initialize()

GDOculusPlatform.initialize_android_async("314159265358979")\
.then(func(_initialization_resp):
    print("Oculus")
)

print("Platform")
```
This will print:

```
Godot
Platform
Oculus
```

Since almost all functions in this platform are asynchronous, they don't block code execution allowing you to do other stuff while you wait for a response from the Oculus Platform.