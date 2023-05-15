# Functions - Initialization
------
## initialize_android
//// admonition | initialize_android(app_id : `String`)

Checks if the user that launched the app is entitled to the application/game.

**Returs:** A `bool` that is `true` if the platform was initialized correctly or `false` otherwise.

/// details | Example
```
var platform_initialized : bool = GDOculusPlatform.initialize_android("31415926535");
```
///
////
---
## initialize_android_async
//// admonition | initialize_android_async(app_id : `String`)

Requests the platform initialization asynchronously. This is the preferred way of initializing the platform.

**Returs:** A `GDOculusPlatformPromise` that will contain a true `bool` as a response if fulfilled. An error message will be available if rejected/couldn't initialize.

/// details | Example
```
GDOculusPlatform.initialize_android_async("31415926535")\
.then(func(platform_initialized : bool):
    print("Platform initialized!")
)\
.error(func(platform_initialized_err):
    print("Platform NOT initialized. Error message: ", platform_initialized_err)
)
```
///
////