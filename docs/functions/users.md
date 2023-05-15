# Functions - Users
------
## get_is_viewer_entitled
//// admonition | get_is_viewer_entitled()

Checks if the user that launched the app is entitled to the application/game.

**Returs:** A `GDOculusPlatformPromise` that will be fulfilled if the user is entitled. The promise will error if the user is not entitled or if the check fails.

/// details | Example
```
GDOculusPlatform.get_is_viewer_entitled()\
.then(func(_viewer_entitled_resp):
    print("User is entitled!")
)\
.error(func(_viewer_entitled_err):
    print("User is not entitled/error.")
)
```
///
////
---
## get_user
//// admonition | get_user(user_id : `String`)

Requests information about a single user by ID.

**Returs:** A `GDOculusPlatformPromise` that will contain a `Dictionary` as a response if fulfilled. An error message will be available if rejected.

Example response:
```
{
    "id": "31415926535",
    "oculus_id": "some_id",
    "display_name": "steve",
    "image_url": "https://example.org/some-image.png",
    "small_image_url": "https://example.org/some-smaller-image.png",
    "presence": {
        "presence_status": "ONLINE",
        "presence_deeplink_message": "",
        "presence_destination_api_name": "",
        "presence_lobby_session_id": "",
        "presence_match_session_id": "",
    }
}
```

/// details | Example
```
GDOculusPlatform.get_user("31415926535")\
.then(func(get_user_resp : Dictionary):
    print("User info: ", get_user_resp)
)\
.error(func(get_user_err):
    print("Unable to get user info: ", get_user_err)
)
```
///
////
---
## get_logged_in_user
//// admonition | get_logged_in_user()

Requests information about the user that launched the app.

**Returs:** A `GDOculusPlatformPromise` that will contain a `Dictionary` as a response if fulfilled. An error message will be available if rejected.

Example response:
```
{
    "id": "89793238462",
    "oculus_id": "some_other_id",
    "display_name": "steven",
    "image_url": "https://example.org/some-image.png",
    "small_image_url": "https://example.org/some-smaller-image.png",
    "presence": {
        "presence_status": "UNKNOWN",
        "presence_deeplink_message": "",
        "presence_destination_api_name": "",
        "presence_lobby_session_id": "",
        "presence_match_session_id": "",
    }
}
```
/// admonition | Note
    type: attention

Even though the `Dictionary` includes a `presence` key, it will not contain information other than "UNKNOWN" for the status. The current user should be 'online' for your application.
///

/// details | Example
```
GDOculusPlatform.get_logged_in_user()\
.then(func(get_user_resp : Dictionary):
    print("User info: ", get_user_resp)
)\
.error(func(get_user_err):
    print("Unable to get user info: ", get_user_err)
)
```
///
////
---
## get_user_proof
//// admonition | get_user_proof()

Requests a nonce used to verify the current user. Check the [official Oculus Platform documentation](https://developer.oculus.com/documentation/native/ps-ownership/) for more details.

**Returs:** A `GDOculusPlatformPromise` that will be fulfilled with the nonce as a `String` parameter. The function will error with a message if an error occured.

/// admonition | Note
    type: attention

A nonce is only valid once. After you use it to verify the user it becomes invalid.
///

/// details | Example
```
GDOculusPlatform.get_user_proof()\
.then(func(user_proof_resp : String):
    print("Nonce: ", user_proof_resp)
)\
.error(func(user_proof_err):
    print("Error getting user proof: ", user_proof_err)
)
```
///
////