# Godot Oculus Platform Documentation

## Introduction

This is the documentation site for the Godot Oculus Platform, an implementation of the Oculus Platform SDK for the [Godot Engine](https://godotengine.org).

Please note that both the documentation and the plugin itself are in development and may be incomplete.

Quick links:

- [Downloads](/godot_oculus_platform/download/)
- [Oculus Platform documentation](https://developer.oculus.com/documentation/native/ps-platform-intro/)

If you find an issue, please report it on the [GitHub issues page](https://github.com/decacis/godot_oculus_platform/issues).

-----

The following list tracks the supported functions from the Oculus Platform SDK:

- [x] [Platform initialization](/godot_oculus_platform/functions/initialization/)
    * [x] [initialize_android](/godot_oculus_platform/functions/initialization/#initialize_android)
    * [x] [initialize_android_async](/godot_oculus_platform/functions/initialization/#initialize_android_async)
- [x] [User](/godot_oculus_platform/functions/user/)
    * [x] [user_get_logged_in_user_id](/godot_oculus_platform/functions/user/#user_get_logged_in_user_id)
    * [x] [user_get_logged_in_user_locale](/godot_oculus_platform/functions/user/#user_get_logged_in_user_locale)
    * [x] [user_get_is_viewer_entitled](/godot_oculus_platform/functions/user/#user_get_is_viewer_entitled)
    * [x] [user_get_user](/godot_oculus_platform/functions/user/#user_get_user)
    * [x] [user_get_logged_in_user](/godot_oculus_platform/functions/user/#user_get_logged_in_user)
    * [x] [user_get_user_proof](/godot_oculus_platform/functions/user/#user_get_user_proof)
    * [x] [user_get_user_access_token](/godot_oculus_platform/functions/user/#user_get_user_access_token)
    * [x] [user_get_blocked_users](/godot_oculus_platform/functions/user/#user_get_blocked_users)
    * [x] [user_get_logged_in_user_friends](/godot_oculus_platform/functions/user/#user_get_logged_in_user_friends)
    * [x] [user_get_org_scoped_id](/godot_oculus_platform/functions/user/#user_get_org_scoped_id)
    * [x] [user_get_sdk_accounts](/godot_oculus_platform/functions/user/#user_get_sdk_accounts)
    * [x] [user_launch_block_flow](/godot_oculus_platform/functions/user/#user_launch_block_flow)
    * [x] [user_launch_unblock_flow](/godot_oculus_platform/functions/user/#user_launch_unblock_flow)
    * [x] [user_launch_friend_request_flow](/godot_oculus_platform/functions/user/#user_launch_friend_request_flow)
- [x] [Achievements](/godot_oculus_platform/functions/achievements/)
    * [x] [achievements_add_count](/godot_oculus_platform/functions/achievements/#achievements_add_count)
    * [x] [achievements_add_fields](/godot_oculus_platform/functions/achievements/#achievements_add_fields)
    * [x] [achievements_unlock](/godot_oculus_platform/functions/achievements/#achievements_unlock)
    * [x] [achievements_get_all_definitions](/godot_oculus_platform/functions/achievements/#achievements_get_all_definitions)
    * [x] [achievements_get_all_progress](/godot_oculus_platform/functions/achievements/#achievements_get_all_progress)
    * [x] [achievements_get_definitions_by_name](/godot_oculus_platform/functions/achievements/#achievements_get_definitions_by_name)
    * [x] [achievements_get_progress_by_name](/godot_oculus_platform/functions/achievements/#achievements_get_progress_by_name)
- [ ] In-App Purchases
    * [ ] iap_consume_purchase
    * [ ] iap_get_products_by_sku
    * [ ] iap_get_viewer_purchases
    * [ ] iap_get_viewer_purchases_durable_cache
    * [ ] iap_launch_checkout_flow
- [ ] Asset File
    * [ ] assetfile_get_list
    * [ ] assetfile_status
    * [ ] assetfile_status_by_id
    * [ ] assetfile_status_by_name
    * [ ] assetfile_download
    * [ ] assetfile_download_by_id
    * [ ] assetfile_download_by_name
    * [ ] assetfile_download_cancel
    * [ ] assetfile_download_cancel_by_id
    * [ ] assetfile_download_cancel_by_name
    * [ ] assetfile_delete
    * [ ] assetfile_delete_by_id
    * [ ] assetfile_delete_by_name