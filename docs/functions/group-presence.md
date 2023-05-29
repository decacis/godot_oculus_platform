# Functions - Group Presence
Related Oculus Platform documentation:

- [https://developer.oculus.com/documentation/native/ps-group-presence-overview/](https://developer.oculus.com/documentation/native/ps-group-presence-overview/)
- [https://developer.oculus.com/documentation/native/ps-multiplayer-overview](https://developer.oculus.com/documentation/native/ps-multiplayer-overview)

------
## grouppresence_clear
//// admonition | grouppresence_clear()
    type: abstract

Clears the group presence information for the current application/user.

**Returns:** A `GDOculusPlatformPromise` that will contain a `bool` which will always be true, if fulfilled. The promise will error if the request couldn't be completed.

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.grouppresence_clear()\
.then(func(_resp : bool):
    print("Successfully cleared the group presence information!")
)\
.error(func(gp_err):
    print("Unable to clear group presence information: ", gp_err)
)
```
///
////

## grouppresence_send_invites
//// admonition | grouppresence_send_invites(user_ids : `Array`)
    type: abstract

Sends an invite to the specified users to join the current user session. Note that you must have ser the group presence information before to be allowed to send invites.

**Returns:** A `GDOculusPlatformPromise` that will contain a `GDOPAppInviteArray` which will contain a list of the invites that were sent, if fulfilled. The promise will error if the request couldn't be completed.

///// admonition | Note
    type: warning

Please see the example of the `invites` property from the `GDOPAppInviteArray` class [**here**](/godot_oculus_platform/classes/gdopappinvitearray/#invites) for an idea of the format of each invite.
/////

/// details | Example
    type: example
``` gdscript linenums="1"
var user_ids : Array = ["12184515760568", "92059382048201"]

GDOculusPlatform.grouppresence_send_invites(user_ids)\
.then(func(invites_array : GDOPAppInviteArray):
    var all_invites : Array = await GDOP.app_invites_array_get_all(invites_array)
    for invite in all_invites:
        if invite.is_active:
            print("Invite is active!")
)\
.error(func(invites_array_err):
    print("Unable to send invites: ", invites_array_err)
)
```
///
////

## grouppresence_set
//// admonition | grouppresence_set(options : `Dictionary`)
    type: abstract

Sets the information of the group presence for the current application/user. A list of options that can be included is shown bellow.

**Returns:** A `GDOculusPlatformPromise` that will contain a `bool` which will always be true, if fulfilled. The promise will error if the request couldn't be completed.

Available options:

| Key                       |  Type  | Example value             |
|---------------------------|:------:|---------------------------|
| deeplink_message_override | String | DEEPLINK_GO_TO_LOBBY      |
| destination_api_name      | String | MY_AWESOME_DESTINATION    |
| lobby_session_id          | String | some_lobby_id_147721      |
| match_session_id          | String | 41808448444_match         |
| is_joinable               |  bool  | true                      |

/// details | Example
    type: example
``` gdscript linenums="1"
var presence_opts : Dictionary = {
    "destination_api_name": "SNOWY_MOUNTAIN_0",
    "lobby_session_id": "some_user_lobby_0417",
    "match_session_id": "54087487487445",
    "is_joinable": true
}

GDOculusPlatform.grouppresence_set(presence_opts)\
.then(func(_resp : bool):
    print("Group presence info set!")
)\
.error(func(gp_err):
    print("Unable to set group presence information: ", gp_err)
)
```
///
////

## grouppresence_set_deeplink_message_override
//// admonition | grouppresence_set_deeplink_message_override(deeplink_message : `String`)
    type: abstract

Sets the user's deeplink message without changing the other group presence parameters. A destination must be set before using this function.

**Returns:** A `GDOculusPlatformPromise` that will contain a `bool` which will always be true, if fulfilled. The promise will error if the request couldn't be completed.

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.grouppresence_set_deeplink_message_override("SOME_OVERRIDE_DL")\
.then(func(_resp : bool):
    print("Group presence deeplink message set!")
)\
.error(func(gp_err):
    print("Unable to set deeplink message of group presence: ", gp_err)
)
```
///
////

## grouppresence_set_destination
//// admonition | grouppresence_set_destination(destination : `String`)
    type: abstract

Replaces the user's destination without chagind other group presence parameters.

**Returns:** A `GDOculusPlatformPromise` that will contain a `bool` which will always be true, if fulfilled. The promise will error if the request couldn't be completed.

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.grouppresence_set_destination("MISTY_FOREST")\
.then(func(_resp : bool):
    print("Group presence destination set!")
)\
.error(func(gp_err):
    print("Unable to set destination of group presence: ", gp_err)
)
```
///
////

## grouppresence_set_is_joinable
//// admonition | grouppresence_set_destination(is_joinable : `bool`)
    type: abstract

Sets whether the current user's destination and session is joinable without changing other parameters. The destination or lobby/match session ID must be set before.

**Returns:** A `GDOculusPlatformPromise` that will contain a `bool` which will always be true, if fulfilled. The promise will error if the request couldn't be completed.

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.grouppresence_set_is_joinable(false)\
.then(func(_resp : bool):
    print("Group presence joinable state set!")
)\
.error(func(gp_err):
    print("Unable to set joinable state of group presence: ", gp_err)
)
```
///
////

## grouppresence_set_lobby_session
//// admonition | grouppresence_set_lobby_session(id : `String`)
    type: abstract

Replaces the user's lobby session ID without chagind other group presence parameters.

**Returns:** A `GDOculusPlatformPromise` that will contain a `bool` which will always be true, if fulfilled. The promise will error if the request couldn't be completed.

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.grouppresence_set_lobby_session("354141101")\
.then(func(_resp : bool):
    print("Group presence lobby session set!")
)\
.error(func(gp_err):
    print("Unable to set lobby session of group presence: ", gp_err)
)
```
///
////

## grouppresence_set_match_session
//// admonition | grouppresence_set_match_session(id : `String`)
    type: abstract

Replaces the user's match session ID without chagind other group presence parameters.

**Returns:** A `GDOculusPlatformPromise` that will contain a `bool` which will always be true, if fulfilled. The promise will error if the request couldn't be completed.

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.grouppresence_set_match_session("my_match_651475")\
.then(func(_resp : bool):
    print("Group presence match session set!")
)\
.error(func(gp_err):
    print("Unable to set match session of group presence: ", gp_err)
)
```
///
////

## grouppresence_get_invitable_users
//// admonition | grouppresence_get_invitable_users(options : `Dictionary`)
    type: abstract

Requests a list of invitable users that can be invited to the current session. The list includes the user's bidirectional followers and other recently met users. The `options` argument is optional, and a list of allowed keys and examples is shown bellow.

**Returns:** A `GDOculusPlatformPromise` that will contain a `GDOPUserArray` that contains a list of users, if fulfilled. The promise will error if the request couldn't be completed.

Available options for `options`:

| Key             |        Type      | Example                            |
|-----------------|:----------------:|------------------------------------|
| suggested_users | Array of Strings | ["8110887962260", "2154895289701"] |

Each element of the `suggested_users` `Array` should be a user ID as a `String`. Adding users to `suggested_users` will add them to the invitable users list.

///// admonition | Note
    type: warning

Please see the example of the `users` property from the `GDOPUserArray` class [**here**](/godot_oculus_platform/classes/gdopuserarray/#users) for an idea of the format of each user.
/////

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.grouppresence_get_invitable_users()\
.then(func(user_array : GDOPUserArray):
    var all_users : Array = await GDOP.users_array_get_all(user_array)
)\
.error(func(gp_invitable_users_err):
    print("Unable to get a list of invitable users: ", gp_invitable_users_err)
)
```
///
////

## grouppresence_get_sent_invites
//// admonition | grouppresence_get_sent_invites()
    type: abstract

Requests a list of invites sent by the current user.

**Returns:** A `GDOculusPlatformPromise` that will contain a `GDOPAppInviteArray` which will contain a list of the invites that have been sent by the user, if fulfilled. The promise will error if the request couldn't be completed.

///// admonition | Note
    type: warning

Please see the example of the `invites` property from the `GDOPAppInviteArray` class [**here**](/godot_oculus_platform/classes/gdopappinvitearray/#invites) for an idea of the format of each invite.
/////

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.grouppresence_get_sent_invites()\
.then(func(invites_array : GDOPAppInviteArray):
    var all_invites : Array = await GDOP.app_invites_array_get_all(invites_array)
    for invite in all_invites:
        if not invite.is_active:
            print("Invite is inactive!")
)\
.error(func(invites_array_err):
    print("Unable to get sent invites: ", invites_array_err)
)
```
///
////

## grouppresence_launch_invite_panel
//// admonition | grouppresence_launch_invite_panel(options : `Dictionary`)
    type: abstract

Launches the invite panel to invite other users to join the current session. The `options` argument is optional, and a list of allowed keys and examples is shown bellow.

**Returns:** A `GDOculusPlatformPromise` that will contain a `bool` that indicates if the user did invite other users or not, if fulfilled. The promise will error if the request couldn't be completed.

Available options for `options`:

| Key             |        Type      | Example                            |
|-----------------|:----------------:|------------------------------------|
| suggested_users | Array of Strings | ["8110887962260", "2154895289701"] |

Each element of the `suggested_users` `Array` should be a user ID as a `String`. Adding users to `suggested_users` will add them to the invitable users list.

/// details | Example
    type: example
``` gdscript linenums="1"
var options : Dictionary = {
    "suggested_users": ["5015441880527"]
}

GDOculusPlatform.grouppresence_launch_invite_panel(options)\
.then(func(did_send_invite : bool):
    if did_send_invite:
        print("Great! now wait for them to respond to your request.")
)\
.error(func(launch_invite_p_err):
    print("Unable to launch invite panel: ", launch_invite_p_err)
)
```
///
////

## grouppresence_launch_multiplayer_error_dialog
//// admonition | grouppresence_launch_multiplayer_error_dialog(error_key : `MultiplayerErrorErrorKey`)
    type: abstract

Shows an error dialog with a predefined message.

**Returns:** A `GDOculusPlatformPromise` that will contain a `bool` which will always be true, if fulfilled. The promise will error if the request couldn't be completed.

Enums:

**MultiplayerErrorErrorKey:**

| Name                                     | Value | Description             |
|------------------------------------------|:-----:|-------------------------|
| MULTIPLAYER_ERR_KEY_DEST_UNAVAILABLE     |   1   | Destination unavailable |
| MULTIPLAYER_ERR_KEY_DLC_REQUIRED         |   2   | A DLC is required       |
| MULTIPLAYER_ERR_KEY_GENERAL              |   3   | Generic error message   |
| MULTIPLAYER_ERR_KEY_GROUP_FULL           |   4   | The lobby/match is full |
| MULTIPLAYER_ERR_KEY_INVITER_NOT_JOINABLE |   5   | The inviter cannot be joined |
| MULTIPLAYER_ERR_KEY_LVL_NOT_HIGH_ENOUGH  |   6   | User is not of high enough level |
| MULTIPLAYER_ERR_KEY_LVL_NOT_UNLOCKED     |   7   | The level has not been unlocked yet |
| MULTIPLAYER_ERR_KEY_NETWORK_TIMEOUT      |   8   | Network timed out |
| MULTIPLAYER_ERR_KEY_NO_LONGER_AVAILABLE  |   9   | The lobby/match/invite is not longer valid or available |
| MULTIPLAYER_ERR_KEY_UPDATE_REQUIRED      |   10  | An update is required |
| MULTIPLAYER_ERR_KEY_TUTORIAL_REQUIRED    |   11  | Completing the tutorial is required |

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.grouppresence_launch_multiplayer_error_dialog(GDOculusPlatform.MULTIPLAYER_ERR_KEY_GROUP_FULL)\
.then(func(_resp_ : bool):
    print("User was informed that the group is already full.")
)\
.error(func(mp_error_err):
    print("Unable to launch multiplayer error dialog: ", mp_error_err)
)
```
///
////

## grouppresence_launch_rejoin_dialog
//// admonition | grouppresence_launch_rejoin_dialog(lobby_session_id : `String`, match_session_id : `String`, destination_api_name : `String`)
    type: abstract

Launches a rejoin dialog to allow the user to rejoin a previous session from a lobby/match ID. `lobby_session_id` and/or `match_session_id` must be set, but if you only use one and not the other, you can pass an empty `String` as the parameter.

**Returns:** A `GDOculusPlatformPromise` that will contain a `bool` which will indicate if the user decided to rejoin or not, if fulfilled. The promise will error if the request couldn't be completed.

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.grouppresence_launch_rejoin_dialog("8458441_my_lobby", "", "DEST_QUIET_LAKE")\
.then(func(did_rejoin : bool):
    if did_rejoin:
        print("User decided to rejoin, send them to the correct location!")
)\
.error(func(launch_rejoin_err):
    print("Unable to launch rejoin panel: ", launch_rejoin_err)
)
```
///
////

## grouppresence_launch_roster_panel
//// admonition | grouppresence_launch_roster_panel(options : `Dictionary`)
    type: abstract

Launches the roster panel which displays the current user in the roster and also users in the same session. The `options` argument is optional, and a list of allowed keys and examples is shown bellow.

**Returns:** A `GDOculusPlatformPromise` that will contain a `bool` which will always be true, if fulfilled. The promise will error if the request couldn't be completed.

Available options for `options`:

| Key             |        Type      | Example                            |
|-----------------|:----------------:|------------------------------------|
| suggested_users | Array of Strings | ["8110887962260", "2154895289701"] |

Each element of the `suggested_users` `Array` should be a user ID as a `String`. Adding users to `suggested_users` will add them to the invitable users list (the user can invite other users from the roster panel as well).

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.grouppresence_launch_roster_panel()\
.then(func(_resp : bool):
    print("Successfully opened roster panel.")
)\
.error(func(launch_roster_err):
    print("Unable to launch roster panel: ", launch_roster_err)
)
```
///
////