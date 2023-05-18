# Functions - In-App Purchases
Related Oculus Platform documentation:

- [https://developer.oculus.com/documentation/native/ps-iap/](https://developer.oculus.com/documentation/native/ps-iap/)

------
## iap_get_viewer_purchases
//// admonition | iap_get_viewer_purchases()
    type: abstract

Requests all of the logged-in user purchases.

**Returs:** A `GDOculusPlatformPromise` that will contain an `Array` of `Dictionaries` with information about each purchase (both consumable and durable). The promise will error if the request couldn't be fulfilled.

Example response:
``` json linenums="1"
[
    {
        "sku": "durable_product_sku",
        "reporting_id": "154128782811",
        "purchase_str_id": "332574476951",
        "grant_time": 1683990516,
        "expiration_time": 0,
        "developer_payload": "my_custom_payload"
    },
    {
        "sku": "consumable_product_sku",
        "reporting_id": "184128782822",
        "purchase_str_id": "882574476943",
        "grant_time": 1683990517,
        "expiration_time": 1684004517,
        "developer_payload": ""
    }
]
```

/// admonition | Note
    type: warning

Keys ending with `_time` like `grant_time` are in seconds. They are UNIX timestamps.
///

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.iap_get_viewer_purchases()\
.then(func(user_purchases : Array):
    for purchase in user_purchases:
        print("Purchased at: ", purchase.grant_time)
)\
.error(func(user_purchases_err):
    print("Unable to retrieve user purchases: ", user_purchases_err)
)
```
///
////

## iap_get_viewer_purchases_durable_cache
//// admonition | iap_get_viewer_purchases_durable_cache()
    type: abstract

Requests all of the logged-in user purchases that are **durable**. This is taken from the cache, so it is recommended to first call [iap_get_viewer_purchases](#iap_get_viewer_purchases) to update the cache and use this function for subsequent calls.

**Returs:** A `GDOculusPlatformPromise` that will contain an `Array` of `Dictionaries` with information about each durable cached purchase. The promise will error if the request couldn't be fulfilled.

Example response:
``` json linenums="1"
[
    {
        "sku": "durable_product_sku",
        "reporting_id": "154128782811",
        "purchase_str_id": "332574476951",
        "grant_time": 1683990516,
        "expiration_time": 0,
        "developer_payload": ""
    },
    {
        "sku": "durable_product_sku_2",
        "reporting_id": "154128452811",
        "purchase_str_id": "328574476711",
        "grant_time": 1683990518,
        "expiration_time": 0,
        "developer_payload": "developer custom message"
    }
]
```

/// admonition | Note
    type: warning

`grant_time` is a UNIX timestamp (in seconds). `expiration_time` will be 0 for every item since they are durable purchases.
///

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.iap_get_viewer_purchases_durable_cache()\
.then(func(user_durable_purchases : Array):
    for d_purchase in user_durable_purchases:
        print("Purchased at: ", d_purchase.grant_time)
)\
.error(func(user_durable_purchases_err):
    print("Unable to retrieve user durable purchases: ", user_durable_purchases_err)
)
```
///
////

## iap_get_products_by_sku
//// admonition | iap_get_products_by_sku(sku_list : `Array`)
    type: abstract

Requests product information of a list of SKUs. The `sku_list` `Array` must only contain `String`s.

**Returs:** A `GDOculusPlatformPromise` that will contain an `Array` of `Dictionaries` with information about each requested product. The promise will error if the request couldn't be fulfilled.

Example response:
``` json linenums="1"
[
    {
        "sku": "gems_pack_10",
        "name": "10 Gems",
        "description": "This pack of shiny gems sure is worth!",
        "formatted_price": "$9.99"
    },
    {
        "sku": "gems_pack_50",
        "name": "50 Gems",
        "description": "This pack of shiny gems sure is even more worth!",
        "formatted_price": "$39.99"
    }
]
```

/// details | Example
    type: example
``` gdscript linenums="1"
var sku_list : Array = ["gems_pack_10", "gems_pack_50"]

GDOculusPlatform.iap_get_products_by_sku(sku_list)\
.then(func(products : Array):
    for product in products:
        print("Product info: ", product)
)\
.error(func(products_err):
    print("Unable to retrieve products from SKUs: ", products_err)
)
```
///
////

## iap_consume_purchase
//// admonition | iap_consume_purchase(sku : `String`)
    type: abstract

Consumes a product with the given SKU.

**Returs:** A `GDOculusPlatformPromise` that will contain `true` as an argument if the request was successful. The promise will error if the product couldn't be consumed.

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.iap_consume_purchase("my_product_sku")\
.then(func(consumed : bool):
    print("Product consumed!")
)\
.error(func(consume_purchase_err):
    print("Unable to consume purchase: ", consume_purchase_err)
)
```
///
////

## iap_launch_checkout_flow
//// admonition | iap_launch_checkout_flow(sku : `String`)
    type: abstract

Launches a checkout flow for the product with the given SKU. The user will be able to complete the purchase or cancel it.

**Returs:** A `GDOculusPlatformPromise` that will contain a `Dictionary` with the product information if fulfilled. The promise will error if we couldn't launch the checkout flow.

Example response:
``` json linenums="1"
{
    "sku": "my_product_sku",
    "reporting_id": "154128782811",
    "purchase_str_id": "332574476951",
    "grant_time": 1683990516,
    "expiration_time": 0,
    "developer_payload": ""
}
```

/// admonition | Note
    type: warning

If the user doesn't purchase the product, the function **will not error**, instead to know if the user completed the purchase you should check if `purchase_str_id` is empty. It will **not** be empty if the user completed the purchase.
///

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.iap_launch_checkout_flow("my_product_sku")\
.then(func(product : Dictionaty):
    
    if product.purchase_str_id != "":
        print("User completed the purchase!")
    else:
        print("False alarm, the user didn't purchase the item.")

)\
.error(func(checkout_flow_err):
    print("Unable to launch checkout flow: ", checkout_flow_err)
)
```
///
////