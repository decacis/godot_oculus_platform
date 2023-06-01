# Functions - Application
Related Oculus Platform documentation:

- [https://developer.oculus.com/documentation/native/ps-deep-linking/](https://developer.oculus.com/documentation/native/ps-deep-linking/)
- [https://developer.oculus.com/documentation/native/ps-events/](https://developer.oculus.com/documentation/native/ps-events/)

------
## Signals

### app_launch_intent_changed
//// admonition | About
    type: abstract
This signal will be emitted when the launch intent changes. For example, if another app launched this app, and this app is already loaded in the background.

The signal will contain a `String` with the type of the intent.

You should call [application_get_launch_details](#application_get_launch_details) to get more information about the launch.
////

------
## application_get_version
//// admonition | application_get_version()
    type: abstract

Returns information about the current application.

**Returns:** A `GDOculusPlatformPromise` that will contain a `Dictionary` with information about the current app version if fulfilled. The promise will error if the request couldn't be completed.

Example response:
``` json linenums="1"
{
    "current_code": 5,
    "latest_code": 6,
    "current_name": "v5-alpha",
    "latest_name": "v6-beta"
}
```

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.application_get_version()\
.then(func(app_version : Dictionary):
    if app_version.current_code != app_version.latest_code:
        print("There is a new version of this app, please update!")
)\
.error(func(app_version_err):
    print("Unable to retrieve app version info: ", app_version_err)
)
```
///
////

## application_launch_other_app
//// admonition | application_launch_other_app(app_id : `String`, deeplink_options : `Dictionary`)
    type: abstract

Sends a request to the Oculus Platform to launch another app. The `app_id` argument is the ID of the other app you wish to launch. You can pass an empty `Dictionary` for `deeplink_options` and an example of the options is shown bellow.

**Returns:** A `GDOculusPlatformPromise` that will contain a `String` with information about the request if fulfilled. The promise will error if the request couldn't be completed.

Example of `deeplink_options`:
``` json linenums="1"
{
    "deeplink_message": "FROM_APP1_TO_APP2_LOBBY",
    "destination_api_name": "MY_COOL_DESTINATION",
    "lobby_session_id": "51254821626844",
    "match_session_id": "92848281510484"
}
```

If you decide to include `deeplink_options`, the only required field is `deeplink_message`. The other fields can be used to interact with other APIs, but they are not required.

/// details | Example
    type: example
``` gdscript linenums="1"
var deeplink_options : Dictionary = {
    "deeplink_message": "GO_TO_MAIN_LOBBY"
}

GDOculusPlatform.application_launch_other_app("50125468232421", deeplink_options)\
.then(func(launch_result : String):
    print("Launch result: ", launch_result)
)\
.error(func(launch_err):
    print("Unable to launch other app: ", launch_err)
)
```
///
////

## application_get_launch_details
//// admonition | application_get_launch_details()
    type: abstract

Used to retrieve information about the launch. Can be used to deep link applications and know if another app requested the launch, among other things.

**Returns:** A `GDOculusPlatformPromise` that will contain a `Dictionary` with information about the app's launch. The promise will error if the request couldn't be completed.

Example response:
``` json linenums="1"
{
    "deeplink_message": "GO_TO_MAIN_LOBBY",
    "destination_api_name": "",
    "lobby_session_id": "",
    "match_session_id": "",
    "tracking_id": "574371645284520",
    "launch_source": "events",
    "launch_type": "DEEPLINK",
    "users": {
        "data": [
            {
                "id": "2384626433832795",
                "oculus_id": "some_id",
                "display_name": "Steve",
                "image_url": "https://example.org/some-image.png",
                "small_image_url": "",
                "presence": {
                    "presence_status": "ONLINE",
                    "presence_deeplink_message": "",
                    "presence_destination_api_name": "",
                    "presence_lobby_session_id": "",
                    "presence_match_session_id": "",
                }
            }
        ],
        "next_page_url": ""
    }
}
```

- `launch_type` can be: `DEEPLINK`, `COORDINATED`, `INVITE`, `NORMAL` or `UNKNOWN`.
- `launch_source` can be used to distinguish where the deeplink came from. For example, a `DEEPLINK` launch type could be coming from events or rich presence.
- `users` is a `Dictionary` that could be populated with other users the current user may want to be with.

///// admonition | Note
    type: warning

The `Dictionary` of the `users` key can theoretically contain a URL as the value of the `next_page_url` key, but in all of our tests with 1000+ entries, it has not happened yet. Nevertheless, you should check if the `String` is empty, and if it's not, make a HTTP GET request to get the rest of the values.

Also, if you happen to get this URL, please report it on the [issues page](https://github.com/decacis/godot_oculus_platform/issues) in GitHub, so we are aware that it can happen and update the docs.
/////

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.application_get_launch_details()\
.then(func(launch_details : Dictionary):
    
    if launch_details.launch_type == "DEEPLINK":

        match launch_details.deeplink_message:
            "GO_TO_MAIN_LOBBY":
                _handle_dl_main_lobby()
            "GO_TO_STORE":
                _handle_dl_store()
    
)\
.error(func(launch_details_err):
    print("Unable to get launch details: ", launch_details_err)
)
```
///
////
