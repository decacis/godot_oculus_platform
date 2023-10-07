# Functions - User Age Category
Related Oculus Platform documentation:

- [https://developer.oculus.com/documentation/native/ps-age-group-apis/](https://developer.oculus.com/documentation/native/ps-age-group-apis/)

------

## useragecategory_get
//// admonition | useragecategory_get()
    type: abstract

Retrieves the age group of the current user from Meta.

**Returns:** A `GDOculusPlatformPromise` that will contain a `AccountAgeCategory` that lets you know the age group of the current user. The promise will error if the request couldn't be completed.

**Enums:**

*AccountAgeCategory:*

| Name                       |  Value  | Description                          |
|----------------------------|:-------:|--------------------------------------|
| ACCOUNTAGECATEGORY_UNKNOWN |    0    | Unknown age group.                   |
| ACCOUNTAGECATEGORY_CHILD   |    1    | For users between the ages of 10-12  |
| ACCOUNTAGECATEGORY_TEEN    |    2    | For users between the ages of 13-17  |
| ACCOUNTAGECATEGORY_ADULT   |    3    | For users between the ages 18 and up |

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.useragecategory_get()\
.then(func(user_age_category : GDOculusPlatform.AccountAgeCategory):
    match user_age_category:
        GDOculusPlatform.ACCOUNTAGECATEGORY_CHILD:
            print("The user is a child!")
        GDOculusPlatform.ACCOUNTAGECATEGORY_TEEN:
            print("The user is a teen!")
        GDOculusPlatform.ACCOUNTAGECATEGORY_ADULT:
            print("The user is an adult!")
        _:
            print("No idea about the age of the user!")
)\
.error(func(user_age_category_err):
    print("Unable to retrieve the user age category: ", user_age_category_err)
)
```
///
////

## useragecategory_report
//// admonition | useragecategory_report(app_age_category : `AppAgeCategory`)
    type: abstract

Used to report the app age cateogry to Meta.

**Returns:** A `GDOculusPlatformPromise` that will contain a `bool` (true) if the request was successful. The promise will error if the request couldn't be completed.

**Enums:**

*AppAgeCategory:*

| Name                     |  Value  | Description                          |
|--------------------------|:-------:|--------------------------------------|
| APPAGECATEGORY_CHILD     |    1    | The user's age is under 13 years.    |
| APPAGECATEGORY_NON_CHILD |    2    | The user's age is 13 years or older. |

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.useragecategory_report(GDOculusPlatform.APPAGECATEGORY_NON_CHILD)\
.then(func(report_resp : bool):
    print("Successfully reported the app age category!")
)\
.error(func(report_err):
    print("Unable to report the app's age category: ", report_err)
)
```
///
////