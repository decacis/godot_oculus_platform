# Functions - Asset Files
Related Oculus Platform documentation:

- [https://developer.oculus.com/documentation/native/ps-iap/](https://developer.oculus.com/documentation/native/ps-iap/)
- [https://developer.oculus.com/resources/add-ons/](https://developer.oculus.com/resources/add-ons/)

------
## assetfile_get_list
//// admonition | assetfile_get_list()
    type: abstract

Requests a list of asset files associated with this app.

**Returns:** A `GDOculusPlatformPromise` that will contain an `Array` of `Dictionaries` with information about each asset file. The promise will error if the request couldn't be fulfilled.

If the asset file is of type `language_pack`, the "tag" key is supposed to conform to the BCP47 standard, but in reality it replaces the "-" with "_" so what should be `en-US` ends up as `en_US`.

Example response:
``` json linenums="1"
[
    {
        "id": "151548188744",
        "type": "default",
        "download_status": "installed",
        "file_path": "/sdcard/path/to/asset.pck",
        "iap_status": "entitled",
        "metadata": "custom_metadata_set_by_you"
    },
    {
        "id": "821548111514",
        "type": "language_pack",
        "download_status": "available",
        "file_path": "/sdcard/path/to/asset.po",
        "iap_status": "free",
        "metadata": "",
        "language_info": {
            "english_name": "Spanish",
            "native_name": "Español",
            "tag": "es_ES"
        }
    }
]
```

Asset file types:

| Type          | Description                                                                                                           |
|---------------|-----------------------------------------------------------------------------------------------------------------------|
| default       | The asset file is used to download extra content post-installation.                                                   |
| store         | The asset file should be shown in the Store.                                                                          |
| language_pack | The asset file is used to manage different languages and translation data, which can be downloaded post-installation. |

Asset file download status:

| Type        | Description                                     |
|-------------|-------------------------------------------------|
| installed   | The asset file is installed                     |
| available   | The asset file can be downloaded                |
| in-progress | The asset file is being downloaded or installed |

Asset file IAP status:

| Type         | Description                                    |
|--------------|------------------------------------------------|
| free         | The asset file is free                         |
| entitled     | The user is entitled to the asset file         |
| not-entitled | The user is **not** entitled to the asset file |

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.assetfile_get_list()\
.then(func(asset_files : Array):
    for asset_file in asset_files:
        
        if asset_file.iap_status == "entitled"\
        and asset_file.download_status == "available":
            print("This asset file is available for download")
        
        elif asset_file.download_status == "installed"\
        and asset_file.iap_status == "not-entitled":
            print("User has an asset installed that they shouldn't have. Maybe they refunded the item?")
)\
.error(func(asset_files_err):
    print("Unable to retrieve list of assets: ", asset_files_err)
)
```
///
////

## assetfile_status_by_id
//// admonition | assetfile_status_by_id(asset_id : `String`)
    type: abstract

Requests information about a single asset file by its ID.

**Returns:** A `GDOculusPlatformPromise` that will contain an `Dictionary` with information about the asset file. The promise will error if the request couldn't be fulfilled.

See the example response from [assetfile_get_list](#assetfile_get_list) to get an idea of the response. `assetfile_get_list()` returns an `Array` because it can return multiple asset files, but this function returns a single asset file (and thus a `Dictionary` instead of an `Array`).

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.assetfile_status_by_id("151548188744")\
.then(func(asset_file : Dictionary):
    
    if asset_file.download_status == "installed"\
    and asset_file.iap_status == "not-entitled":
        print("User should not have this asset!")
)\
.error(func(asset_file_err):
    print("Unable to retrieve asset file: ", asset_file_err)
)
```
///
////

## assetfile_status_by_name
//// admonition | assetfile_status_by_name(asset_name : `String`)
    type: abstract

Requests information about a single asset file by its name.

**Returns:** A `GDOculusPlatformPromise` that will contain an `Dictionary` with information about the asset file. The promise will error if the request couldn't be fulfilled.

See the example response from [assetfile_get_list](#assetfile_get_list) to get an idea of the response. `assetfile_get_list()` returns an `Array` because it can return multiple asset files, but this function returns a single asset file (and thus a `Dictionary` instead of an `Array`).

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.assetfile_status_by_name("my_asset_file.po")\
.then(func(asset_file : Dictionary):
    
    download_file(asset_file.file_path)
)\
.error(func(asset_file_err):
    print("Unable to retrieve asset file: ", asset_file_err)
)
```
///
////

## assetfile_download_by_id
//// admonition | assetfile_download_by_id(asset_id : `String`)
    type: abstract

Sends a request to download an asset file with the given ID.

**Returns:** A `GDOculusPlatformPromise` that will contain an `Dictionary` with information about the request. The promise will error if the request couldn't be fulfilled.

Example response:

``` json linenums="1"
{
    "id": "821548111514",
    "file_path": "/sdcard/path/to/asset.pck"
}
```

/// admonition | Note
    type: warning

The `file_path` in the dictionary does not indicate that the asset has finished downloading, it just indicates where the asset will be/is being downloaded.

An `assetfile_download_update` `Signal` will be emitted periodically to track the progress of the download. Here's an example of the payload of the signal:

``` json linenums="1"
{
    "id": "821548111514",
    "completed": false,
    "total_bytes": 2048,
    "transferred_bytes": 1024
}
```

An `assetfile_download_finished` `Signal` will be emitted once the asset file has finished downloading. It will have a `String` with the asset file ID as a payload. Note that the `assetfile_download_update` `Signal` will be emitted as well one last time.

///

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.assetfile_download_finished.connect(call_me_when_finished)

GDOculusPlatform.assetfile_download_by_id("821548111514")\
.then(func(download_info : Dictionary):
    
    if download_info.file_path != "":
        print("Downloading file on path: ", download_info.file_path)
)\
.error(func(download_asset_err):
    print("Unable to download asset file: ", download_asset_err)
)

func call_me_when_finished(asset_file_id : String):
    print("Finished downloading file with ID: ", asset_file_id)
```
///
////

## assetfile_download_by_name
//// admonition | assetfile_download_by_name(asset_name : `String`)
    type: abstract

Sends a request to download an asset file with the given name.

**Returns:** A `GDOculusPlatformPromise` that will contain an `Dictionary` with information about the request. The promise will error if the request couldn't be fulfilled.

Please look at the response from [assetfile_download_by_id](#assetfile_download_by_id) - both this function and `assetfile_download_by_id` return the same data and can be used interchangeably, apart from using an ID for the other function and a name for this one.

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.assetfile_download_by_name("my_asset_file.obb")\
.then(func(download_info : Dictionary):
    
    if download_info.file_path != "":
        GDOP.call_on_finished_downloading("821548111514", call_me_when_finished)
)\
.error(func(download_asset_err):
    print("Unable to download asset file: ", download_asset_err)
)

func call_me_when_finished(asset_file_id : String):
    print("Finished downloading file with ID: ", asset_file_id)
```
///
////

## assetfile_download_cancel_by_id
//// admonition | assetfile_download_cancel_by_id(asset_id : `String`)
    type: abstract

Sends a request to cancel a download of the asset file with the given ID.

**Returns:** A `GDOculusPlatformPromise` that will contain an `Dictionary` with information about the request. The promise will error if the request couldn't be fulfilled.

Example response:

``` json linenums="1"
{
    "id": "244752684352",
    "file_path": "/sdcard/path/to/asset.zip",
    "success": true
}
```

/// admonition | Note
    type: warning

`success` will be `true` if the request was successful and `false` otherwise.
///

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.assetfile_download_cancel_by_id("244752684352")\
.then(func(download_cancel_info : Dictionary):
    
    if download_cancel_info.success:
        print("Successfully cancelled the download!")
)\
.error(func(download_cancel_err):
    print("Unable to cancel the download: ", download_cancel_err)
)
```
///
////

## assetfile_download_cancel_by_name
//// admonition | assetfile_download_cancel_by_name(asset_name : `String`)
    type: abstract

Sends a request to cancel a download of the asset file with the given name.

**Returns:** A `GDOculusPlatformPromise` that will contain an `Dictionary` with information about the request. The promise will error if the request couldn't be fulfilled.

Take a look at the example response from [assetfile_download_cancel_by_id](#assetfile_download_cancel_by_id) because both that function and this one return the same data.

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.assetfile_download_cancel_by_name("my_asset_name.zip")\
.then(func(download_cancel_info : Dictionary):
    
    if download_cancel_info.success:
        print("Successfully cancelled the download!")
)\
.error(func(download_cancel_err):
    print("Unable to cancel the download: ", download_cancel_err)
)
```
///
////

## assetfile_delete_by_id
//// admonition | assetfile_delete_by_id(asset_id : `String`)
    type: abstract

Sends a request to delete an asset file with the given ID.

**Returns:** A `GDOculusPlatformPromise` that will contain an `Dictionary` with information about the request. The promise will error if the request couldn't be fulfilled.

Example response:

``` json linenums="1"
{
    "id": "774568224174",
    "file_path": "/sdcard/path/to/asset.obb",
    "success": false
}
```

/// admonition | Note
    type: warning

`success` will be `true` if the request was successful and `false` otherwise.
///

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.assetfile_delete_by_id("774568224174")\
.then(func(delete_asset_info : Dictionary):
    
    if delete_asset_info.success:
        print("Successfully deleted the asset file!")
)\
.error(func(delete_asset_err):
    print("Unable to delete the asset file: ", delete_asset_err)
)
```
///
////

## assetfile_delete_by_name
//// admonition | assetfile_delete_by_name(asset_name : `String`)
    type: abstract

Sends a request to delete an asset file with the given name.

**Returns:** A `GDOculusPlatformPromise` that will contain an `Dictionary` with information about the request. The promise will error if the request couldn't be fulfilled.

Take a look at the example response from [assetfile_delete_by_id](#assetfile_delete_by_id) because both that function and this one return the same data.

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.assetfile_delete_by_name("pack_of_gems.pck")\
.then(func(delete_asset_info : Dictionary):
    
    if delete_asset_info.success:
        print("Successfully deleted the asset file!")
)\
.error(func(delete_asset_err):
    print("Unable to delete the asset file: ", delete_asset_err)
)
```
///
////