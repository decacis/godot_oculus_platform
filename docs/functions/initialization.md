# Functions - Initialization

-----

## is_platform_initialized
//// admonition | is_platform_initialized()
    type: abstract

**Returns:** A `bool` that is `true` if the platform is already initialized and `false` otherwise.

/// details | Example
    type: example
``` gdscript linenums="1"
if not GDOculusPlatform.is_platform_initialized():
    # Try to initialize the platform synchronously.
    var platform_initialized : bool = GDOculusPlatform.initialize_android("31415926535")

    if not platform_initialized:
        print("Unable to initialize Oculus Platform")
```
///
////

## initialize_android
//// admonition | initialize_android(app_id : `String`, options : `Dictionary`)
    type: abstract

Requests the Oculus Platform initialization synchronously. Keep in mind that this function will block the main loop until this function returns.

**Returns:** A `bool` that is `true` if the platform was initialized correctly or `false` otherwise.

Options (optional):

| Key                    |   Value type  | Description                                                        |
|------------------------|:-------------:|--------------------------------------------------------------------|
| disable_p2p_networking |     bool      | Disables/enables the initialization of the WebRTC networking stack, only used for VoIP & Networking (both deprecated). |

/// details | Example
    type: example
``` gdscript linenums="1"
var platform_initialized : bool = GDOculusPlatform.initialize_android("31415926535")

# Other example:
var options : Dictionary = {
    "disable_p2p_networking": true
}
var platform_initialized : bool = GDOculusPlatform.initialize_android("31415926535", options)
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
