# Functions - Challenges
Related Oculus Platform documentation:

- [https://developer.oculus.com/documentation/native/ps-challenges/](https://developer.oculus.com/documentation/native/ps-challenges/)

------
## challenges_get
//// admonition | challenges_get(challenge_id : `String`)
    type: abstract

Returns information about a single challenge.

**Returns:** A `GDOculusPlatformPromise` that will contain a `Dictionary` with information about the challenge with the given `challenge_id` if fulfilled. The promise will error if the request couldn't be completed.

Example response:
``` json linenums="1"
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
    "invited_users": {
        "data": [],
        "next_page_url": ""
    },
    "participants": {
        "data": [
            {
                "id": "2384626433832795",
                "oculus_id": "some_id",
                "display_name": "Steve",
                "image_url": "https://example.org/some-image.png",
                "small_image_url": "",
                "presence": {
                    "presence_status": "OFFLINE",
                    "presence_deeplink_message": "",
                    "presence_destination_api_name": "",
                    "presence_lobby_session_id": "",
                    "presence_match_session_id": "",
                }
            }
        ],
        "next_page_url": ""
    }
}
```

/// admonition | Notes
    type: warning

Take a look at the example response and the note from the [user_get_blocked_users](/godot_oculus_platform/functions/user/#user_get_blocked_users) function to know more details about the `invited_users` and `participants` keys.

The `visibility` field can be `PUBLIC`, `PRIVATE`, `INVITE_ONLY` or `UNKNOWN`.

The `type` field can be `USER_CREATED`, `DEVELOPER_CREATED` or `UNKNOWN`.

The `leaderboard` field can be an empty `Dictionary`.

The `destination` field of `leaderboard` can be an empty `Dictionary`.
///

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.challenges_get("511854451440")\
.then(func(challenge_resp : Dictionary):
    print("Challenge information: ", challenge_resp)
)\
.error(func(challenge_err):
    print("Unable to retrieve challenge info: ", challenge_err)
)
```
///
////

## challenges_get_list
//// admonition | challenges_get_list(limit : `int`, challenge_options : `Dictionary`)
    type: abstract

Requests a list of challenges. You can pass various filters to narrow down the response - see bellow. The `limit` is the maximum number of challenges that this function can return.

**Returns:** A `GDOculusPlatformPromise` that will contain a `Dictionary` with information about a block of challenges if fulfilled. The promise will error if the request couldn't be completed.

Example response:

``` json linenums="1"
{
    "data": [
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
            "invited_users": {
                "data": [],
                "next_page_url": ""
            },
            "participants": {
                "data": [
                    {
                        "id": "2384626433832795",
                        "oculus_id": "some_id",
                        "display_name": "Steve",
                        "image_url": "https://example.org/some-image.png",
                        "small_image_url": "",
                        "presence": {
                            "presence_status": "OFFLINE",
                            "presence_deeplink_message": "",
                            "presence_destination_api_name": "",
                            "presence_lobby_session_id": "",
                            "presence_match_session_id": "",
                        }
                    }
                ],
                "next_page_url": ""
            }
        }
    ],
    "previous_page_url": "",
    "next_page_url": "",
    "total_count": 1
}
```

More info about [previous_page_url and next_page_url](/godot_oculus_platform/misc/about-previous_page_url-and-next_page_url/).

The `total_count` key is not necessarily the total count of challenges in this block, but the total count of challenges that satisfy this query.

**Default values:**

`limit` defaults to `10`.

By default `challenge_options` is:

``` json linenums="1"
{
    "viewer_filter": GDOculusPlatform.CHALLENGE_VISIBILITY_VIEWER_ALL_VISIBLE,
    "visibility": GDOculusPlatform.CHALLENGE_VISIBILITY_PUBLIC,
    "include_active_challenges": true,
    "include_future_challenges": false,
    "include_past_challenges": false
}
```

`challenge_options` can have the following **optional** keys/fields:

| Key                       |              Type               | Example                                                  |
|---------------------------|:-------------------------------:|----------------------------------------------------------|
| leaderboard_name          |             String              | MY_AWESOME_LEADERBOARD_API_NAME                          |
| title                     |             String              | Coin Challenge                                           |
| description               |             String              | Collect as many coins as you can!                        |
| start_date                |               int               | 1784034738                                               |
| end_date                  |               int               | 1791012840                                               |
| viewer_filter             | ChallengeVisibilityViewerFilter | GDOculusPlatform.CHALLENGE_VISIBILITY_VIEWER_ALL_VISIBLE |
| visibility                |       ChallengeVisibility       | GDOculusPlatform.CHALLENGE_VISIBILITY_PUBLIC             |
| include_active_challenges |               bool              | true                                                     |
| include_future_challenges |               bool              | false                                                    |
| include_past_challenges   |               bool              | true                                                     |

**Enums:**

*ChallengeVisibilityViewerFilter*

| Name                                                 |  Value  | Description                                                               |
|------------------------------------------------------|:-------:|---------------------------------------------------------------------------|
| CHALLENGE_VISIBILITY_VIEWER_ALL_VISIBLE              |    1    | Will return all challenges visible to the user.                           |
| CHALLENGE_VISIBILITY_VIEWER_PARTICIPATING            |    2    | Will return only challenges where the viewer is participating.            |
| CHALLENGE_VISIBILITY_VIEWER_INVITED                  |    3    | Will return only challenges where the viewer is invited.                  |
| CHALLENGE_VISIBILITY_VIEWER_PARTICIPATING_OR_INVITED |    4    | Will return only challenges where the viewer is participating or invited. |

*ChallengeVisibility*

| Name                             |  Value  | Description                                                               |
|----------------------------------|:-------:|---------------------------------------------------------------------------|
| CHALLENGE_VISIBILITY_INVITE_ONLY |    1    | Will return all challenges that are invite only.                          |
| CHALLENGE_VISIBILITY_PUBLIC      |    2    | Will return all public challenges.                                        |
| CHALLENGE_VISIBILITY_PRIVATE     |    3    | Will return all private challenges.                                       |

/// details | Example
    type: example
``` gdscript linenums="1"
var challenge_filters : Dictionary = {
    "start_date": 1684034738,
    "include_active_challenges": true,
    "include_future_challenges": true,
    "include_past_challenges": false
}

GDOculusPlatform.challenges_get_list(10, challenge_filters)\
.then(func(ch_array : Dictionary):

    if not ch_array.previous_page_array.is_empty():
        # Get previous page
        pass
    if not ch_array.next_page_array.is_empty():
        # Get next page
        pass
    
    for challenge in ch_array.data:
        print("Title: ", challenge.title)
        
        if not challenge.leaderboard.is_empty():
            print("Challenge leaderboard ID: ", challenge.leaderboard.id)

)\
.error(func(leaderboard_entries_err):
    print("Unable to retrieve challenges: ", leaderboard_entries_err)
)
```
///
////

## challenges_get_entries
//// admonition | challenges_get_entries(challenge_id : `String`, limit : `int`, filter : `LeaderboardFilterType`, start_at : `LeaderboardStartAt`)
    type: abstract

Requests the entries of the challenge with the given `challenge_id`. The `limit` argument defines the number of entries to return and **must be more than 0**. If you set the `filter` to `GDOculusPlatform.LEADERBOARD_FILTER_TYPE_FRIENDS` you can restrict the result to bidirectional followers, for example.

**Returns:** A `GDOculusPlatformPromise` that will contain a `Dictionary` with information about a block of entries from the challenge. The promise will error if the request couldn't be fulfilled.

You can check the `enums` from [leaderboard_get_entries](/godot_oculus_platform/functions/leaderboards/#leaderboard_get_entries) to know what values you are allowed to use.

``` json linenums="1"
{
    "data": [
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
    ],
    "previous_page_url": "",
    "next_page_url": "",
    "total_count": 1,
}
```

More info about [previous_page_url and next_page_url](/godot_oculus_platform/misc/about-previous_page_url-and-next_page_url/).

/// admonition | Note
    type: warning

The `total_count` key is not the total count of elements in this page/block, but the total count of entries that satisfy the query/request. They can be the same if there are no more entries, but they don't have to.

The `timestamp` key is a UNIX timestamp (in seconds).
///

/// details | Example
    type: example
``` gdscript linenums="1"
var leaderboard_info : Dictionary = {
    "id": "185485748521",
    "limit": 50,
    "filter": GDOculusPlatform.LEADERBOARD_FILTER_TYPE_NONE,
    "start_at": GDOculusPlatform.LEADERBOARD_START_AT_CENTERED_ON_VIEWER
}

GDOculusPlatform.challenges_get_entries(\
leaderboard_info.id,\
leaderboard_info.limit,\
leaderboard_info.filter,\
leaderboard_info.start_at\
)\
.then(func(c_entries : Dictionary):
    for entry in c_entries.data:
        print("User: ", entry.user.oculus_id)
        print("Score: ", entry.score)
        print("------------------")

)\
.error(func(challenge_entries_err):
    print("Unable to retrieve challenge entries: ", challenge_entries_err)
)
```
///
////

## challenge_get_entries_after_rank
//// admonition | challenge_get_entries_after_rank(challenge_id : `String`, limit : `int`, after_rank : `int`)
    type: abstract

Requests the entries of the challenge with the given `challenge_id` after a given `after_rank`, for example, 5 returns challenge results starting with the 6th user. The `limit` argument defines the number of entries to return and **must be more than 0**.

The `after_rank` argument is exclusive, meaning that if for example you call this function with a `limit` of 3 and `after_rank` of 5, the response will include the 6th, 7th and 8th ranks/entries.

**Returns:** A `GDOculusPlatformPromise` that will contain a `Dictionary` with information about a block of entries from the challenge. The promise will error if the request couldn't be fulfilled.

///// admonition | Note
    type: warning

Take a look at the example response and the note from the [challenges_get_entries](#challenges_get_entries) function to know more details about the possible response from this function.
/////

/// details | Example
    type: example
``` gdscript linenums="1"
var challenge_info : Dictionary = {
    "id": "154874515188",
    "limit": 5,
    "after_rank": 10
}

GDOculusPlatform.challenge_get_entries_after_rank(\
challenge_info.id,\
challenge_info.limit,\
challenge_info.after_rank\
)\
.then(func(c_entries : Dictionary):

    if not c_entries.previous_page_url.is_empty():
        # Get previous page
        pass
    if not c_entries.next_page_url.is_empty():
        # Get next page
        pass
    
    for entry in c_entries.data:
        print("User: ", entry.user.oculus_id)
        print("Rank: ", entry.rank)
        print("------------------")

)\
.error(func(challenge_entries_err):
    print("Unable to retrieve challenge entries: ", challenge_entries_err)
)
```
///
////

## challenge_get_entries_by_ids
//// admonition | challenge_get_entries_by_ids(challenge_id : `String`, limit : `int`, user_ids : `Array`, start_at : `LeaderboardStartAt`)
    type: abstract

Requests the entries of the challenge with the given `challenge_id` and only entries that match the given `user_ids`. The `limit` argument defines the number of entries to return and **must be more than 0**. If the `start_at` argument is `LEADERBOARD_START_AT_CENTERED_ON_VIEWER` or `LEADERBOARD_START_AT_CENTERED_ON_VIEWER_OR_TOP` the current user/player ID will be automatically added to the request.

**Returns:** A `GDOculusPlatformPromise` that will contain a `Dictionary` with information about a block of entries from the challenge. The promise will error if the request couldn't be fulfilled.

///// admonition | Note
    type: warning

Take a look at the example response and the note from the [challenges_get_entries](#challenges_get_entries) function to know more details about the possible response from this function.
/////

/// details | Example
    type: example
``` gdscript linenums="1"
var challenge_info : Dictionary = {
    "id": "51418484515504",
    "limit": 5,
    "user_ids": [
        "2614448641204419",
        "7822381524110013"
    ],
    "start_at": GDOculusPlatform.LEADERBOARD_START_AT_CENTERED_ON_VIEWER
}

GDOculusPlatform.challenge_get_entries_by_ids(\
challenge_info.id,\
challenge_info.limit,\
challenge_info.user_ids,\
challenge_info.start_at\
)\
.then(func(c_entries : Dictionary):

    for entry in c_entries.data:
        print("User: ", entry.user.oculus_id)
        print("Rank: ", entry.rank)
        print("Score: ", entry.display_score)
        print("------------------")
)\
.error(func(challenge_entries_err):
    print("Unable to retrieve challenge entries: ", challenge_entries_err)
)
```
///
////

## challenges_join
//// admonition | challenges_join(challenge_id : `String`)
    type: abstract

Sends a request to join the current user to the challenge with the `challenge_id` if the user has permission.

**Returns:** A `GDOculusPlatformPromise` that will contain a `Dictionary` with information about the challenge with the given `challenge_id` if fulfilled. The promise will error if the request couldn't be completed.

See the example response from [challenges_get](#challenges_get) to know the format of the `Dictionary` that this function will return.

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.challenges_join("264822651547")\
.then(func(challenge_info : Dictionary):
    print("Challenge information: ", challenge_info)
)\
.error(func(challenge_join_err):
    print("Unable to join challenge: ", challenge_join_err)
)
```
///
////

## challenges_leave
//// admonition | challenges_leave(challenge_id : `String`)
    type: abstract

Sends a request to withdraw the current user to the challenge with the `challenge_id` if the user has permission.

**Returns:** A `GDOculusPlatformPromise` that will contain a `Dictionary` with information about the challenge with the given `challenge_id` if fulfilled. The promise will error if the request couldn't be completed.

See the example response from [challenges_get](#challenges_get) to know the format of the `Dictionary` that this function will return.

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.challenges_leave("264822651547")\
.then(func(challenge_info : Dictionary):
    print("Challenge information: ", challenge_info)
)\
.error(func(challenge_leave_err):
    print("Unable to leave challenge: ", challenge_leave_err)
)
```
///
////

## challenges_decline_invite
//// admonition | challenges_decline_invite(challenge_id : `String`)
    type: abstract

Sends a request to decline an invite to join the challenge with the given `challenge_id`.

**Returns:** A `GDOculusPlatformPromise` that will contain a `Dictionary` with information about the challenge with the given `challenge_id` if fulfilled. The promise will error if the request couldn't be completed.

See the example response from [challenges_get](#challenges_get) to know the format of the `Dictionary` that this function will return.

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.challenges_decline_invite("264822651547")\
.then(func(challenge_info : Dictionary):
    print("Challenge information: ", challenge_info)
)\
.error(func(challenge_decline_err):
    print("Unable to decline challenge invite: ", challenge_decline_err)
)
```
///
////
