# Functions - User
Related Oculus Platform documentation:

- [https://developer.oculus.com/documentation/native/ps-presence/](https://developer.oculus.com/documentation/native/ps-presence/)
- [https://developer.oculus.com/documentation/native/ps-entitlement-check/](https://developer.oculus.com/documentation/native/ps-entitlement-check/)
- [https://developer.oculus.com/documentation/native/ps-blockingsdk/](https://developer.oculus.com/documentation/native/ps-blockingsdk/)

------
## user_get_logged_in_user_id
//// admonition | user_get_logged_in_user_id()
    type: abstract

Requests the logged-in user ID.

**Returns:** A `String` with the user ID. The `String` will be "0" if there's no ID.

/// details | Example
    type: example
``` gdscript linenums="1"
var user_id : String = user_get_logged_in_user_id()
# user_id = "3141592653589793" for example
```
///
////

## user_get_logged_in_user_locale
//// admonition | user_get_logged_in_user_locale()
    type: abstract

Requests the logged-in user's locale'.

**Returns:** A `String` with the user's locale that **SHOULD** conform to BCP47: [https://tools.ietf.org/html/bcp47](https://tools.ietf.org/html/bcp47) but in reality the API replaces "-" with "_"

/// details | Example
    type: example
``` gdscript linenums="1"
var user_locale : String = user_get_logged_in_user_locale()
# user_locale = "en_US" for example
```
///
////

## user_get_is_viewer_entitled
//// admonition | user_get_is_viewer_entitled()
    type: abstract

Checks if the user that launched the app is entitled to the application/game.

**Returns:** A `GDOculusPlatformPromise` that will be fulfilled if the user is entitled. The promise will error if the user is not entitled or if the check fails.

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.user_get_is_viewer_entitled()\
.then(func(_viewer_entitled_resp):
    print("User is entitled!")
)\
.error(func(_viewer_entitled_err):
    print("User is not entitled/error.")
)
```
///
////

## user_get_user
//// admonition | user_get_user(user_id : `String`)
    type: abstract

Requests information about a single user by ID.

**Returns:** A `GDOculusPlatformPromise` that will contain a `Dictionary` as a response if fulfilled. An error message will be available if rejected.

Example response:
``` json linenums="1"
{
    "id": "3141592653589793",
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
    type: example
``` gdscript linenums="1"
GDOculusPlatform.user_get_user("31415926535")\
.then(func(get_user_resp : Dictionary):
    print("User info: ", get_user_resp)
)\
.error(func(get_user_err):
    print("Unable to get user info: ", get_user_err)
)
```
///
////

## user_get_logged_in_user
//// admonition | user_get_logged_in_user()
    type: abstract

Requests information about the user that launched the app.

**Returns:** A `GDOculusPlatformPromise` that will contain a `Dictionary` as a response if fulfilled. An error message will be available if rejected.

Example response:
``` json linenums="1"
{
    "id": "2384626433832795",
    "oculus_id": "some_other_id",
    "display_name": "steven",
    "image_url": "https://example.org/some-image.png",
    "small_image_url": "",
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
    type: warning

Even though the `Dictionary` includes a `presence` key, it will not contain information other than "UNKNOWN" for the status. The current user should be 'online' for your application.
///

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.user_get_logged_in_user()\
.then(func(get_user_resp : Dictionary):
    print("User info: ", get_user_resp)
)\
.error(func(get_user_err):
    print("Unable to get user info: ", get_user_err)
)
```
///
////

## user_get_user_proof
//// admonition | user_get_user_proof()
    type: abstract

Requests a nonce used to verify the current user. Check the [official Oculus Platform documentation](https://developer.oculus.com/documentation/native/ps-ownership/) for more details.

**Returns:** A `GDOculusPlatformPromise` that will be fulfilled with the nonce as a `String` parameter. The function will error with a message if an error occured.

/// admonition | Note
    type: warning

A nonce is only valid once. After you use it to verify the user it becomes invalid.
///

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.user_get_user_proof()\
.then(func(user_proof_resp : String):
    print("Nonce: ", user_proof_resp)
)\
.error(func(user_proof_err):
    print("Error getting user proof: ", user_proof_err)
)
```
///
////

## user_get_user_access_token
//// admonition | user_get_user_access_token()
    type: abstract

Requests a token of the current user suitable to make REST calls against graph.oculus.com

**Returns:** A `GDOculusPlatformPromise` that will be fulfilled with the access token as a `String` parameter. The function will error with a message if an error occured.

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.user_get_user_access_token()\
.then(func(user_access_token : String):
    print("Access token: ", user_access_token)
)\
.error(func(user_access_token_err):
    print("Error getting user proof: ", user_access_token_err)
)
```
///
////

## user_get_blocked_users
//// admonition | user_get_blocked_users()
    type: abstract

Requests the user IDs of users blocked by the current user.

**Returns:** A `GDOculusPlatformPromise` that will contain an `Array` of user IDs as `String`s. The function will error with a message if an error occured.

Example response:
``` json linenums="1"
[
    "3141592653589793",
    "2384626433832795",
    "1288419716045741"
]
```

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.user_get_blocked_users()\
.then(func(blocked_users : Array):
    for user_id in blocked_users:
        print("Blocked user ID: ", user_id)
)\
.error(func(blocked_users_err):
    print("Error getting blocked users: ", blocked_users_err)
)
```
///
////

## user_get_logged_in_user_friends
//// admonition | user_get_logged_in_user_friends()
    type: abstract

Requests the user IDs of the current user's friends.

**Returns:** A `GDOculusPlatformPromise` will contain an `Array` of `Dictionaries` with information about each friend. Same format as the `Dictionary` returned by [user_get_user](#user_get_user). The function will error with a message if an error occured.

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.user_get_logged_in_user_friends()\
.then(func(friends : Array):
    for friend_info in friends:
        print("Friend ID: ", friend_info.id)
        print("Friend image: ", friend_info.image_url)
)\
.error(func(friends_err):
    print("Error getting friends: ", friends_err)
)
```
///
////

## user_get_org_scoped_id
//// admonition | user_get_org_scoped_id(user_id : `String`)
    type: abstract

Requests an ID which is unique per org. Allows different apps within the same org to identify the user.

**Returns:** A `GDOculusPlatformPromise` will contain the given user's scoped org ID as a `String`. The function will error with a message if an error occured.

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.user_get_org_scoped_id("31415926535")\
.then(func(org_scoped_id : String):
    print("Org scoped ID: ", org_scoped_id)
)\
.error(func(org_scoped_id_err):
    print("Error getting org scoped ID: ", org_scoped_id_err)
)
```
///
////

## user_get_sdk_accounts
//// admonition | user_get_sdk_accounts()
    type: abstract

Requests all the accounts belonging to the current user.

**Returns:** A `GDOculusPlatformPromise` will contain an `Array` of `Dictionaries` with the type of account and its ID, if fulfilled. The function will error with a message if an error occured.

Example response:
``` json linenums="1"
[
    {
        "account_type": "OCULUS",
        "account_id": "3141592653589793"
    }
]
```

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.user_get_sdk_accounts()\
.then(func(sdk_accounts : Array):
    for sdk_account in sdk_accounts:
        print("Account type: ", sdk_account.account_type)
        print("Account ID: ", sdk_account.account_id)
)\
.error(func(sdk_accounts_err):
    print("Error getting SDK accounts: ", sdk_accounts_err)
)
```
///
////

## user_launch_block_flow
//// admonition | user_launch_block_flow(user_id : `String`)
    type: abstract

Launches a block flow to block the user associated with the given `user_id`. The user/player can then decide to block or cancel the request.

**Returns:** A `GDOculusPlatformPromise` will contain an `Dictionary` reflecting the choices of the user/player. The function will error with a message if an error occured.

Example response:
``` json linenums="1"
{
    "did_block": true,
    "did_cancel": false,
}
```

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.user_launch_block_flow("89793238462")\
.then(func(block_flow_resp : Dictionary):
    if block_flow_resp.did_block:
        print("User blocked!")
    else:
        print("Changed your mind?")
)\
.error(func(block_flow_err):
    print("Error launching block flow: ", block_flow_err)
)
```
///
////

## user_launch_unblock_flow
//// admonition | user_launch_unblock_flow(user_id : `String`)
    type: abstract

Launches an unblock flow to unblock the user associated with the given `user_id`. The user/player can then decide to unblock or cancel the request.

**Returns:** A `GDOculusPlatformPromise` will contain an `Dictionary` reflecting the choices of the user/player. The function will error with a message if an error occured.

Example response:
``` json linenums="1"
{
    "did_unblock": true,
    "did_cancel": false,
}
```

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.user_launch_unblock_flow("89793238462")\
.then(func(unblock_flow_resp : Dictionary):
    if unblock_flow_resp.did_unblock:
        print("User unblocked!")
    else:
        print("Better keep them blocked!")
)\
.error(func(unblock_flow_err):
    print("Error launching unblock flow: ", unblock_flow_err)
)
```
///
////

## user_launch_friend_request_flow
//// admonition | user_launch_friend_request_flow(user_id : `String`)
    type: abstract

Launches a friend request flow to add the user associated with the given `user_id` as a friend. The user/player can then decide to send the request or cancel it.

**Returns:** A `GDOculusPlatformPromise` will contain an `Dictionary` reflecting the choices of the user/player. The function will error with a message if an error occured.

Example response:
``` json linenums="1"
{
    "did_send_request": true,
    "did_cancel": false,
}
```

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.user_launch_friend_request_flow("89793238462")\
.then(func(friend_req_flow_resp : Dictionary):
    if friend_req_flow_resp.did_send_request:
        print("Friend request sent!")
    else:
        print("Actually now that I think about it...")
)\
.error(func(friend_req_flow_err):
    print("Error launching friend request flow: ", friend_req_flow_err)
)
```
///
////