# Functions - In-App Purchases
Related Oculus Platform documentation:

- [https://developer.oculus.com/documentation/native/ps-iap/](https://developer.oculus.com/documentation/native/ps-iap/)

------
## iap_get_viewer_purchases
//// admonition | iap_get_viewer_purchases()
    type: abstract

Requests all of the logged-in user purchases.

**Returns:** A `GDOculusPlatformPromise` that will contain a `Dictionary` - the `data` key will contain information about each purchase (both consumable and durable). The promise will error if the request couldn't be fulfilled.

Example response:

``` json linenums="1"
{
    "data": [
        {
            "sku": "durable_product_sku",
            "reporting_id": "154128782811",
            "purchase_str_id": "3325744768484514854951",
            "grant_time": 1683990516,
            "expiration_time": 0,
            "developer_payload": ""
        },
        {
            "sku": "consumable_product_sku",
            "reporting_id": "184128782822",
            "purchase_str_id": "8825744725484848476943",
            "grant_time": 1683990517,
            "expiration_time": 1684004517,
            "developer_payload": ""
        }
    ],
    "next_page_url": ""
}
```

More info about [next_page_url](/godot_oculus_platform/misc/about-previous_page_url-and-next_page_url/).

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.iap_get_viewer_purchases()\
.then(func(user_purchases : Dictionary):
    for purchase in user_purchases.data:
        print("Purchased at: ", purchase.grant_time)
)\
.error(func(user_purchases_err):
    print("Unable to retrieve user purchases: ", user_purchases_err)
)
```
///
////

## iap_get_products_by_sku
//// admonition | iap_get_products_by_sku(sku_list : `Array`)
    type: abstract

Requests product information of a list of SKUs. The `sku_list` `Array` must only contain `String`s.

**Returns:** A `GDOculusPlatformPromise` that will contain a `Dicitonary` - the `data` key will contain information about each product requested. The promise will error if the request couldn't be fulfilled.

Example response:

``` json linenums="1"
{
    "data": [
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
    ],
    "next_page_url": ""
}
```

More info about [next_page_url](/godot_oculus_platform/misc/about-previous_page_url-and-next_page_url/).

/// details | Example
    type: example
``` gdscript linenums="1"
var sku_list : Array = ["gems_pack_10", "gems_pack_50"]

GDOculusPlatform.iap_get_products_by_sku(sku_list)\
.then(func(prods : Dictionary):
    if not prods.next_page_url.is_empty():
        # Get next page
        pass
    
    for product in prods.data:
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

**Returns:** A `GDOculusPlatformPromise` that will contain `true` as an argument if the request was successful. The promise will error if the product couldn't be consumed.

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

**Returns:** A `GDOculusPlatformPromise` that will contain a `Dictionary` with the product information if fulfilled. The promise **will error if the user canceled the purchase** or if the checkout flow couldn't be launched.

Example response on purchase success:
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

Example error on canceled:
``` json linenums="1"
{
    "category": "user_canceled",
    "code": 0,
    "message": "The purchase has been canceled."
}
```

///// admonition | Note
    type: warning

Sometimes, after the user makes a purchase, the `iap_status` key from the [assetfile_get_list](/godot_oculus_platform/functions/asset-files/#assetfile_get_list) will still show up as `not-entitled` for some time. You will be able to download assets associated with the product, but the `iap_status` may take some time to update.
/////

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.iap_launch_checkout_flow("my_product_sku")\
.then(func(product : Dictionary):
    
    if product.purchase_str_id != "":
        print("User completed the purchase!")
    else:
        print("False alarm, the user didn't purchase the item.")

)\
.error(func(checkout_flow_err):
    if typeof(checkout_flow_err) == TYPE_DICTIONARY\
    and checkout_flow_err.has("category")\
    and checkout_flow_err.category == "user_canceled":
        print("The user canceled the purchase!")
    
    else:
        print("Unable to launch checkout flow: ", checkout_flow_err)
)
```
///
////
