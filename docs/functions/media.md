# Functions - Media

------

## media_share_to_facebook
//// admonition | media_share_to_facebook(post_text_suggestion : `String`, file_path : `String`, content_type : `MediaContentType`)
    type: abstract

Sends a request to initiate a flow to share media to Facebook. At the moment, only photos can be shared. The `post_text_suggestion` argument is a suggestion for the body of the post, `file_path` if an absolute path to an image and `content_type` is the type of content (photos only for now).

**Returns:** A `GDOculusPlatformPromise` that will contain a `Dictionary` with information about the status of the request. The promise will error if the request couldn't be completed.

**Enums:**

*MediaContentType:*

| Name                     |  Value  | Description                  |
|--------------------------|:-------:|------------------------------|
| MEDIA_CONTENT_TYPE_PHOTO |    1    | The content/file is a photo. |

Example response:
``` json linenums="1"
{
    "share_media_status": "SHARED",
}
```

///// admonition | Note
    type: warning

`share_media_status` can be `UNKNOWN`, `SHARED` or `CANCELED`.
/////

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.media_share_to_facebook(\
"Check out this awesome location!",\
"/sdcard/some/path/to/an/image.png",\
GDOculusPlatform.MEDIA_CONTENT_TYPE_PHOTO\
)\
.then(func(share_media_resp : Dictionary):
    if share_media_resp.share_media_status != "SHARED":
        print("Couldn't share media.")
    else:
        print("Your friends will love that photo!")
)\
.error(func(share_media_err):
    print("Unable to share media to Facebook: ", share_media_err)
)
```
///
////
