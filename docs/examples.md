# Examples
Here are some examples of using this asset. For more details make sure to check the documentation for each function you want to use.

### Entitlement check
An entitlement check allows you to quickly check if the user that launched the app actually is entitled to it.

``` gdscript linenums="1"
# Initializing android platform with the APP_ID as a parameter
GDOculusPlatform.initialize_android_async("314159265358979")\
.then(func(_initialization_resp):
    print("Oculus Platform initialized!")
    
    # Is the user entitled to this app?
    GDOculusPlatform.get_is_viewer_entitled()\
    .then(func(_is_viewer_entitled_resp):
        print("User is entitled!")
        
    )\
    .error(func(is_viewer_entitled_err):
        print("User not entitled/error! ", is_viewer_entitled_err)
    )
    
)\
.error(func(initialization_err):
    print("Oculus Platform initialization error: ", initialization_err)
)
```

### Getting logged in user information
Since the promises (`then` and `error` functions) take a `Callable` you can do something like this:

``` gdscript linenums="1"
GDOculusPlatform.initialize_android_async("6324217457624418")\
.then(func(_initialization_resp):
    print("Oculus Platform initialized")
        
    GDOculusPlatform.get_logged_in_user()\
    .then(_process_logged_in_user_response)
    
)\
.error(func(initialization_err):
    print("Oculus Platform initialization error: ", initialization_err)
)

func _process_logged_in_user_response(resp : Dictionary):
    print("LOGGED IN USER INFO:")
    print("--------------------")

    print("ID: ", resp.id)
    print("OCULUS ID: ", resp.oculus_id)
    print("DISPLAY NAME: ", resp.display_name)
    print("IMAGE URL: ", resp.image_url)
    print("SMALL IMAGE URL: ", resp.small_image_url)
```

You may have noticed that we didn't add an `error` function call to the `get_logged_in_user()` function. Both the `then` and `error` functions are optional, and you can skip them if you don't care about their result.