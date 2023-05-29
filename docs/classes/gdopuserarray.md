# Classes - GDOPUserArray
Used in:

- [User](/godot_oculus_platform/functions/user/)
- [Application](/godot_oculus_platform/functions/application/)
- [Challenges](/godot_oculus_platform/functions/challenges/)
- [Group Presence](/godot_oculus_platform/functions/group-presence/)

-----

The `GDOPUserArray` is used to represent a page/block of an `Array` of users. The Oculus Platform SDK sends certain information in blocks, and you are responsible for paginating the data.

## Helper functions
To ease the extraction of the data contained in a `GDOPUserArray` we provide a helper function called `users_array_get_all` which, as the name implies, gets all the data from a given `GDOPUserArray`. Example:

``` gdscript linenums="1" hl_lines="4"
GDOculusPlatform.user_get_logged_in_user_friends()\
.then(func(friends : GDOPUserArray):

    var all_friends : Array = await GDOP.users_array_get_all(friends)
    print("Friends: ", all_friends)

)\
.error(func(friends_err):
    print("Error getting friends: ", friends_err)
)
```

## Properties

### users
//// admonition | About
    type: abstract

An `Array` of users. See bellow for an example:

``` json linenums="1"
[
    {
        "id": "2384626433832795",
        "oculus_id": "some_id",
        "display_name": "Steve",
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
]
```
////

## Functions

### get_has_next_page
//// admonition | get_has_next_page()
    type: abstract

Used to know if there is more data to extract.

**Returns:** A `bool` that will be `true` if there is more data to extract (there is a next page) and `false` otherwise.
////

## How to paginate data
You can use the `user_array_get_next_page` function from `GDOculusPlatform` to get the next page of users. See an example bellow:

``` gdscript linenums="1"
var users : Array = some_GDOPUserArray.users

GDOculusPlatform.user_array_get_next_page(some_GDOPUserArray)\
.then(func(next_array : GDOPUserArray):

    users.append_array(next_array.users)

)\
.error(func(next_array_err):
    print("Error getting next page: ", next_array_err)
)
```