# Godot Oculus Platform Documentation

## Introduction

This is the documentation site for the Godot Oculus Platform, an implementation of the Oculus Platform SDK for the [Godot Engine](https://godotengine.org).

Please note that both the documentation and the plugin itself are in development and may be incomplete. 

If you find an issue, please report it on the [GitHub issues page](https://github.com/decacis/godot_oculus_platform/issues).

The following list tracks the supported functions from the Oculus Platform SDK:

- [x] [Platform initialization](/godot_oculus_platform/functions/initialization/)
    * [x] [initialize_android](/godot_oculus_platform/functions/initialization/#initialize_android)
    * [x] [initialize_android_async](/godot_oculus_platform/functions/initialization/#initialize_android_async)
- [x] [Users](/godot_oculus_platform/functions/users/)
    * [x] [get_is_viewer_entitled](/godot_oculus_platform/functions/users/#get_is_viewer_entitled)
    * [x] [get_user](/godot_oculus_platform/functions/users/#get_user)
    * [x] [get_logged_in_user](/godot_oculus_platform/functions/users/#get_logged_in_user)
    * [x] [get_user_proof](/godot_oculus_platform/functions/users/#get_user_proof)
    * [x] [get_user_access_token](/godot_oculus_platform/functions/users/#get_user_access_token)
    * [x] [get_blocked_users](/godot_oculus_platform/functions/users/#get_blocked_users)
    * [x] [get_logged_in_user_friends](/godot_oculus_platform/functions/users/#get_logged_in_user_friends)
    * [x] [get_org_scoped_id](/godot_oculus_platform/functions/users/#get_org_scoped_id)
    * [x] [get_sdk_accounts](/godot_oculus_platform/functions/users/#get_sdk_accounts)
    * [x] [launch_block_flow](/godot_oculus_platform/functions/users/#launch_block_flow)
    * [x] [launch_unblock_flow](/godot_oculus_platform/functions/users/#launch_unblock_flow)
    * [x] [launch_friend_request_flow](/godot_oculus_platform/functions/users/#launch_friend_request_flow)
- [ ] Achievements
    * [ ] achievements_add_count
    * [ ] achievements_add_fields
    * [ ] achievements_get_all_definitions
    * [ ] achievements_get_all_progress
    * [ ] achievements_get_definitions_by_name
    * [ ] achievements_get_progress_by_name
    * [ ] achievements_unlock