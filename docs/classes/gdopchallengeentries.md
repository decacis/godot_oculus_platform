# Classes - GDOPChallengeEntries
Used in:

- [Challenges](/godot_oculus_platform/functions/challenges/)

-----

The `GDOPChallengeEntries` is used to represent a page/block of an `Array` of challenge entries. The Oculus Platform SDK sends certain information in blocks, and you are responsible for paginating the data.

## Helper functions
To ease the extraction of the data contained in a `GDOPChallengeEntries` we provide a helper function called `challenge_entries_get_all` which, as the name implies, gets all the data from a given `GDOPChallengeEntries`. Example:

``` gdscript linenums="1" hl_lines="14"
var challenge_info : Dictionary = {
    "id": "15418415174",
    "limit": 30,
    "after_rank": 10
}

GDOculusPlatform.challenge_get_entries_after_rank(\
challenge_info.id,\
challenge_info.limit,\
challenge_info.after_rank\
)\
.then(func(c_entries : GDOPChallengeEntries):

    var all_entries : Array = await GDOP.challenge_entries_get_all(c_entries)
    for entry in all_entries:
        print("User: ", entry.user.oculus_id)
        print("Score: ", entry.score)

)\
.error(func(challenge_entries_err):
    print("Unable to retrieve challenge entries: ", challenge_entries_err)
)
```

## Properties

### entries
//// admonition | About
    type: abstract

An `Array` of challenge entries. See bellow for an example:

``` json linenums="1"
[
    {
        "id": "5118451178741",
        "rank": 10,
        "score": 500,
        "timestamp": 1684639488,
        "display_score": "500 pts",
        "extra_data": "some custom data",
        "user": { 
            "display_name": "Steve",
            "id": "4238760617434810",
            "oculus_id": "user_oculus_id",
            "image_url": "https://example.org/user_image.png",
            "small_image_url": "https://example.org/user_image_small.png",
            "presence": {
                "presence_status": "OFFLINE",
                "presence_deeplink_message": "",
                "presence_destination_api_name": "",
                "presence_lobby_session_id": "",
                "presence_match_session_id": "" 
            }
        }
    }
]
```
/// admonition | Note
    type: warning

The `timestamp` key is a UNIX timestamp (in seconds).
///
////

## Functions

### get_has_prev_page
//// admonition | get_has_prev_page()
    type: abstract

Used to know if there are more entries previous to this block of entries.

**Returns:** A `bool` that will be `true` if there are previous blocks of entries that can be extracted and `false` otherwise.
////

### get_has_next_page
//// admonition | get_has_next_page()
    type: abstract

Used to know if there are more entries next to this block of entries.

**Returns:** A `bool` that will be `true` if there are next blocks of entries that can be extracted and `false` otherwise.
////

### get_total_count
//// admonition | get_total_count()
    type: abstract

Used to know the total count of entries (not only the ones contained in a given block).

**Returns:** A `int` with the total count of entries (not only the ones contained in a single block/page).
////

## How to paginate data
You can use the `challenge_entries_get_prev_page` function from `GDOculusPlatform` to get the previous page/block of entries and `challenge_entries_get_next_page` to get the next page/block of entries. See an example bellow:

``` gdscript linenums="1"
var entries : Array = some_GDOPChallengeEntries.entries

GDOculusPlatform.challenge_entries_get_prev_page(some_GDOPChallengeEntries)\
.then(func(prev_entries : GDOPChallengeEntries):

    var prev : Array = prev_entries.entries
    prev.append_array(some_GDOPChallengeEntries.entries)

)\
.error(func(next_entries_err):
    print("Error getting next page: ", next_entries_err)
)
```