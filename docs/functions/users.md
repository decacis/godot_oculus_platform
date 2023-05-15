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
---
## get_user_access_token
//// admonition | get_user_access_token()

Requests a token of the current user suitable to make REST calls against graph.oculus.com

**Returs:** A `GDOculusPlatformPromise` that will be fulfilled with the access token as a `String` parameter. The function will error with a message if an error occured.

/// details | Example
```
GDOculusPlatform.get_user_access_token()\
.then(func(user_access_token : String):
    print("Access token: ", user_access_token)
)\
.error(func(user_access_token_err):
    print("Error getting user proof: ", user_access_token_err)
)
```
///
////
---
## get_blocked_users
//// admonition | get_blocked_users()

Requests the user IDs of users blocked by the current user.

**Returs:** A `GDOculusPlatformPromise` that will contain an array of user IDs as `String`s. The function will error with a message if an error occured.

/// details | Example
```
GDOculusPlatform.get_blocked_users()\
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
---
## get_logged_in_user_friends
//// admonition | get_logged_in_user_friends()

Requests the user IDs of the current user's friends.

**Returs:** A `GDOculusPlatformPromise` will contain an `Array` of `Dictionaries` with information about each friend. Same format as the `Dictionary` returned by [get_user()](#get_user). The function will error with a message if an error occured.

/// details | Example
```
GDOculusPlatform.get_logged_in_user_friends()\
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
---
## get_org_scoped_id
//// admonition | get_org_scoped_id(user_id : `String`)

Requests an ID which is unique per org. Allows different apps within the same org to identify the user.

**Returs:** A `GDOculusPlatformPromise` will contain the given user's scoped org ID as a `String`. The function will error with a message if an error occured.

/// details | Example
```
GDOculusPlatform.get_org_scoped_id("31415926535")\
.then(func(org_scoped_id : String):
    print("Org scoped ID: ", org_scoped_id)
)\
.error(func(org_scoped_id_err):
    print("Error getting org scoped ID: ", org_scoped_id_err)
)
```
///
////
---
## get_sdk_accounts
//// admonition | get_sdk_accounts()

Requests all the accounts belonging to the current user.

**Returs:** A `GDOculusPlatformPromise` will contain an `Array` of `Dictionaries` with the type of account and its ID, if fulfilled. The function will error with a message if an error occured.

Example response:
```
{
    "account_type": "oculus",
    "account_id": "31415926535",
}
```

/// details | Example
```
GDOculusPlatform.get_sdk_accounts()\
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
---
## launch_block_flow
//// admonition | launch_block_flow(user_id : `String`)

Launches a block flow to block the user associated with the given `user_id`. The user/player can then decide to block or cancel the request.

**Returs:** A `GDOculusPlatformPromise` will contain an `Dictionary` reflecting the choices of the user/player. The function will error with a message if an error occured.

Example response:
```
{
    "did_block": true,
    "did_cancel": false,
}
```

/// details | Example
```
GDOculusPlatform.launch_block_flow("89793238462")\
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
---
## launch_unblock_flow
//// admonition | launch_unblock_flow(user_id : `String`)

Launches an unblock flow to unblock the user associated with the given `user_id`. The user/player can then decide to unblock or cancel the request.

**Returs:** A `GDOculusPlatformPromise` will contain an `Dictionary` reflecting the choices of the user/player. The function will error with a message if an error occured.

Example response:
```
{
    "did_unblock": true,
    "did_cancel": false,
}
```

/// details | Example
```
GDOculusPlatform.launch_unblock_flow("89793238462")\
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
---
## launch_friend_request_flow
//// admonition | launch_friend_request_flow(user_id : `String`)

Launches a friend request flow to add the user associated with the given `user_id` as a friend. The user/player can then decide to send the request or cancel it.

**Returs:** A `GDOculusPlatformPromise` will contain an `Dictionary` reflecting the choices of the user/player. The function will error with a message if an error occured.

Example response:
```
{
    "did_send_request": true,
    "did_cancel": false,
}
```

/// details | Example
```
GDOculusPlatform.launch_friend_request_flow("89793238462")\
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