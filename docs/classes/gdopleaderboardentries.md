# Classes - GDOPLeaderboardEntries
Used in:

- [Leaderboards](/godot_oculus_platform/functions/leaderboards/)

-----

The `GDOPLeaderboardEntries` is used to represent a page/block of an `Array` of leaderboard entries. The Oculus Platform SDK sends certain information in blocks, and you are responsible for paginating the data.

## Helper functions
To ease the extraction of the data contained in a `GDOPLeaderboardEntries` we provide a helper function called `leaderboard_entries_get_all` which, as the name implies, gets all the data from a given `GDOPLeaderboardEntries`. Example:

``` gdscript linenums="1" hl_lines="14"
var leaderboard_info : Dictionary = {
    "name": "MY_LEADERBOARD_0",
    "limit": 10,
    "after_rank": 5
}

GDOculusPlatform.leaderboard_get_entries_after_rank(\
leaderboard_info.name,\
leaderboard_info.limit,\
leaderboard_info.after_rank\
)\
.then(func(l_entries : GDOPLeaderboardEntries):

    var all_entries : Array = await GDOP.leaderboard_entries_get_all(l_entries)
    for entry in all_entries:
        print("User: ", entry.user.oculus_id)
        print("Rank: ", entry.rank)

)\
.error(func(leaderboard_entries_err):
    print("Unable to retrieve leaderboard entries: ", leaderboard_entries_err)
)
```

## Properties

### entries
//// admonition | About
    type: abstract

An `Array` of leaderboard entries. See bellow for an example:

``` json linenums="1"
[
    {
        "id": "36310577835242",
        "rank": 3,
        "score": 500,
        "timestamp": 1684639488,
        "display_score": "500 pts",
        "extra_data": "",
        "supplementary_metric": {
            "id": "5614515145111",
            "metric": 16674
        },
        "user": { 
            "display_name": "Steve",
            "id": "4238760617434810",
            "oculus_id": "user_oculus_id",
            "image_url": "https://example.org/user_image.png",
            "small_image_url": "https://example.org/user_image_small.png",
            "presence": {
                "presence_status": "ONLINE",
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

The `supplementary_metric` key can be an empty `Dictionary`.
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

Used to know the total count of entries (not only the ones contained in a given block). You can use this to tell a user they are number 10 out of 100 entries, for example.

**Returns:** A `int` with the total count of entries (not only the ones contained in a single block/page).
////

## How to paginate data
You can use the `leaderboard_entries_get_prev_page` function from `GDOculusPlatform` to get the previous page/block of entries and `leaderboard_entries_get_next_page` to get the next page/block of entries. See an example bellow:

``` gdscript linenums="1"
var entries : Array = some_GDOPLeaderboardEntries.entries

GDOculusPlatform.leaderboard_entries_get_next_page(some_GDOPLeaderboardEntries)\
.then(func(next_entries : GDOPLeaderboardEntries):

    entries.append_array(next_entries.entries)

)\
.error(func(next_entries_err):
    print("Error getting next page: ", next_entries_err)
)
```