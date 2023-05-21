# Functions - Leaderboards
Related Oculus Platform documentation:

- [https://developer.oculus.com/documentation/native/ps-leaderboards/](https://developer.oculus.com/documentation/native/ps-leaderboards/)

------
## leaderboard_get
//// admonition | leaderboard_get(leaderboard_name : `String`)
    type: abstract

Returns information about a single leaderboard.

**Returns:** A `GDOculusPlatformPromise` that will contain a `Dictionary` with information about the leaderboard with the given API name if fulfilled. The promise will error if the request couldn't be completed.

Example response:
``` json linenums="1"
{
    "id": "6579389442106298",
    "api_name": "MY_LEADERBOARD_0"
}
```

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.leaderboard_get("MY_LEADERBOARD_0")\
.then(func(leaderboard_resp : Dictionary):
    print("Leaderboard information: ", leaderboard_resp)
)\
.error(func(leaderboard_err):
    print("Unable to retrieve leaderboard info: ", leaderboard_err)
)
```
///
////

## leaderboard_get_entries
//// admonition | leaderboard_get_entries(leaderboard_name : `String`, limit : `int`, filter : `LeaderboardFilterType`, start_at : `LeaderboardStartAt`)
    type: abstract

Requests the entries of the leaderboard with the given `leaderboard_name`. The `limit` argument defines the number of entries to return and **must be more than 0**.

**Returns:** A `GDOculusPlatformPromise` that will contain an `Array` of `Dictionaries` with information about each entry of the leaderboard. The promise will error if the request couldn't be fulfilled.

Default values:

| Argument | Value                                              |
|----------|----------------------------------------------------|
| filter   | LeaderboardFilterType.LEADERBOARD_FILTER_TYPE_NONE |
| start_at | LeaderboardStartAt.LEADERBOARD_START_AT_TOP        |

Enums:

**LeaderboardFilterType**

| Name                             |  Value  | Description                                                                                                                 |
|----------------------------------|:-------:|-----------------------------------------------------------------------------------------------------------------------------|
| LEADERBOARD_FILTER_TYPE_NONE     |    0    | Will return all players in the leaderboard (within the other limits).
| LEADERBOARD_FILTER_TYPE_FRIENDS  |    1    | Will return only players who are bidirectional friends of the current user/player. Each entry will still have their absolute rank. |

**LeaderboardStartAt**

| Name                                    |  Value  | Description                                                                                           |
|-----------------------------------------|:-------:|-------------------------------------------------------------------------------------------------------|
| LEADERBOARD_START_AT_TOP                |    0    | Default behavior. Will return results starting with the player that is ranked 1st on the leaderboard. |
| LEADERBOARD_START_AT_CENTERED_ON_VIEWER |    1    | Will try to start from the user's rank on the leaderboard and center the leaderboard entries around that.  Example:  If the user is rank 10th and the request is to fetch 3 entries centered on the user, it'll return the entries ranked 9th, 10th, and 11th. If the user is not ranked on the requested leaderboard, this will return an error. |

Example response:
``` json linenums="1"
[
    {
        "id": "36310577835242",
        "rank": 3,
        "score": 500,
        "timestamp": 1684639488,
        "display_score": "500 pts",
        "extra_data": "",
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
///

/// details | Example
    type: example
``` gdscript linenums="1"
var leaderboard_info : Dictionary = {
    "name": "MY_LEADERBOARD_0",
    "limit": 50,
    "filter": LeaderboardFilterType.LEADERBOARD_FILTER_TYPE_NONE,
    "start_at": LeaderboardStartAt.LEADERBOARD_START_AT_CENTERED_ON_VIEWER
}

GDOculusPlatform.leaderboard_get_entries(\
leaderboard_info.name,\
leaderboard_info.limit,\
leaderboard_info.filter,\
leaderboard_info.start_at\
)\
.then(func(leaderboard_entries : Array):
    for entry in leaderboard_entries:
        
        print("User: ", entry.user.oculus_id)
        print("Rank: ", entry.rank)
        print("------------------")
)\
.error(func(leaderboard_entries_err):
    print("Unable to retrieve leaderboard entries: ", leaderboard_entries_err)
)
```
///
////

## leaderboard_get_entries_after_rank
//// admonition | leaderboard_get_entries_after_rank(leaderboard_name : `String`, limit : `int`, after_rank : `int`)
    type: abstract

Requests the entries of the leaderboard with the given `leaderboard_name` after a given `after_rank`. The `limit` argument defines the number of entries to return and **must be more than 0**.

The `after_rank` argument is exclusive, meaning that if for example you call this function with a `limit` of 3 and `after_rank` of 5, the response will include the 6th, 7th and 8th ranks/entries.

**Returns:** A `GDOculusPlatformPromise` that will contain a `Dictionary` with information about the leaderboard with the given API name if fulfilled. The promise will error if the request couldn't be completed.

You can check the example response of the [leaderboard_get_entries](#leaderboard_get_entries) functions to see an example of what this functions returns if fulfilled.

/// details | Example
    type: example
``` gdscript linenums="1"
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
.then(func(leaderboard_entries : Array):
    for entry in leaderboard_entries:
        
        print("User: ", entry.user.oculus_id)
        print("Rank: ", entry.rank)
        print("------------------")
)\
.error(func(leaderboard_entries_err):
    print("Unable to retrieve leaderboard entries: ", leaderboard_entries_err)
)
```
///
////

## leaderboard_get_entries_by_ids
//// admonition | leaderboard_get_entries_by_ids(leaderboard_name : `String`, limit : `int`, user_ids : `Array`, start_at : `LeaderboardStartAt`)
    type: abstract

Requests the entries of the leaderboard with the given `leaderboard_name` and only entries that match the given `user_ids`. The `limit` argument defines the number of entries to return and **must be more than 0**. If the `start_at` argument is `LEADERBOARD_START_AT_CENTERED_ON_VIEWER` the current user/player ID will be automatically added to the request.

As an example use case, you can use this function to get a list of users that are competing and compare their ranks.

**Returns:** A `GDOculusPlatformPromise` that will contain a `Dictionary` with information about the leaderboard with the given API name if fulfilled. The promise will error if the request couldn't be completed.

You can check the example response of the [leaderboard_get_entries](#leaderboard_get_entries) functions to see an example of what this functions returns if fulfilled.

Default values:

| Argument | Value                                              |
|----------|----------------------------------------------------|
| start_at | LeaderboardStartAt.LEADERBOARD_START_AT_TOP        |

/// details | Example
    type: example
``` gdscript linenums="1"
var leaderboard_info : Dictionary = {
    "name": "MY_LEADERBOARD_0",
    "limit": 10,
    "user_ids": [
        "4238760617434810",
        "7438380617106547"
    ],
    "start_at": LeaderboardStartAt.LEADERBOARD_START_AT_TOP
}

GDOculusPlatform.leaderboard_get_entries_by_ids(\
leaderboard_info.name,\
leaderboard_info.limit,\
leaderboard_info.user_ids,\
leaderboard_info.start_at\
)\
.then(func(leaderboard_entries : Array):
    for entry in leaderboard_entries:
        
        print("User: ", entry.user.oculus_id)
        print("Rank: ", entry.rank)
        print("Score: ", entry.display_score)
        print("------------------")
)\
.error(func(leaderboard_entries_err):
    print("Unable to retrieve leaderboard entries: ", leaderboard_entries_err)
)
```
///
////

## leaderboard_write_entry
//// admonition | leaderboard_write_entry(leaderboard_name : `String`, score : `int`, force_update : `bool`, extra : `Dictionary`)
    type: abstract

Sends a request to write a new entry to the leaderboard with the given `leaderboard_name`. See bellow for optional values for the `extra` `Dictionary`.

**Returns:** A `GDOculusPlatformPromise` that will contain a `Dictionary` with information about request status. The promise will error if the request couldn't be completed.

Default values:

| Argument     |  Value  |
|--------------|:-------:|
| force_update |  false  |
| extra        |    {}   |

**Note:** if `force_update` is true, then the new ranking will replace the previous ranking even if the new score is lower (assuming the leaderboard's sort order is higher is better).

Extra values (optional):

| Key                  |  Value type  | Description                                                        |
|----------------------|:------------:|--------------------------------------------------------------------|
| supplementary_metric |     int      | A supplementary metric used for tiebreaks. For example, if two users have a score of 10 but user1 has a `supplementary_metric` of 5 and user2 has a `supplementary_metric` of 8 (and the leaderboard's sort order is higher is better), then user2 will win. |
| extra_data           |   String     | A string of data to store along with the entry. You can use it to store details about the gameplay or any data that you want to associate with the entry. |

Example response:
``` json linenums="1"
{
    "did_update": true,
    "challenge_ids": []
}
```

/// details | Example
    type: example
``` gdscript linenums="1"
var entry_info : Dictionary = {
    "name": "MY_LEADERBOARD_0",
    "score": 50,
    "force_update": false,
    "extra": {
        "supplementary_metric": 10,
        "extra_data": ""
    }
}

GDOculusPlatform.leaderboard_write_entry(\
entry_info.name,\
entry_info.score,\
entry_info.force_update,\
entry_info.extra\
)\
.then(func(leaderboard_update_info : Dictionary):
    print("Entry updated? ", leaderboard_update_info.did_update)
)\
.error(func(leaderboard_update_err):
    print("Unable to add entry: ", leaderboard_update_err)
)
```
///
////