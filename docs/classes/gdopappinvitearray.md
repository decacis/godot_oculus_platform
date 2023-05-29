# Classes - GDOPAppInviteArray
Used in:

- [Group Presence](/godot_oculus_platform/functions/group-presence/)

-----

The `GDOPAppInviteArray` is used to represent a page/block of an `Array` of application invites. The Oculus Platform SDK sends certain information in blocks, and you are responsible for paginating the data.

## Helper functions
To ease the extraction of the data contained in a `GDOPAppInviteArray` we provide a helper function called `app_invites_array_get_all` which, as the name implies, gets all the data from a given `GDOPAppInviteArray`. Example:

``` gdscript linenums="1" hl_lines="3"
GDOculusPlatform.grouppresence_get_sent_invites()\
.then(func(sent_invites : GDOPAppInviteArray):
    var all_invites : Array = await GDOP.app_invites_array_get_all(sent_invites)
    for invite in all_invites:
        if invite.is_active:
            pass # do something
)\
.error(func(sent_invites_err):
    push_error("Error getting sent invites: ", sent_invites_err)
)
```

## Properties

### invites
//// admonition | About
    type: abstract

An `Array` of invites. See bellow for an example:

``` json linenums="1"
[
    {
        "id": "818518747157704",
        "lobby_session_id": "some_custom_id_1877",
        "match_session_id": "some_custom_id_0544",
        "is_active": true,
        "recipient": {
            "display_name": "username",
            "id": "51054474470074144",
            "oculus_id": "user_id",
            "image_url": "https://example.org/some_url",
            "small_image_url": "https://example.org/some_other_url",
            "presence": {
                "presence_status": "OFFLINE",
                "presence_deeplink_message": "",
                "presence_destination_api_name": "",
                "presence_lobby_session_id": "",
                "presence_match_session_id": ""
            }
        }, 
        "destination": {
            "display_name": "My Destination",
            "api_name": "MY_DESTINATION_0",
            "deep_link_message": "MY_DESTINATION_0_DL"
        }
    }
]
```

///// admonition | Note
    type: warning

The `recipient` and `destination` can be empty `Dictionaries` in some cases.
/////

////

## Functions

### get_has_next_page
//// admonition | get_has_next_page()
    type: abstract

Used to know if there is more data to extract.

**Returns:** A `bool` that will be `true` if there is more data to extract (there is a next page) and `false` otherwise.
////

## How to paginate data
You can use the `app_invites_array_get_next_page` function from `GDOculusPlatform` to get the next page of invites. See an example bellow:

``` gdscript linenums="1"
var invites : Array = some_GDOPAppInviteArray.invites

GDOculusPlatform.app_invites_array_get_next_page(some_GDOPAppInviteArray)\
.then(func(next_array : GDOPAppInviteArray):

    invites.append_array(next_array.invites)

)\
.error(func(next_array_err):
    print("Error getting next page: ", next_array_err)
)
```