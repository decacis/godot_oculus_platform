# Classes - GDOPChallengeArray
Used in:

- [Challenges](/godot_oculus_platform/functions/challenges/)

-----

The `GDOPChallengeArray` is used to represent a page/block of an `Array` of challenges. The Oculus Platform SDK sends certain information in blocks, and you are responsible for paginating the data.

## Helper functions
To ease the extraction of the data contained in a `GDOPChallengeArray` we provide a helper function called `challenge_array_get_all` which, as the name implies, gets all the data from a given `GDOPChallengeArray`. Example:

``` gdscript linenums="1" hl_lines="10"
var challenge_filters : Dictionary = {
    "include_active_challenges": true,
    "include_future_challenges": true,
    "include_past_challenges": false
}

GDOculusPlatform.challenges_get_list(50, challenge_filters)\
.then(func(ch_array : GDOPChallengeArray):

    var all_challenges : Array = await GDOP.challenge_array_get_all(ch_array)
    for challenge in all_challenges:
        print("Title: ", challenge.title)
        
        if not challenge.leaderboard.is_empty():
            print("Challenge leaderboard ID: ", challenge.leaderboard.id)

)\
.error(func(leaderboard_entries_err):
    print("Unable to retrieve challenges: ", leaderboard_entries_err)
)
```

## Properties

### challenges
//// admonition | About
    type: abstract

An `Array` of challenges. See bellow for an example:

``` json linenums="1"
[
    {
        "id": "21541874514770",
        "title": "My Challenge",
        "description": "Collect the most coins in rush mode",
        "start_date": 1684639488,
        "end_date": 1671659703,
        "visibility": "PUBLIC",
        "type": "DEVELOPER_CREATED",
        "leaderboard": {
            "id": "4238760617434810",
            "api_name": "MY_LEADERBOARD_0",
            "destination": {
                "display_name": "Rush Mountain",
                "api_name": "MY_DESTINATION_0",
                "deeplink_message": "MY_DESTINATION_0_RUSH"
            }
        },
        "invited_users": GDOPUserArray,
        "participants": GDOPUserArray
    }
]
```
/// admonition | Notes
    type: warning

The `start_date` and `end_date` fields are UNIX timestamps (in seconds).

Take a look at the [GDOPUserArray](/godot_oculus_platform/classes/gdopuserarray/) documentation to know how to extact its data.

The `visibility` field can be `PUBLIC`, `PRIVATE`, `INVITE_ONLY` or `UNKNOWN`.

The `type` field can be `USER_CREATED`, `DEVELOPER_CREATED` or `UNKNOWN`.

The `leaderboard` field can be an empty `Dictionaty`.

The `destination` field of `leaderboard` can be an empty `Dictionary`.
///
////

## Functions

### get_has_prev_page
//// admonition | get_has_prev_page()
    type: abstract

Used to know if there are more entries previous to this block of challenges.

**Returns:** A `bool` that will be `true` if there are previous blocks of challenges that can be extracted and `false` otherwise.
////

### get_has_next_page
//// admonition | get_has_next_page()
    type: abstract

Used to know if there are more entries next to this block of challenges.

**Returns:** A `bool` that will be `true` if there are next blocks of challenges that can be extracted and `false` otherwise.
////

### get_total_count
//// admonition | get_total_count()
    type: abstract

Used to know the total count of challenges (not only the ones contained in a given block).

**Returns:** A `int` with the total count of challenges (not only the ones contained in a single block/page).
////

## How to paginate data
You can use the `challenge_array_get_prev_page` function from `GDOculusPlatform` to get the previous page/block of challenges and `challenge_array_get_next_page` to get the next page/block of challenges. See an example bellow:

``` gdscript linenums="1"
var challenges : Array = some_GDOPChallengeArray.challenges

GDOculusPlatform.challenge_array_get_prev_page(some_GDOPChallengeArray)\
.then(func(next_challenges : GDOPChallengeArray):

    challenges.append_array(next_challenges.challenges)

)\
.error(func(next_challenges_err):
    print("Error getting next page: ", next_challenges_err)
)
```