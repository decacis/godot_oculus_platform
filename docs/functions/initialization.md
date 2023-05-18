# Functions - Initialization

-----
/// admonition | Important
    type: danger

Before initializing the Oculus Platform, you must initialize the plugin like this:
``` gdscript linenums="1"
GDOP.initialize(false)
# or
GDOP.initialize()
```
With either `false` or `true` (no argument). Passing `false` will initialize the plugin with `quiet_mode=false` meaning that it will print unhandled Oculus Platform messages.
///

## initialize_android
//// admonition | initialize_android(app_id : `String`)
    type: abstract

Requests the Oculus Platform initialization.

**Returns:** A `bool` that is `true` if the platform was initialized correctly or `false` otherwise.

/// details | Example
    type: example
``` gdscript linenums="1"
var platform_initialized : bool = GDOculusPlatform.initialize_android("31415926535");
```
///
////

## initialize_android_async
//// admonition | initialize_android_async(app_id : `String`)
    type: abstract

Requests the Oculus Platform initialization asynchronously. This is the preferred way of initializing the platform.

**Returns:** A `GDOculusPlatformPromise` that will contain a true `bool` as a response if fulfilled. An error message will be available if rejected/couldn't initialize.

/// details | Example
    type: example
``` gdscript linenums="1"
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