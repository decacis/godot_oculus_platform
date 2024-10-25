#ifndef __ANDROID__
#define OVRP_PUBLIC_FUNCTION OVRPL_PUBLIC_FUNCTION
#endif

#include <godot_oculus_platform.h>
#include <godot_cpp/classes/json.hpp>
#include <godot_cpp/core/class_db.hpp>

#define OVRID_SIZE 21

#ifdef __ANDROID__
static JavaVM *jvm;
static jobject jactivity;
#endif

using namespace godot;

GDOculusPlatform *GDOculusPlatform::singleton = nullptr;

void GDOculusPlatform::_bind_methods() {
	ClassDB::bind_method(D_METHOD("pump_messages"), &GDOculusPlatform::pump_messages);

	// INITIALIZATION
	ClassDB::bind_method(D_METHOD("is_platform_initialized"), &GDOculusPlatform::is_platform_initialized);
	ClassDB::bind_method(D_METHOD("initialize_platform", "app_id", "options"), &GDOculusPlatform::initialize_platform, DEFVAL(Dictionary()));
	ClassDB::bind_method(D_METHOD("initialize_platform_async", "app_id"), &GDOculusPlatform::initialize_platform_async);

	// USER
	ClassDB::bind_method(D_METHOD("user_get_logged_in_user_id"), &GDOculusPlatform::user_get_logged_in_user_id);
	ClassDB::bind_method(D_METHOD("user_get_logged_in_user_locale"), &GDOculusPlatform::user_get_logged_in_user_locale);
	ClassDB::bind_method(D_METHOD("user_get_is_viewer_entitled"), &GDOculusPlatform::user_get_is_viewer_entitled);
	ClassDB::bind_method(D_METHOD("user_get_logged_in_user"), &GDOculusPlatform::user_get_logged_in_user);
	ClassDB::bind_method(D_METHOD("user_get_user", "user_id"), &GDOculusPlatform::user_get_user);
	ClassDB::bind_method(D_METHOD("user_get_user_proof"), &GDOculusPlatform::user_get_user_proof);
	ClassDB::bind_method(D_METHOD("user_get_user_access_token"), &GDOculusPlatform::user_get_user_access_token);
	ClassDB::bind_method(D_METHOD("user_get_blocked_users"), &GDOculusPlatform::user_get_blocked_users);
	ClassDB::bind_method(D_METHOD("user_get_logged_in_user_friends"), &GDOculusPlatform::user_get_logged_in_user_friends);
	ClassDB::bind_method(D_METHOD("user_get_org_scoped_id", "user_id"), &GDOculusPlatform::user_get_org_scoped_id);
	ClassDB::bind_method(D_METHOD("user_get_sdk_accounts"), &GDOculusPlatform::user_get_sdk_accounts);
	ClassDB::bind_method(D_METHOD("user_launch_block_flow", "user_id"), &GDOculusPlatform::user_launch_block_flow);
	ClassDB::bind_method(D_METHOD("user_launch_unblock_flow", "user_id"), &GDOculusPlatform::user_launch_unblock_flow);
	ClassDB::bind_method(D_METHOD("user_launch_friend_request_flow", "user_id"), &GDOculusPlatform::user_launch_friend_request_flow);

	// ACHIEVEMENTS
	ClassDB::bind_method(D_METHOD("achievements_add_count", "achievement_name", "count"), &GDOculusPlatform::achievements_add_count);
	ClassDB::bind_method(D_METHOD("achievements_add_fields", "achievement_name", "fields"), &GDOculusPlatform::achievements_add_fields);
	ClassDB::bind_method(D_METHOD("achievements_unlock", "achievement_name"), &GDOculusPlatform::achievements_unlock);
	ClassDB::bind_method(D_METHOD("achievements_get_all_definitions"), &GDOculusPlatform::achievements_get_all_definitions);
	ClassDB::bind_method(D_METHOD("achievements_get_all_progress"), &GDOculusPlatform::achievements_get_all_progress);
	ClassDB::bind_method(D_METHOD("achievements_get_definitions_by_name", "achievement_names"), &GDOculusPlatform::achievements_get_definitions_by_name);
	ClassDB::bind_method(D_METHOD("achievements_get_progress_by_name", "achievement_names"), &GDOculusPlatform::achievements_get_progress_by_name);

	// IAP
	ClassDB::bind_method(D_METHOD("iap_get_viewer_purchases"), &GDOculusPlatform::iap_get_viewer_purchases);
	ClassDB::bind_method(D_METHOD("iap_get_products_by_sku", "sku_list"), &GDOculusPlatform::iap_get_products_by_sku);
	ClassDB::bind_method(D_METHOD("iap_consume_purchase", "sku"), &GDOculusPlatform::iap_consume_purchase);
	ClassDB::bind_method(D_METHOD("iap_launch_checkout_flow", "sku"), &GDOculusPlatform::iap_launch_checkout_flow);

	// ASSET FILE
	ClassDB::bind_method(D_METHOD("assetfile_get_list"), &GDOculusPlatform::assetfile_get_list);
	ClassDB::bind_method(D_METHOD("assetfile_status_by_id", "asset_id"), &GDOculusPlatform::assetfile_status_by_id);
	ClassDB::bind_method(D_METHOD("assetfile_status_by_name", "asset_name"), &GDOculusPlatform::assetfile_status_by_name);
	ClassDB::bind_method(D_METHOD("assetfile_download_by_id", "asset_id"), &GDOculusPlatform::assetfile_download_by_id);
	ClassDB::bind_method(D_METHOD("assetfile_download_by_name", "asset_name"), &GDOculusPlatform::assetfile_download_by_name);
	ClassDB::bind_method(D_METHOD("assetfile_download_cancel_by_id", "asset_id"), &GDOculusPlatform::assetfile_download_cancel_by_id);
	ClassDB::bind_method(D_METHOD("assetfile_download_cancel_by_name", "asset_name"), &GDOculusPlatform::assetfile_download_cancel_by_name);
	ClassDB::bind_method(D_METHOD("assetfile_delete_by_id", "asset_id"), &GDOculusPlatform::assetfile_delete_by_id);
	ClassDB::bind_method(D_METHOD("assetfile_delete_by_name", "asset_name"), &GDOculusPlatform::assetfile_delete_by_name);

	// LEADERBOARD
	ClassDB::bind_method(D_METHOD("leaderboard_get", "leaderboard_name"), &GDOculusPlatform::leaderboard_get);
	ClassDB::bind_method(D_METHOD("leaderboard_get_entries", "leaderboard_name", "limit", "filter", "start_at"), &GDOculusPlatform::leaderboard_get_entries);
	ClassDB::bind_method(D_METHOD("leaderboard_get_entries_after_rank", "leaderboard_name", "limit", "start_at"), &GDOculusPlatform::leaderboard_get_entries_after_rank);
	ClassDB::bind_method(D_METHOD("leaderboard_get_entries_by_ids", "leaderboard_name", "limit", "start_at", "user_ids"), &GDOculusPlatform::leaderboard_get_entries_by_ids);
	ClassDB::bind_method(D_METHOD("leaderboard_write_entry", "leaderboard_name", "score", "force_update", "extra"), &GDOculusPlatform::leaderboard_write_entry);

	// ABUSE REPORT
	ClassDB::bind_method(D_METHOD("abuse_report_request_handled", "report_request_response"), &GDOculusPlatform::abuse_report_request_handled);

	// APPLICATION
	ClassDB::bind_method(D_METHOD("application_get_version"), &GDOculusPlatform::application_get_version);
	ClassDB::bind_method(D_METHOD("application_launch_other_app", "app_id", "deeplink_options"), &GDOculusPlatform::application_launch_other_app, DEFVAL(Dictionary()));
	ClassDB::bind_method(D_METHOD("application_get_launch_details"), &GDOculusPlatform::application_get_launch_details);
	ClassDB::bind_method(D_METHOD("application_start_app_download"), &GDOculusPlatform::application_start_app_download);
	ClassDB::bind_method(D_METHOD("application_check_app_download_progress"), &GDOculusPlatform::application_check_app_download_progress);
	ClassDB::bind_method(D_METHOD("application_cancel_app_download"), &GDOculusPlatform::application_cancel_app_download);
	ClassDB::bind_method(D_METHOD("application_install_app_update_and_relaunch", "deeplink_options"), &GDOculusPlatform::application_install_app_update_and_relaunch, DEFVAL(Dictionary()));

	// CHALLENGES
	ClassDB::bind_method(D_METHOD("challenges_get", "challenge_id"), &GDOculusPlatform::challenges_get);
	ClassDB::bind_method(D_METHOD("challenges_get_list", "limit", "challenge_options"), &GDOculusPlatform::challenges_get_list, DEFVAL(10), DEFVAL(Dictionary()));
	ClassDB::bind_method(D_METHOD("challenges_get_entries", "challenge_id", "limit", "filter", "start_at"), &GDOculusPlatform::challenges_get_entries);
	ClassDB::bind_method(D_METHOD("challenges_get_entries_after_rank", "challenge_id", "limit", "start_at"), &GDOculusPlatform::challenges_get_entries_after_rank);
	ClassDB::bind_method(D_METHOD("challenges_get_entries_by_ids", "challenge_id", "limit", "start_at", "user_ids"), &GDOculusPlatform::challenges_get_entries_by_ids);
	ClassDB::bind_method(D_METHOD("challenges_join", "challenge_id"), &GDOculusPlatform::challenges_join);
	ClassDB::bind_method(D_METHOD("challenges_leave", "challenge_id"), &GDOculusPlatform::challenges_leave);
	ClassDB::bind_method(D_METHOD("challenges_decline_invite", "challenge_id"), &GDOculusPlatform::challenges_decline_invite);

	// GROUP PRESENCE
	ClassDB::bind_method(D_METHOD("grouppresence_clear"), &GDOculusPlatform::grouppresence_clear);
	ClassDB::bind_method(D_METHOD("grouppresence_send_invites", "user_ids"), &GDOculusPlatform::grouppresence_send_invites);
	ClassDB::bind_method(D_METHOD("grouppresence_set", "group_presence_options"), &GDOculusPlatform::grouppresence_set);
	ClassDB::bind_method(D_METHOD("grouppresence_set_deeplink_message_override", "deeplink_message"), &GDOculusPlatform::grouppresence_set_deeplink_message_override);
	ClassDB::bind_method(D_METHOD("grouppresence_set_destination", "api_name"), &GDOculusPlatform::grouppresence_set_destination);
	ClassDB::bind_method(D_METHOD("grouppresence_set_is_joinable", "is_joinable"), &GDOculusPlatform::grouppresence_set_is_joinable);
	ClassDB::bind_method(D_METHOD("grouppresence_set_lobby_session", "id"), &GDOculusPlatform::grouppresence_set_lobby_session);
	ClassDB::bind_method(D_METHOD("grouppresence_set_match_session", "id"), &GDOculusPlatform::grouppresence_set_match_session);
	ClassDB::bind_method(D_METHOD("grouppresence_get_invitable_users", "options"), &GDOculusPlatform::grouppresence_get_invitable_users, DEFVAL(Dictionary()));
	ClassDB::bind_method(D_METHOD("grouppresence_get_sent_invites"), &GDOculusPlatform::grouppresence_get_sent_invites);
	ClassDB::bind_method(D_METHOD("grouppresence_launch_invite_panel", "options"), &GDOculusPlatform::grouppresence_launch_invite_panel, DEFVAL(Dictionary()));
	ClassDB::bind_method(D_METHOD("grouppresence_launch_multiplayer_error_dialog", "error_key"), &GDOculusPlatform::grouppresence_launch_multiplayer_error_dialog);
	ClassDB::bind_method(D_METHOD("grouppresence_launch_rejoin_dialog", "lobby_session_id", "match_session_id", "destination_api_name"), &GDOculusPlatform::grouppresence_launch_rejoin_dialog);
	ClassDB::bind_method(D_METHOD("grouppresence_launch_roster_panel", "options"), &GDOculusPlatform::grouppresence_launch_roster_panel, DEFVAL(Dictionary()));

	// MEDIA
	ClassDB::bind_method(D_METHOD("media_share_to_facebook", "post_text_suggestion", "file_path", "content_type"), &GDOculusPlatform::media_share_to_facebook);

	// USER AGE CATEGORY
	ClassDB::bind_method(D_METHOD("useragecategory_get"), &GDOculusPlatform::useragecategory_get);
	ClassDB::bind_method(D_METHOD("useragecategory_report", "app_age_category"), &GDOculusPlatform::useragecategory_report);

	// DEVICE APPLICATION INTEGRITY
	ClassDB::bind_method(D_METHOD("deviceappintegrity_get_integrity_token", "challenge_nonce"), &GDOculusPlatform::deviceappintegrity_get_integrity_token);

	// COWATCHING
	ClassDB::bind_method(D_METHOD("cowatch_get_presenter_data"), &GDOculusPlatform::cowatch_get_presenter_data);
	ClassDB::bind_method(D_METHOD("cowatch_get_viewers_data"), &GDOculusPlatform::cowatch_get_viewers_data);
	ClassDB::bind_method(D_METHOD("cowatch_is_in_session"), &GDOculusPlatform::cowatch_is_in_session);
	ClassDB::bind_method(D_METHOD("cowatch_join_session"), &GDOculusPlatform::cowatch_join_session);
	ClassDB::bind_method(D_METHOD("cowatch_launch_invite_dialog"), &GDOculusPlatform::cowatch_launch_invite_dialog);
	ClassDB::bind_method(D_METHOD("cowatch_leave_session"), &GDOculusPlatform::cowatch_leave_session);
	ClassDB::bind_method(D_METHOD("cowatch_request_to_present"), &GDOculusPlatform::cowatch_request_to_present);
	ClassDB::bind_method(D_METHOD("cowatch_set_presenter_data", "video_title", "presenter_data"), &GDOculusPlatform::cowatch_set_presenter_data);
	ClassDB::bind_method(D_METHOD("cowatch_set_viewer_data", "viewer_data"), &GDOculusPlatform::cowatch_set_viewer_data);

	// SIGNALS

	ADD_SIGNAL(MethodInfo("unhandled_message", PropertyInfo(Variant::DICTIONARY, "message")));
	ADD_SIGNAL(MethodInfo("assetfile_download_update", PropertyInfo(Variant::DICTIONARY, "download_info")));
	ADD_SIGNAL(MethodInfo("assetfile_download_finished", PropertyInfo(Variant::STRING, "asset_id")));
	ADD_SIGNAL(MethodInfo("abuse_report_form_requested"));
	ADD_SIGNAL(MethodInfo("app_launch_intent_changed", PropertyInfo(Variant::STRING, "intent_type")));
	ADD_SIGNAL(MethodInfo("cowatch_api_not_ready", PropertyInfo(Variant::STRING, "message")));
	ADD_SIGNAL(MethodInfo("cowatch_api_ready", PropertyInfo(Variant::STRING, "message")));
	ADD_SIGNAL(MethodInfo("cowatch_initialized", PropertyInfo(Variant::STRING, "message")));
	ADD_SIGNAL(MethodInfo("cowatch_presenter_data_changed", PropertyInfo(Variant::STRING, "message")));
	ADD_SIGNAL(MethodInfo("cowatch_session_started", PropertyInfo(Variant::STRING, "message")));
	ADD_SIGNAL(MethodInfo("cowatch_session_stopped", PropertyInfo(Variant::STRING, "message")));
	ADD_SIGNAL(MethodInfo("cowatch_viewers_data_changed", PropertyInfo(Variant::DICTIONARY, "viewer_data_changed")));

	// ENUMS

	BIND_ENUM_CONSTANT(LEADERBOARD_FILTER_TYPE_NONE); // 0
	BIND_ENUM_CONSTANT(LEADERBOARD_FILTER_TYPE_FRIENDS); // 1

	BIND_ENUM_CONSTANT(LEADERBOARD_START_AT_TOP); // 0
	BIND_ENUM_CONSTANT(LEADERBOARD_START_AT_CENTERED_ON_VIEWER); // 1
	BIND_ENUM_CONSTANT(LEADERBOARD_START_AT_CENTERED_ON_VIEWER_OR_TOP); // 2

	BIND_ENUM_CONSTANT(REPORT_REQUEST_HANDLED); // 1
	BIND_ENUM_CONSTANT(REPORT_REQUEST_UNHANDLED); // 2

	BIND_ENUM_CONSTANT(CHALLENGE_VISIBILITY_VIEWER_ALL_VISIBLE); // 1
	BIND_ENUM_CONSTANT(CHALLENGE_VISIBILITY_VIEWER_PARTICIPATING); // 2
	BIND_ENUM_CONSTANT(CHALLENGE_VISIBILITY_VIEWER_INVITED); // 3
	BIND_ENUM_CONSTANT(CHALLENGE_VISIBILITY_VIEWER_PARTICIPATING_OR_INVITED); // 4

	BIND_ENUM_CONSTANT(CHALLENGE_VISIBILITY_INVITE_ONLY); // 1
	BIND_ENUM_CONSTANT(CHALLENGE_VISIBILITY_PUBLIC); // 2
	BIND_ENUM_CONSTANT(CHALLENGE_VISIBILITY_PRIVATE); // 3

	BIND_ENUM_CONSTANT(MULTIPLAYER_ERR_KEY_DEST_UNAVAILABLE); // 1
	BIND_ENUM_CONSTANT(MULTIPLAYER_ERR_KEY_DLC_REQUIRED); // 2
	BIND_ENUM_CONSTANT(MULTIPLAYER_ERR_KEY_GENERAL); // 3
	BIND_ENUM_CONSTANT(MULTIPLAYER_ERR_KEY_GROUP_FULL); // 4
	BIND_ENUM_CONSTANT(MULTIPLAYER_ERR_KEY_INVITER_NOT_JOINABLE); // 5
	BIND_ENUM_CONSTANT(MULTIPLAYER_ERR_KEY_LVL_NOT_HIGH_ENOUGH); // 6
	BIND_ENUM_CONSTANT(MULTIPLAYER_ERR_KEY_LVL_NOT_UNLOCKED); // 7
	BIND_ENUM_CONSTANT(MULTIPLAYER_ERR_KEY_NETWORK_TIMEOUT); // 8
	BIND_ENUM_CONSTANT(MULTIPLAYER_ERR_KEY_NO_LONGER_AVAILABLE); // 9
	BIND_ENUM_CONSTANT(MULTIPLAYER_ERR_KEY_UPDATE_REQUIRED); // 10
	BIND_ENUM_CONSTANT(MULTIPLAYER_ERR_KEY_TUTORIAL_REQUIRED); // 11

	BIND_ENUM_CONSTANT(MEDIA_CONTENT_TYPE_PHOTO); // 1

	BIND_ENUM_CONSTANT(ACCOUNTAGECATEGORY_UNKNOWN); // 0
	BIND_ENUM_CONSTANT(ACCOUNTAGECATEGORY_CHILD); // 1
	BIND_ENUM_CONSTANT(ACCOUNTAGECATEGORY_TEEN); // 2
	BIND_ENUM_CONSTANT(ACCOUNTAGECATEGORY_ADULT); // 3

	BIND_ENUM_CONSTANT(APPAGECATEGORY_CHILD); // 1
	BIND_ENUM_CONSTANT(APPAGECATEGORY_NON_CHILD); // 2
}

GDOculusPlatform *GDOculusPlatform::get_singleton() { return singleton; }

GDOculusPlatform::GDOculusPlatform() {
	ERR_FAIL_COND(singleton != nullptr);
	singleton = this;
}

GDOculusPlatform::~GDOculusPlatform() {
	ERR_FAIL_COND(singleton != this);
	singleton = nullptr;
}

///////////////////////////////////////////////////
// TODO: remove it if all functions are available
///////////////////////////////////////////////////
Ref<GDOculusPlatformPromise> _empty_func_helper() {
	Ref<GDOculusPlatformPromise> promise = memnew(GDOculusPlatformPromise(0));
	ERR_FAIL_V_MSG(promise, "Godot Oculus Platform only works with the Meta Quest (android).");

	return promise;
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// INTERNAL METHODS
/////////////////////////////////////////////////

bool GDOculusPlatform::_try_connecting_process() {
	if (!progress_connected) {
		Error resp = Engine::get_singleton()->get_main_loop()->connect("process_frame", Callable(this, "pump_messages"));
		ERR_FAIL_COND_V_MSG(resp != OK, false, "[GDOP] Unable to connect pump_messages to process_frame signal.");
		progress_connected = true;
	}
	return progress_connected;
}

/// Retrieve existing promise from ID.
bool GDOculusPlatform::_get_promise(uint64_t p_promise_id, Ref<GDOculusPlatformPromise> &p_promise) {
	for (auto &p : _promises) {
		if (p->has_id(p_promise_id)) {
			p_promise = p;
			return true;
		}
	}

	ERR_FAIL_V_MSG(false, vformat("[GDOP] Unable to get promise with ID: %s", p_promise_id));
}

bool GDOculusPlatform::_fulfill_promise(uint64_t p_promise_id, const Array &val) {
	for (auto &p : _promises) {
		if (p->has_id(p_promise_id)) {
			p->fulfill(val);
			_promises.erase(p);
			return true;
		}
	}

	ERR_FAIL_V_MSG(false, vformat("[GDOP] Unable to fulfill promise with ID: %s", p_promise_id));
}

bool GDOculusPlatform::_reject_promise(uint64_t p_promise_id, const Array &val) {
	for (auto &p : _promises) {
		if (p->has_id(p_promise_id)) {
			p->reject(val);
			_promises.erase(p);
			return true;
		}
	}

	ERR_FAIL_V_MSG(false, vformat("[GDOP] Unable to reject promise with ID: %s", p_promise_id));
}

/// Rejects all promises in the rejection queue.
void GDOculusPlatform::_reject_promises() {
	for (int i = _promises_to_reject.size() - 1; i > -1; i--) {
		Ref<GDOculusPlatformPromise> temp_promise = _promises_to_reject.get(i);
		_promises_to_reject.remove_at(i);

		temp_promise->reject(temp_promise->saved_rejection_response);
	}
}

/// Fulfills all promises in the rejection queue.
void GDOculusPlatform::_fulfill_promises() {
	for (int i = _promises_to_fulfill.size() - 1; i > -1; i--) {
		Ref<GDOculusPlatformPromise> temp_promise = _promises_to_fulfill.get(i);
		_promises_to_fulfill.remove_at(i);

		temp_promise->fulfill(temp_promise->saved_fulfill_response);
	}
}

/// Returns a unique promise id. Only used for promises that should be rejected straight away.
uint64_t GDOculusPlatform::_get_reject_promise_id() {
	_last_promise_rejected_id += 1;
	return _last_promise_rejected_id;
}

/// Returns a unique promise id. Only used for promises that should be fulfilled straight away.
uint64_t GDOculusPlatform::_get_fulfill_promise_id() {
	_last_promise_fulfilled_id += 1;
	return _last_promise_fulfilled_id;
}

/// Checks the OVR messages queue and handles them according to their type.
void GDOculusPlatform::pump_messages() {
	_fulfill_promises();
	_reject_promises();

	ovrMessageHandle message = nullptr;

	// Process messages
	while ((message = ovr_PopMessage()) != nullptr) {
		switch (ovr_Message_GetType(message)) {
			case ovrMessage_PlatformInitializeAndroidAsynchronous:
			case ovrMessage_PlatformInitializeWindowsAsynchronous:
				_process_initialize_platform_async(message);
				break;

			case ovrMessage_Entitlement_GetIsViewerEntitled:
				_process_user_get_is_viewer_entitled(message);
				break;

			case ovrMessage_User_GetLoggedInUser:
			case ovrMessage_User_Get:
				_process_user_get_logged_in_user(message);
				break;

			case ovrMessage_User_GetUserProof:
				_process_user_get_user_proof(message);
				break;

			case ovrMessage_User_GetAccessToken:
				_process_user_get_user_access_token(message);
				break;

			case ovrMessage_User_GetBlockedUsers:
				_process_user_get_blocked_users(message);
				break;

			case ovrMessage_User_GetNextBlockedUserArrayPage:
				_process_user_get_blocked_users(message);
				break;

			case ovrMessage_User_GetLoggedInUserFriends:
				_process_user_get_next_array_page(message);
				break;

			case ovrMessage_User_GetNextUserArrayPage:
				_process_user_get_next_array_page(message);
				break;

			case ovrMessage_User_GetOrgScopedID:
				_process_user_get_org_scoped_id(message);
				break;

			case ovrMessage_User_GetSdkAccounts:
				_process_user_get_sdk_accounts(message);
				break;

			case ovrMessage_User_LaunchBlockFlow:
				_process_user_launch_block_flow(message);
				break;

			case ovrMessage_User_LaunchUnblockFlow:
				_process_user_launch_unblock_flow(message);
				break;

			case ovrMessage_User_LaunchFriendRequestFlow:
				_process_user_launch_friend_request_flow(message);
				break;

			case ovrMessage_Achievements_AddCount:
				_process_achievements_update(message);
				break;

			case ovrMessage_Achievements_AddFields:
				_process_achievements_update(message);
				break;

			case ovrMessage_Achievements_Unlock:
				_process_achievements_update(message);
				break;

			case ovrMessage_Achievements_GetAllDefinitions:
				_process_achievements_definitions(message);
				break;

			case ovrMessage_Achievements_GetDefinitionsByName:
				_process_achievements_definitions(message);
				break;

			case ovrMessage_Achievements_GetNextAchievementDefinitionArrayPage:
				_process_achievements_definitions(message);
				break;

			case ovrMessage_Achievements_GetAllProgress:
				_process_achievements_progress(message);
				break;

			case ovrMessage_Achievements_GetProgressByName:
				_process_achievements_progress(message);
				break;

			case ovrMessage_Achievements_GetNextAchievementProgressArrayPage:
				_process_achievements_progress(message);
				break;

			case ovrMessage_IAP_GetViewerPurchases:
				_process_iap_viewer_purchases(message);
				break;

			case ovrMessage_IAP_GetViewerPurchasesDurableCache:
				_process_iap_viewer_purchases(message);
				break;

			case ovrMessage_IAP_GetNextPurchaseArrayPage:
				_process_iap_viewer_purchases(message);
				break;

			case ovrMessage_IAP_GetProductsBySKU:
				_process_iap_products(message);
				break;

			case ovrMessage_IAP_GetNextProductArrayPage:
				_process_iap_products(message);
				break;

			case ovrMessage_IAP_ConsumePurchase:
				_process_iap_consume_purchase(message);
				break;

			case ovrMessage_IAP_LaunchCheckoutFlow:
				_process_iap_launch_checkout_flow(message);
				break;

			case ovrMessage_AssetFile_GetList:
				_process_assetfile_get_list(message);
				break;

			case ovrMessage_AssetFile_StatusById:
				_process_assetfile_get_status(message);
				break;

			case ovrMessage_AssetFile_StatusByName:
				_process_assetfile_get_status(message);
				break;

			case ovrMessage_AssetFile_DownloadById:
				_process_assetfile_download(message);
				break;

			case ovrMessage_AssetFile_DownloadByName:
				_process_assetfile_download(message);
				break;

			case ovrMessage_AssetFile_DownloadCancelById:
				_process_assetfile_download_cancel(message);
				break;

			case ovrMessage_AssetFile_DownloadCancelByName:
				_process_assetfile_download_cancel(message);
				break;

			case ovrMessage_AssetFile_DeleteById:
				_process_assetfile_delete(message);
				break;

			case ovrMessage_AssetFile_DeleteByName:
				_process_assetfile_delete(message);
				break;

			case ovrMessage_Notification_AssetFile_DownloadUpdate:
				_handle_download_update(message);
				break;

			case ovrMessage_Leaderboard_Get:
				_process_leaderboard_get(message);
				break;

			case ovrMessage_Leaderboard_GetNextLeaderboardArrayPage:
				_process_leaderboard_get(message);
				break;

			case ovrMessage_Leaderboard_GetEntries:
				_process_leaderboard_get_entries(message);
				break;

			case ovrMessage_Leaderboard_GetEntriesByIds:
				_process_leaderboard_get_entries(message);
				break;

			case ovrMessage_Leaderboard_GetEntriesAfterRank:
				_process_leaderboard_get_entries(message);
				break;

			case ovrMessage_Leaderboard_GetPreviousEntries:
				_process_leaderboard_get_entries(message);
				break;

			case ovrMessage_Leaderboard_GetNextEntries:
				_process_leaderboard_get_entries(message);
				break;

			case ovrMessage_Leaderboard_WriteEntry:
				_process_leaderboard_write_entry(message);
				break;

			case ovrMessage_Leaderboard_WriteEntryWithSupplementaryMetric:
				_process_leaderboard_write_entry(message);
				break;

			case ovrMessage_Notification_AbuseReport_ReportButtonPressed:
				emit_signal("abuse_report_form_requested");
				break;

			case ovrMessage_AbuseReport_ReportRequestHandled:
				_process_abuse_report_handled(message);
				break;

			case ovrMessage_Application_GetVersion:
				_process_application_get_version(message);
				break;

			case ovrMessage_Application_LaunchOtherApp:
				_process_application_launch_other_app(message);
				break;

			case ovrMessage_Application_StartAppDownload:
				_process_application_start_app_download(message);
				break;

			case ovrMessage_Application_CheckAppDownloadProgress:
				_process_application_check_app_download_progress(message);
				break;

			case ovrMessage_Application_CancelAppDownload:
				_process_application_start_app_download(message);
				break;

			case ovrMessage_Application_InstallAppUpdateAndRelaunch:
				_process_application_start_app_download(message);
				break;

			case ovrMessage_Notification_ApplicationLifecycle_LaunchIntentChanged:
				emit_signal("app_launch_intent_changed", String(ovr_Message_GetString(message)));
				break;

			case ovrMessage_Challenges_Get:
				_process_challenges_get(message);
				break;

			case ovrMessage_Challenges_GetList:
				_process_challenges_get_list(message);
				break;

			case ovrMessage_Challenges_GetNextChallenges:
				_process_challenges_get_list(message);
				break;

			case ovrMessage_Challenges_GetPreviousChallenges:
				_process_challenges_get_list(message);
				break;

			case ovrMessage_Challenges_GetEntries:
				_process_challenges_get_entries(message);
				break;

			case ovrMessage_Challenges_GetEntriesAfterRank:
				_process_challenges_get_entries(message);
				break;

			case ovrMessage_Challenges_GetEntriesByIds:
				_process_challenges_get_entries(message);
				break;

			case ovrMessage_Challenges_GetPreviousEntries:
				_process_challenges_get_entries(message);
				break;

			case ovrMessage_Challenges_GetNextEntries:
				_process_challenges_get_entries(message);
				break;

			case ovrMessage_Challenges_Join:
				_process_challenges_get(message);
				break;

			case ovrMessage_Challenges_Leave:
				_process_challenges_get(message);
				break;

			case ovrMessage_Challenges_DeclineInvite:
				_process_challenges_get(message);
				break;

			case ovrMessage_GroupPresence_Clear:
				_process_groupresence_no_payload(message);
				break;

			case ovrMessage_GroupPresence_Set:
				_process_groupresence_no_payload(message);
				break;

			case ovrMessage_GroupPresence_SetDeeplinkMessageOverride:
				_process_groupresence_no_payload(message);
				break;

			case ovrMessage_GroupPresence_SetDestination:
				_process_groupresence_no_payload(message);
				break;

			case ovrMessage_GroupPresence_SetIsJoinable:
				_process_groupresence_no_payload(message);
				break;

			case ovrMessage_GroupPresence_SetLobbySession:
				_process_groupresence_no_payload(message);
				break;

			case ovrMessage_GroupPresence_SetMatchSession:
				_process_groupresence_no_payload(message);
				break;

			case ovrMessage_GroupPresence_LaunchMultiplayerErrorDialog:
				_process_groupresence_no_payload(message);
				break;

			case ovrMessage_GroupPresence_LaunchRosterPanel:
				_process_groupresence_no_payload(message);
				break;

			case ovrMessage_GroupPresence_SendInvites:
				_process_groupresence_send_invites(message);
				break;

			case ovrMessage_GroupPresence_GetSentInvites:
				_handle_process_app_invite_array(message);
				break;

			case ovrMessage_GroupPresence_GetNextApplicationInviteArrayPage:
				_handle_process_app_invite_array(message);
				break;

			case ovrMessage_GroupPresence_GetInvitableUsers:
				_process_user_get_next_array_page(message);
				break;

			case ovrMessage_GroupPresence_LaunchInvitePanel:
				_process_groupresence_launch_invite_panel(message);
				break;

			case ovrMessage_GroupPresence_LaunchRejoinDialog:
				_process_groupresence_launch_rejoin_panel(message);
				break;

			case ovrMessage_Media_ShareToFacebook:
				_process_media_share_to_facebook(message);
				break;

			case ovrMessage_UserAgeCategory_Get:
				_process_useragecategory_get(message);
				break;

			case ovrMessage_UserAgeCategory_Report:
				_process_useragecategory_report(message);
				break;

			case ovrMessage_DeviceApplicationIntegrity_GetIntegrityToken:
				_process_deviceappintegrity_get_integrity_token(message);
				break;

			case ovrMessage_Cowatching_GetPresenterData:
				_process_cowatch_get_presenter_data(message);
				break;

			case ovrMessage_Cowatching_GetViewersData:
				_process_cowatch_get_viewers_data(message);
				break;

			case ovrMessage_Cowatching_IsInSession:
				_process_cowatch_is_in_session(message);
				break;

			case ovrMessage_Cowatching_JoinSession:
				_process_cowatch_join_session(message);
				break;

			case ovrMessage_Cowatching_LaunchInviteDialog:
				_process_cowatch_launch_invite_dialog(message);
				break;

			case ovrMessage_Cowatching_LeaveSession:
				_process_cowatch_leave_session(message);
				break;

			case ovrMessage_Cowatching_RequestToPresent:
				_process_cowatch_request_to_present(message);
				break;

			case ovrMessage_Cowatching_ResignFromPresenting:
				_process_cowatch_resign_from_presenting(message);
				break;

			case ovrMessage_Cowatching_SetPresenterData:
				_process_cowatch_set_presenter_data(message);
				break;

			case ovrMessage_Cowatching_SetViewerData:
				_process_cowatch_set_viewer_data(message);
				break;

			case ovrMessage_Notification_Cowatching_ApiNotReady:
				emit_signal("cowatch_api_not_ready", String(ovr_Message_GetString(message)));
				break;

			case ovrMessage_Notification_Cowatching_ApiReady:
				emit_signal("cowatch_api_ready", String(ovr_Message_GetString(message)));
				break;

			case ovrMessage_Notification_Cowatching_Initialized:
				emit_signal("cowatch_initialized", String(ovr_Message_GetString(message)));
				break;

			case ovrMessage_Notification_Cowatching_PresenterDataChanged:
				emit_signal("cowatch_presenter_data_changed", String(ovr_Message_GetString(message)));
				break;

			case ovrMessage_Notification_Cowatching_SessionStarted:
				emit_signal("cowatch_session_started", String(ovr_Message_GetString(message)));
				break;

			case ovrMessage_Notification_Cowatching_SessionStopped:
				emit_signal("cowatch_session_stopped", String(ovr_Message_GetString(message)));
				break;

			case ovrMessage_Notification_Cowatching_ViewersDataChanged:
				_process_cowatch_viewer_data_changed(message);
				break;

			default:
				_handle_unhandled_message(message);
		}

		ovr_FreeMessage(message);
	}
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// PLATFORM INITIALIZATION
/////////////////////////////////////////////////

bool GDOculusPlatform::is_platform_initialized() {
	return ovr_IsPlatformInitialized();
}

/// Initialize Android Oculus Platform synchronously.
bool GDOculusPlatform::initialize_platform(const String &p_app_id, const Dictionary &p_initialization_options) {
	if (ovr_IsPlatformInitialized()) {
		return true;
	}
#ifdef __ANDROID__
	// No initialization options defined
	if (p_initialization_options.is_empty()) {
		JNIEnv *gdjenv;
		_get_env(&gdjenv);

		// Try to connect pump_messages to process
		if (!_try_connecting_process()) {
			return false;
		}

		ovrPlatformInitializeResult init_result = ovr_PlatformInitializeAndroid(p_app_id.utf8().get_data(), jactivity, gdjenv);

		ERR_FAIL_COND_V_MSG(init_result != ovrPlatformInitialize_Success, false, vformat("[GDOP] Error initializing platform: %s", ovrPlatformInitializeResult_ToString(init_result)));

		return true;

	} else {
		ovrKeyValuePair config_options[2];

		// Make sure initialization options are valid
		if (p_initialization_options.has("disable_p2p_networking")) {
			ERR_FAIL_COND_V_MSG(p_initialization_options.get("disable_p2p_networking", 0).get_type() != Variant::BOOL, false, "[GDOP] Invalid initialization options. The disable_p2p_networking key must have a boolean value.");

			config_options[0] = ovr_InitConfigOption_CreateBool(ovrInitConfigOption_DisableP2pNetworking, (bool)p_initialization_options.get("disable_p2p_networking", true));
		} else {
			config_options[0] = ovr_InitConfigOption_CreateBool(ovrInitConfigOption_DisableP2pNetworking, true);
		}

		if (p_initialization_options.has("enable_cowatching")) {
			ERR_FAIL_COND_V_MSG(p_initialization_options.get("enable_cowatching", 0).get_type() != Variant::BOOL, false, "[GDOP] Invalid initialization options. The enable_cowatching key must have a boolean value.");

			config_options[1] = ovr_InitConfigOption_CreateBool(ovrInitConfigOption_EnableCowatching, (bool)p_initialization_options.get("enable_cowatching", false));
		} else {
			config_options[1] = ovr_InitConfigOption_CreateBool(ovrInitConfigOption_EnableCowatching, false);
		}

		JNIEnv *gdjenv;
		_get_env(&gdjenv);

		// Try to connect pump_messages to process
		if (!_try_connecting_process()) {
			return false;
		}

		size_t config_opts_size = sizeof(config_options) / sizeof(config_options[0]);

		ovrPlatformInitializeResult init_result = ovr_PlatformInitializeAndroidWithOptions(p_app_id.utf8().get_data(), jactivity, gdjenv, config_options, config_opts_size);

		ERR_FAIL_COND_V_MSG(init_result != ovrPlatformInitialize_Success, false, vformat("[GDOP] Error initializing platform: %s", ovrPlatformInitializeResult_ToString(init_result)));

		return true;
	}
#else
	// Initialization options (p_initialization_options) not supported for windows
	// Try to connect pump_messages to process
	if (!_try_connecting_process()) {
		return false;
	}
	ovrPlatformInitializeResult init_result = ovr_PlatformInitializeWindows(p_app_id.utf8().get_data());
	ERR_FAIL_COND_V_MSG(init_result != ovrPlatformInitialize_Success, false, vformat("[GDOP] Error initializing windows platform: %s", ovrPlatformInitializeResult_ToString(init_result)));
	return true;
#endif
}

ovrPlatformInitializeResult initOutResult;
Ref<GDOculusPlatformPromise> GDOculusPlatform::initialize_platform_async(const String &p_app_id) {
	if (!ovr_IsPlatformInitialized()) {
#ifdef __ANDROID__
		JNIEnv *gdjenv;
		_get_env(&gdjenv);
#endif
		// Try to connect pump_messages to process
		if (!_try_connecting_process()) {
			Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
			String rejection_msg = "Oculus Platform not initialized because pump_messages couldn't be connected to process.";
			return_promise->saved_rejection_response = Array::make(rejection_msg);
			_promises_to_reject.push_back(return_promise);

			return return_promise;
		}

#ifdef __ANDROID__
		ovrRequest req = ovr_PlatformInitializeAndroidAsynchronous(p_app_id.utf8().get_data(), jactivity, gdjenv);
#else
		ovrRequest req = ovr_PlatformInitializeWindowsAsynchronous(p_app_id.utf8().get_data(), &initOutResult);
#endif
		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
		_promises.push_back(return_promise);

		return return_promise;

	} else {
		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
		String rejection_msg = "Oculus Platform already initialized";
		return_promise->saved_rejection_response = Array::make(rejection_msg);
		_promises_to_reject.push_back(return_promise);

		return return_promise;
	}
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// USER
/////////////////////////////////////////////////

/// Requests the current user's id
/// @return The logged-in user's id as a String
String GDOculusPlatform::user_get_logged_in_user_id() {
	char native_id[OVRID_SIZE];
	ovrID u_id = ovr_GetLoggedInUserID();
	ovrID_ToString(native_id, OVRID_SIZE, u_id);

	return String(native_id);
}

/// Requests the current user's locale
/// @return The logged-in user's locale as a String
String GDOculusPlatform::user_get_logged_in_user_locale() {
	return String(ovr_GetLoggedInUserLocale());
}

/// Checks if the user is entitled to the current application.
/// @return Promise that will be fulfilled if the user is entitled to the app. It will be rejected (error) if the user is not entitled
Ref<GDOculusPlatformPromise> GDOculusPlatform::user_get_is_viewer_entitled() {
#ifndef __ANDROID__
	// Try to connect pump_messages to process
	if (!_try_connecting_process()) {
		return false;
	}
#endif
	ovrRequest req = ovr_Entitlement_GetIsViewerEntitled();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests information about the current user.
/// @return Promise that will be fulfilled with the user's id, oculus_id, display_name, image_url, small_image_url and various Presence related information.
Ref<GDOculusPlatformPromise> GDOculusPlatform::user_get_logged_in_user() {
#ifndef __ANDROID__
	// Try to connect pump_messages to process
	if (!_try_connecting_process()) {
		return false;
	}
#endif
	ovrRequest req = ovr_User_GetLoggedInUser();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests information about an user from its ID.
/// @return Promise that will be fulfilled with the user's id, oculus_id, display_name, image_url, small_image_url and various Presence related information.
Ref<GDOculusPlatformPromise> GDOculusPlatform::user_get_user(const String &p_user_id) {
#ifndef __ANDROID__
	// Try to connect pump_messages to process
	if (!_try_connecting_process()) {
		return false;
	}
#endif
	ovrID u_id;
	if (ovrID_FromString(&u_id, p_user_id.utf8().get_data())) {
		ovrRequest req = ovr_User_Get(u_id);

		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
		_promises.push_back(return_promise);

		return return_promise;

	} else {
		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
		String rejection_msg = "Invalid user id.";
		return_promise->saved_rejection_response = Array::make(rejection_msg);
		_promises_to_reject.push_back(return_promise);

		return return_promise;
	}
}

/// Requests a nonce used to verify the user.
/// @return Promise that will be fulfilled with the a nonce that can be used to verify the user.
Ref<GDOculusPlatformPromise> GDOculusPlatform::user_get_user_proof() {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_User_GetUserProof();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests the user access token suitable to make REST calls against graph.oculus.com.
/// @return Promise that will be contain a String token if fulfilled
Ref<GDOculusPlatformPromise> GDOculusPlatform::user_get_user_access_token() {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_User_GetAccessToken();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests the user IDs of users blocked by the current user.
/// @return Promise that will contain user IDs as an Array of Strings if fulfilled
Ref<GDOculusPlatformPromise> GDOculusPlatform::user_get_blocked_users() {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_User_GetBlockedUsers();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests the user IDs of the current user's friends.
/// @return Promise that will contain an Array of Dictionaries with information about each friend. Same format as the Dictionary returned by get_user()
Ref<GDOculusPlatformPromise> GDOculusPlatform::user_get_logged_in_user_friends() {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_User_GetLoggedInUserFriends();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests the scoped org ID of a given user
/// @return Promise that will contain the org scoped ID of the given user as a String if fulfilled
Ref<GDOculusPlatformPromise> GDOculusPlatform::user_get_org_scoped_id(const String &p_user_id) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrID u_id;
	if (ovrID_FromString(&u_id, p_user_id.utf8().get_data())) {
		ovrRequest req = ovr_User_GetOrgScopedID(u_id);

		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
		_promises.push_back(return_promise);

		return return_promise;

	} else {
		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
		String rejection_msg = "Invalid user id.";
		return_promise->saved_rejection_response = Array::make(rejection_msg);
		_promises_to_reject.push_back(return_promise);

		return return_promise;
	}
}

/// Requests all the accounts belonging to this user.
/// @return Promise that will contain an Array of Dictionaries with the type of account and its ID, if fulfilled.
Ref<GDOculusPlatformPromise> GDOculusPlatform::user_get_sdk_accounts() {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_User_GetSdkAccounts();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests a block flow to block an user by its ID.
/// @return Promise that will contain a Dictionary with information if the user blocked or cancelled the request.
Ref<GDOculusPlatformPromise> GDOculusPlatform::user_launch_block_flow(const String &p_user_id) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrID u_id;
	if (ovrID_FromString(&u_id, p_user_id.utf8().get_data())) {
		ovrRequest req = ovr_User_LaunchBlockFlow(u_id);

		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
		_promises.push_back(return_promise);

		return return_promise;

	} else {
		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
		String rejection_msg = "Invalid user id.";
		return_promise->saved_rejection_response = Array::make(rejection_msg);
		_promises_to_reject.push_back(return_promise);

		return return_promise;
	}
}

/// Requests an unblock flow to unblock an user by its ID.
/// @return Promise that will contain a Dictionary with information if the user unblocked or cancelled the request.
Ref<GDOculusPlatformPromise> GDOculusPlatform::user_launch_unblock_flow(const String &p_user_id) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrID u_id;
	if (ovrID_FromString(&u_id, p_user_id.utf8().get_data())) {
		ovrRequest req = ovr_User_LaunchUnblockFlow(u_id);

		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
		_promises.push_back(return_promise);

		return return_promise;

	} else {
		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
		String rejection_msg = "Invalid user id.";
		return_promise->saved_rejection_response = Array::make(rejection_msg);
		_promises_to_reject.push_back(return_promise);

		return return_promise;
	}
}

/// Requests a friend request flow to send a friend request to a user with a given ID.
/// @return Promise that will contain a Dictionary with information if the user sent the friend request or cancelled.
Ref<GDOculusPlatformPromise> GDOculusPlatform::user_launch_friend_request_flow(const String &p_user_id) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrID u_id;
	if (ovrID_FromString(&u_id, p_user_id.utf8().get_data())) {
		ovrRequest req = ovr_User_LaunchFriendRequestFlow(u_id);

		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
		_promises.push_back(return_promise);

		return return_promise;

	} else {
		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
		String rejection_msg = "Invalid user id.";
		return_promise->saved_rejection_response = Array::make(rejection_msg);
		_promises_to_reject.push_back(return_promise);

		return return_promise;
	}
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// ACHIEVEMENTS
/////////////////////////////////////////////////

/// Requests an update for an achievement of type COUNT.
/// @return Promise that will contain a Dictionary with info about the result of the update request.
Ref<GDOculusPlatformPromise> GDOculusPlatform::achievements_add_count(const String &p_achievement_name, uint64_t p_count) {
#ifndef __ANDROID__
	// Try to connect pump_messages to process
	if (!_try_connecting_process()) {
		return false;
	}
#endif
	ovrRequest req = ovr_Achievements_AddCount(p_achievement_name.utf8().get_data(), p_count);

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests an update for an achievement of type BITFIELD.
/// @return Promise that will contain a Dictionary with info about the result of the update request.
Ref<GDOculusPlatformPromise> GDOculusPlatform::achievements_add_fields(const String &p_achievement_name, const String &p_fields) {
#ifndef __ANDROID__
	// Try to connect pump_messages to process
	if (!_try_connecting_process()) {
		return false;
	}
#endif
	ovrRequest req = ovr_Achievements_AddFields(p_achievement_name.utf8().get_data(), p_fields.utf8().get_data());

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests an update (to unlock) for an achievement of any type.
/// @return Promise that will contain a Dictionary with info about the result of the update request.
Ref<GDOculusPlatformPromise> GDOculusPlatform::achievements_unlock(const String &p_achievement_name) {
#ifndef __ANDROID__
	// Try to connect pump_messages to process
	if (!_try_connecting_process()) {
		return false;
	}
#endif
	ovrRequest req = ovr_Achievements_Unlock(p_achievement_name.utf8().get_data());

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests all the achievement definitions.
/// @return Promise that will contain an Array of Dictionaries with info about each achievement.
Ref<GDOculusPlatformPromise> GDOculusPlatform::achievements_get_all_definitions() {
#ifndef __ANDROID__
	// Try to connect pump_messages to process
	if (!_try_connecting_process()) {
		return false;
	}
#endif
	ovrRequest req = ovr_Achievements_GetAllDefinitions();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests all the achievement progress.
/// @return Promise that will contain an Array of Dictionaries with info about each achievement.
Ref<GDOculusPlatformPromise> GDOculusPlatform::achievements_get_all_progress() {
#ifndef __ANDROID__
	// Try to connect pump_messages to process
	if (!_try_connecting_process()) {
		return false;
	}
#endif
	ovrRequest req = ovr_Achievements_GetAllProgress();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests achievements definitions by name
/// @return Promise that will contain an Array of Dictionaries with info about each achievement.
Ref<GDOculusPlatformPromise> GDOculusPlatform::achievements_get_definitions_by_name(const Array &p_achievement_names) {
#ifndef __ANDROID__
	// Try to connect pump_messages to process
	if (!_try_connecting_process()) {
		return false;
	}
#endif
	int achiev_arr_s = p_achievement_names.size();

	if (achiev_arr_s > 0 && achiev_arr_s <= INT_MAX) {
		const char **char_arr = memnew_arr(const char *, achiev_arr_s);
		std::vector<std::string> sav(achiev_arr_s);

		for (size_t j = 0; j < achiev_arr_s; j++) {
			char_arr[j] = "";
		}

		for (int i = 0; i < achiev_arr_s; i++) {
			if (p_achievement_names[i].get_type() == Variant::STRING) {
				sav[i] = ((String)p_achievement_names[i]).utf8().get_data();
				char_arr[i] = sav[i].c_str();

			} else {
				memdelete_arr(char_arr);
				Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
				String rejection_msg = "Invalid achievement name found in array. All achievement names must be Strings.";
				return_promise->saved_rejection_response = Array::make(rejection_msg);
				_promises_to_reject.push_back(return_promise);

				return return_promise;
			}
		}

		ovrRequest req = ovr_Achievements_GetDefinitionsByName(char_arr, achiev_arr_s);

		memdelete_arr(char_arr);

		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
		_promises.push_back(return_promise);

		return return_promise;

	} else if (achiev_arr_s >= INT_MAX) {
		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
		String rejection_msg = "Too many achievement names... How do you have more than 2147483647 achievements?";
		return_promise->saved_rejection_response = Array::make(rejection_msg);
		_promises_to_reject.push_back(return_promise);

		return return_promise;

	} else {
		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
		String rejection_msg = "Achievements array is empty.";
		return_promise->saved_rejection_response = Array::make(rejection_msg);
		_promises_to_reject.push_back(return_promise);

		return return_promise;
	}
}

/// Requests achievements progress by name.
/// @return Promise that will contain an Array of Dictionaries with info about each achievement.
Ref<GDOculusPlatformPromise> GDOculusPlatform::achievements_get_progress_by_name(const Array &p_achievement_names) {
#ifndef __ANDROID__
	// Try to connect pump_messages to process
	if (!_try_connecting_process()) {
		return false;
	}
#endif
	int64_t achiev_arr_s = p_achievement_names.size();

	if (achiev_arr_s > 0 && achiev_arr_s <= INT_MAX) {
		const char **char_arr = memnew_arr(const char *, achiev_arr_s);
		std::vector<std::string> sav(achiev_arr_s);

		for (size_t j = 0; j < achiev_arr_s; j++) {
			char_arr[j] = "";
		}

		for (int i = 0; i < achiev_arr_s; i++) {
			if (p_achievement_names[i].get_type() == Variant::STRING) {
				sav[i] = ((String)p_achievement_names[i]).utf8().get_data();
				char_arr[i] = sav[i].c_str();

			} else {
				memdelete_arr(char_arr);
				Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
				String rejection_msg = "Invalid achievement name found in array. All achievement names must be Strings.";
				return_promise->saved_rejection_response = Array::make(rejection_msg);
				_promises_to_reject.push_back(return_promise);

				return return_promise;
			}
		}
		ovrRequest req = ovr_Achievements_GetProgressByName(char_arr, achiev_arr_s);

		memdelete_arr(char_arr);

		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
		_promises.push_back(return_promise);

		return return_promise;

	} else if (achiev_arr_s >= INT_MAX) {
		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
		String rejection_msg = "Too many achievement names... How do you have more than 2147483647 achievements?";
		return_promise->saved_rejection_response = Array::make(rejection_msg);
		_promises_to_reject.push_back(return_promise);

		return return_promise;

	} else {
		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
		String rejection_msg = "Achievements array is empty.";
		return_promise->saved_rejection_response = Array::make(rejection_msg);
		_promises_to_reject.push_back(return_promise);

		return return_promise;
	}
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// IAP
/////////////////////////////////////////////////

/// Requests the current user's purchases. They include consumable items and durable items.
/// @return Promise that contains an Array of Dictionaries with information about each purchase.
Ref<GDOculusPlatformPromise> GDOculusPlatform::iap_get_viewer_purchases() {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_IAP_GetViewerPurchases();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests the current user's purchases (only durable) from the device's cache.
/// @return Promise that contains an Array of Dictionaries with information about each purchase.
Ref<GDOculusPlatformPromise> GDOculusPlatform::iap_get_viewer_purchases_durable_cache() {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_IAP_GetViewerPurchasesDurableCache();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests a list of products by their SKU
/// @return Promise that contains an Array of Dictionaries with information about each product
Ref<GDOculusPlatformPromise> GDOculusPlatform::iap_get_products_by_sku(const Array &p_sku_list) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	int64_t skus_arr_s = p_sku_list.size();

	if (skus_arr_s > 0 && skus_arr_s <= INT_MAX) {
		const char **char_arr = memnew_arr(const char *, skus_arr_s);
		std::vector<std::string> sav(skus_arr_s);

		for (size_t j = 0; j < skus_arr_s; j++) {
			char_arr[j] = "";
		}

		for (int i = 0; i < skus_arr_s; i++) {
			if (p_sku_list[i].get_type() == Variant::STRING) {
				sav[i] = ((String)p_sku_list[i]).utf8().get_data();
				char_arr[i] = sav[i].c_str();

			} else {
				memdelete_arr(char_arr);
				Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
				String rejection_msg = "Invalid SKU found in array. All SKUs must be Strings.";
				return_promise->saved_rejection_response = Array::make(rejection_msg);
				_promises_to_reject.push_back(return_promise);

				return return_promise;
			}
		}

		ovrRequest req = ovr_IAP_GetProductsBySKU(char_arr, skus_arr_s);
		memdelete_arr(char_arr);

		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
		_promises.push_back(return_promise);

		return return_promise;

	} else if (skus_arr_s >= INT_MAX) {
		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
		String rejection_msg = "Too many SKUs... How do you have more than 2147483647 SKUs?";
		return_promise->saved_rejection_response = Array::make(rejection_msg);
		_promises_to_reject.push_back(return_promise);

		return return_promise;

	} else {
		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
		String rejection_msg = "SKU array is empty.";
		return_promise->saved_rejection_response = Array::make(rejection_msg);
		_promises_to_reject.push_back(return_promise);

		return return_promise;
	}
}

/// Consumes a consumable item
/// @return Promise that contains true if the request was successful. It will error if unable to consume
Ref<GDOculusPlatformPromise> GDOculusPlatform::iap_consume_purchase(const String &p_sku) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_IAP_ConsumePurchase(p_sku.utf8().get_data());

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Launches the checkout flow
/// @return Promise that contains a Dictionary with information about the product. purchase_str_id will be empty if the user did not complete the purchase
Ref<GDOculusPlatformPromise> GDOculusPlatform::iap_launch_checkout_flow(const String &p_sku) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_IAP_LaunchCheckoutFlow(p_sku.utf8().get_data());

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// ASSET FILE
/////////////////////////////////////////////////

/// Requests a list of asset files associated with the app.
/// @return Promise that contains an Array of Dictionaries with information about each assetfile. Language packs have extra information.
Ref<GDOculusPlatformPromise> GDOculusPlatform::assetfile_get_list() {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_AssetFile_GetList();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests information about a single asset file by ID.
/// @return Promise that contains a Dictionary with information about the assetfile. Language packs have extra information.
Ref<GDOculusPlatformPromise> GDOculusPlatform::assetfile_status_by_id(const String &p_asset_id) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrID n_asset_id;
	if (ovrID_FromString(&n_asset_id, p_asset_id.utf8().get_data())) {
		ovrRequest req = ovr_AssetFile_StatusById(n_asset_id);

		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
		_promises.push_back(return_promise);

		return return_promise;

	} else {
		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
		String rejection_msg = "Invalid asset file id.";
		return_promise->saved_rejection_response = Array::make(rejection_msg);
		_promises_to_reject.push_back(return_promise);

		return return_promise;
	}
}

/// Requests information about a single asset file by name.
/// @return Promise that contains a Dictionary with information about the assetfile. Language packs have extra information.
Ref<GDOculusPlatformPromise> GDOculusPlatform::assetfile_status_by_name(const String &p_asset_name) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_AssetFile_StatusByName(p_asset_name.utf8().get_data());

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests to download an asset file by ID.
/// @return Promise that contains the result of the request as a Dictionary.
Ref<GDOculusPlatformPromise> GDOculusPlatform::assetfile_download_by_id(const String &p_asset_id) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrID n_asset_id;
	if (ovrID_FromString(&n_asset_id, p_asset_id.utf8().get_data())) {
		ovrRequest req = ovr_AssetFile_DownloadById(n_asset_id);

		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
		_promises.push_back(return_promise);

		return return_promise;

	} else {
		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
		String rejection_msg = "Invalid asset file id.";
		return_promise->saved_rejection_response = Array::make(rejection_msg);
		_promises_to_reject.push_back(return_promise);

		return return_promise;
	}
}

/// Requests to download an asset file by name.
/// @return Promise that contains the result of the request as a Dictionary.
Ref<GDOculusPlatformPromise> GDOculusPlatform::assetfile_download_by_name(const String &p_asset_name) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_AssetFile_DownloadByName(p_asset_name.utf8().get_data());

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests to cancel a download of an assetfile by ID.
/// @return Promise that contains the result of the request as a Dictionary. The dictionary includes a "success" key to indicate if the request was successful
Ref<GDOculusPlatformPromise> GDOculusPlatform::assetfile_download_cancel_by_id(const String &p_asset_id) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrID n_asset_id;
	if (ovrID_FromString(&n_asset_id, p_asset_id.utf8().get_data())) {
		ovrRequest req = ovr_AssetFile_DownloadCancelById(n_asset_id);

		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
		_promises.push_back(return_promise);

		return return_promise;

	} else {
		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
		String rejection_msg = "Invalid asset file id.";
		return_promise->saved_rejection_response = Array::make(rejection_msg);
		_promises_to_reject.push_back(return_promise);

		return return_promise;
	}
}

/// Requests to cancel a download of an assetfile by name.
/// @return Promise that contains the result of the request as a Dictionary. The dictionary includes a "success" key to indicate if the request was successful
Ref<GDOculusPlatformPromise> GDOculusPlatform::assetfile_download_cancel_by_name(const String &p_asset_name) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_AssetFile_DownloadCancelByName(p_asset_name.utf8().get_data());

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests to delete an assetfile by ID.
/// @return Promise that contains the result of the request as a Dictionary. The dictionary includes a "success" key to indicate if the request was successful
Ref<GDOculusPlatformPromise> GDOculusPlatform::assetfile_delete_by_id(const String &p_asset_id) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrID n_asset_id;
	if (ovrID_FromString(&n_asset_id, p_asset_id.utf8().get_data())) {
		ovrRequest req = ovr_AssetFile_DeleteById(n_asset_id);

		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
		_promises.push_back(return_promise);

		return return_promise;

	} else {
		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
		String rejection_msg = "Invalid asset file id.";
		return_promise->saved_rejection_response = Array::make(rejection_msg);
		_promises_to_reject.push_back(return_promise);

		return return_promise;
	}
}

/// Requests to delete an assetfile by name.
/// @return Promise that contains the result of the request as a Dictionary. The dictionary includes a "success" key to indicate if the request was successful
Ref<GDOculusPlatformPromise> GDOculusPlatform::assetfile_delete_by_name(const String &p_asset_name) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_AssetFile_DeleteByName(p_asset_name.utf8().get_data());

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// LEADERBOARD
/////////////////////////////////////////////////

/// Requests information about a single leaderboard.
/// @return Promise that contains a Dictionary with the ID and API name of the leaderboard, if fulfilled.
Ref<GDOculusPlatformPromise> GDOculusPlatform::leaderboard_get(const String &p_leaderboard_name) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_Leaderboard_Get(p_leaderboard_name.utf8().get_data());

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests entries of a given leaderboard. Several filters can be applied to narrow down the result.
/// @return Promise that contains an Array of Dictionaries as entries of the leaderboard, if fulfilled.
Ref<GDOculusPlatformPromise> GDOculusPlatform::leaderboard_get_entries(const String &p_leaderboard_name, uint64_t p_limit, LeaderboardFilterType p_filter, LeaderboardStartAt p_start_at) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	if (p_limit < 0) {
		p_limit = 0;
	} else if (p_limit > INT32_MAX) {
		p_limit = INT32_MAX;
	}

	ovrRequest req = ovr_Leaderboard_GetEntries(p_leaderboard_name.utf8().get_data(), p_limit, (ovrLeaderboardFilterType)p_filter, (ovrLeaderboardStartAt)p_start_at);

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests entries after a rank of a given leaderboard. No other filters can be applied.
/// @return Promise that contains an Array of Dictionaries as entries of the leaderboard, if fulfilled.
Ref<GDOculusPlatformPromise> GDOculusPlatform::leaderboard_get_entries_after_rank(const String &p_leaderboard_name, uint64_t p_limit, uint64_t p_after_rank) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	if (p_limit < 0) {
		p_limit = 0;
	} else if (p_limit > INT32_MAX) {
		p_limit = INT32_MAX;
	}

	ovrRequest req = ovr_Leaderboard_GetEntriesAfterRank(p_leaderboard_name.utf8().get_data(), p_limit, p_after_rank);

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests entries of a given leaderboard. Only returns entries that match the given IDs.
/// @return Promise that contains an Array of Dictionaries as entries of the leaderboard, if fulfilled.
Ref<GDOculusPlatformPromise> GDOculusPlatform::leaderboard_get_entries_by_ids(const String &p_leaderboard_name, uint64_t p_limit, const Array &p_user_ids, LeaderboardStartAt p_start_at) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	if (p_limit < 0) {
		p_limit = 0;
	} else if (p_limit > INT32_MAX) {
		p_limit = INT32_MAX;
	}

	int64_t ids_arr_size = p_user_ids.size();

	ovrID *ovr_ids = memnew_arr(ovrID, ids_arr_size);
	std::vector<ovrID> sav(ids_arr_size);

	for (size_t j = 0; j < ids_arr_size; j++) {
		ovr_ids[j] = 0;
	}

	for (int i = 0; i < ids_arr_size; i++) {
		if (p_user_ids[i].get_type() == Variant::STRING) {
			ovrID_FromString(&sav[i], ((String)p_user_ids[i]).utf8().get_data());
			ovr_ids[i] = sav[i];

		} else {
			memdelete_arr(ovr_ids);
			Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
			String rejection_msg = "Invalid user ID found in array. All user IDs names must be Strings.";
			return_promise->saved_rejection_response = Array::make(rejection_msg);
			_promises_to_reject.push_back(return_promise);

			return return_promise;
		}
	}

	ovrRequest req = ovr_Leaderboard_GetEntriesByIds(p_leaderboard_name.utf8().get_data(), p_limit, (ovrLeaderboardStartAt)p_start_at, ovr_ids, ids_arr_size);
	memdelete_arr(ovr_ids);

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Sends a request to write an entry to a leaderboard. Several options such as supplementary metrics and extra data can be specified.
/// @return Promise that contains a Dictionary with info about the request status, if fulfilled.
Ref<GDOculusPlatformPromise> GDOculusPlatform::leaderboard_write_entry(const String &p_leaderboard_name, uint64_t p_score, bool p_force_update, const Dictionary &p_extra) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	if (p_score < 0) {
		p_score = 0;
	}

	if (!p_extra.has("supplementary_metric")) {
		if (p_extra.get("extra_data", "").get_type() != Variant::STRING) {
			Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
			String rejection_msg = "Extra data must be a String.";
			return_promise->saved_rejection_response = Array::make(rejection_msg);
			_promises_to_reject.push_back(return_promise);

			return return_promise;
		}

		ovrRequest req = ovr_Leaderboard_WriteEntry(p_leaderboard_name.utf8().get_data(), p_score, ((String)p_extra.get("extra_data", "")).utf8().get_data(), ((String)p_extra["extra_data"]).utf8().length(), p_force_update);

		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
		_promises.push_back(return_promise);

		return return_promise;

	} else {
		if (p_extra.get("supplementary_metric", "").get_type() != Variant::INT) {
			Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
			String rejection_msg = "Supplementary metric must be an int.";
			return_promise->saved_rejection_response = Array::make(rejection_msg);
			_promises_to_reject.push_back(return_promise);

			return return_promise;
		}

		if (p_extra.get("extra_data", "").get_type() != Variant::STRING) {
			Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
			String rejection_msg = "Extra data must be a String.";
			return_promise->saved_rejection_response = Array::make(rejection_msg);
			_promises_to_reject.push_back(return_promise);

			return return_promise;
		}

		if ((uint64_t)p_extra.get("supplementary_metric", 0) < 0) {
			Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
			String rejection_msg = "supplementary_metric must be a positive int.";
			return_promise->saved_rejection_response = Array::make(rejection_msg);
			_promises_to_reject.push_back(return_promise);

			return return_promise;
		}

		ovrRequest req = ovr_Leaderboard_WriteEntryWithSupplementaryMetric(p_leaderboard_name.utf8().get_data(), p_score, (int64_t)p_extra["supplementary_metric"], ((String)p_extra.get("extra_data", "")).utf8().get_data(), ((String)p_extra["extra_data"]).utf8().length(), p_force_update);

		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
		_promises.push_back(return_promise);

		return return_promise;
	}
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// ABUSE REPORT
/////////////////////////////////////////////////

/// Informs the platform whether the app handled or not the report request.
/// @return Promise that will contain a true bool if the request was successful.
Ref<GDOculusPlatformPromise> GDOculusPlatform::abuse_report_request_handled(ReportRequestResponse p_report_req_resp) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_AbuseReport_ReportRequestHandled((ovrReportRequestResponse)p_report_req_resp);

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// APPLICATION
/////////////////////////////////////////////////

/// Requests information about the app, including current installed version and latest version.
/// @return Promise that will contain a Dictionary with information about the app.
Ref<GDOculusPlatformPromise> GDOculusPlatform::application_get_version() {
#ifndef __ANDROID__
	// Try to connect pump_messages to process
	if (!_try_connecting_process()) {
		return false;
	}
#endif
	ovrRequest req = ovr_Application_GetVersion();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests the platform to launch another app.
/// @return Promise that will contain a message with information about the request.
Ref<GDOculusPlatformPromise> GDOculusPlatform::application_launch_other_app(const String &p_app_id, const Dictionary &p_deeplink_options) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrApplicationOptionsHandle deeplink_options = ovr_ApplicationOptions_Create();
	ovrID app_id;

	if (ovrID_FromString(&app_id, p_app_id.utf8().get_data())) {
		if (!p_deeplink_options.is_empty()) {
			if (p_deeplink_options.has("deeplink_message")) {
				if (p_deeplink_options.get("deeplink_message", 0).get_type() != Variant::STRING) {
					ovr_ApplicationOptions_Destroy(deeplink_options);
					Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
					String rejection_msg = "The deeplink_message value must be a String.";
					return_promise->saved_rejection_response = Array::make(rejection_msg);
					_promises_to_reject.push_back(return_promise);

					return return_promise;

				} else {
					ovr_ApplicationOptions_SetDeeplinkMessage(deeplink_options, ((String)p_deeplink_options["deeplink_message"]).utf8().get_data());
				}

				if (p_deeplink_options.has("destination_api_name")) {
					if (p_deeplink_options.get("destination_api_name", 0).get_type() != Variant::STRING) {
						ovr_ApplicationOptions_Destroy(deeplink_options);
						Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
						String rejection_msg = "The destination_api_name value must be a String.";
						return_promise->saved_rejection_response = Array::make(rejection_msg);
						_promises_to_reject.push_back(return_promise);

						return return_promise;
					} else {
						ovr_ApplicationOptions_SetDestinationApiName(deeplink_options, ((String)p_deeplink_options["destination_api_name"]).utf8().get_data());
					}
				}

				if (p_deeplink_options.has("lobby_session_id")) {
					if (p_deeplink_options.get("lobby_session_id", 0).get_type() != Variant::STRING) {
						ovr_ApplicationOptions_Destroy(deeplink_options);
						Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
						String rejection_msg = "The destination_api_name value must be a String.";
						return_promise->saved_rejection_response = Array::make(rejection_msg);
						_promises_to_reject.push_back(return_promise);

						return return_promise;
					} else {
						ovr_ApplicationOptions_SetLobbySessionId(deeplink_options, ((String)p_deeplink_options["lobby_session_id"]).utf8().get_data());
					}
				}

				if (p_deeplink_options.has("match_session_id")) {
					if (p_deeplink_options.get("match_session_id", 0).get_type() != Variant::STRING) {
						ovr_ApplicationOptions_Destroy(deeplink_options);
						Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
						String rejection_msg = "The destination_api_name value must be a String.";
						return_promise->saved_rejection_response = Array::make(rejection_msg);
						_promises_to_reject.push_back(return_promise);

						return return_promise;
					} else {
						ovr_ApplicationOptions_SetMatchSessionId(deeplink_options, ((String)p_deeplink_options["match_session_id"]).utf8().get_data());
					}
				}

				ovrRequest req = ovr_Application_LaunchOtherApp(app_id, deeplink_options);
				ovr_ApplicationOptions_Destroy(deeplink_options);

				Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
				_promises.push_back(return_promise);

				return return_promise;

			} else {
				ovr_ApplicationOptions_Destroy(deeplink_options);
				Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
				String rejection_msg = "A deeplink_message is required when supplying a non-empty deeplink_options dictionary.";
				return_promise->saved_rejection_response = Array::make(rejection_msg);
				_promises_to_reject.push_back(return_promise);

				return return_promise;
			}

		} else {
			ovr_ApplicationOptions_SetDeeplinkMessage(deeplink_options, "");

			ovrRequest req = ovr_Application_LaunchOtherApp(app_id, deeplink_options);
			ovr_ApplicationOptions_Destroy(deeplink_options);

			Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
			_promises.push_back(return_promise);

			return return_promise;
		}

	} else {
		ovr_ApplicationOptions_Destroy(deeplink_options);
		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
		String rejection_msg = "Invalid app id.";
		return_promise->saved_rejection_response = Array::make(rejection_msg);
		_promises_to_reject.push_back(return_promise);

		return return_promise;
	}
}

/// Starts downloading an app update if there is one.
/// @return Promise that will contain an int with the timestamp of when the download started.
Ref<GDOculusPlatformPromise> GDOculusPlatform::application_start_app_download() {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_Application_StartAppDownload();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests the app update download progress.
/// @return Promise that will contain a Dictionary with information about the progress of the download.
Ref<GDOculusPlatformPromise> GDOculusPlatform::application_check_app_download_progress() {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_Application_CheckAppDownloadProgress();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests the cancelation of the app download.
/// @return Promise that will contain an int with the timestamp of when the download was cancelled.
Ref<GDOculusPlatformPromise> GDOculusPlatform::application_cancel_app_download() {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_Application_CancelAppDownload();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests the platform to install the downloaded update and relaunch.
/// @return Promise that will contain an int with the timestamp of when the install request was initiated.
Ref<GDOculusPlatformPromise> GDOculusPlatform::application_install_app_update_and_relaunch(const Dictionary &p_deeplink_options) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrApplicationOptionsHandle deeplink_options = ovr_ApplicationOptions_Create();

	if (!p_deeplink_options.is_empty()) {
		if (p_deeplink_options.has("deeplink_message")) {
			if (p_deeplink_options.get("deeplink_message", 0).get_type() != Variant::STRING) {
				ovr_ApplicationOptions_Destroy(deeplink_options);
				Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
				String rejection_msg = "The deeplink_message value must be a String.";
				return_promise->saved_rejection_response = Array::make(rejection_msg);
				_promises_to_reject.push_back(return_promise);

				return return_promise;

			} else {
				ovr_ApplicationOptions_SetDeeplinkMessage(deeplink_options, ((String)p_deeplink_options["deeplink_message"]).utf8().get_data());
			}

			if (p_deeplink_options.has("destination_api_name")) {
				if (p_deeplink_options.get("destination_api_name", 0).get_type() != Variant::STRING) {
					ovr_ApplicationOptions_Destroy(deeplink_options);
					Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
					String rejection_msg = "The destination_api_name value must be a String.";
					return_promise->saved_rejection_response = Array::make(rejection_msg);
					_promises_to_reject.push_back(return_promise);

					return return_promise;
				} else {
					ovr_ApplicationOptions_SetDestinationApiName(deeplink_options, ((String)p_deeplink_options["destination_api_name"]).utf8().get_data());
				}
			}

			if (p_deeplink_options.has("lobby_session_id")) {
				if (p_deeplink_options.get("lobby_session_id", 0).get_type() != Variant::STRING) {
					ovr_ApplicationOptions_Destroy(deeplink_options);
					Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
					String rejection_msg = "The destination_api_name value must be a String.";
					return_promise->saved_rejection_response = Array::make(rejection_msg);
					_promises_to_reject.push_back(return_promise);

					return return_promise;
				} else {
					ovr_ApplicationOptions_SetLobbySessionId(deeplink_options, ((String)p_deeplink_options["lobby_session_id"]).utf8().get_data());
				}
			}

			if (p_deeplink_options.has("match_session_id")) {
				if (p_deeplink_options.get("match_session_id", 0).get_type() != Variant::STRING) {
					ovr_ApplicationOptions_Destroy(deeplink_options);
					Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
					String rejection_msg = "The destination_api_name value must be a String.";
					return_promise->saved_rejection_response = Array::make(rejection_msg);
					_promises_to_reject.push_back(return_promise);

					return return_promise;
				} else {
					ovr_ApplicationOptions_SetMatchSessionId(deeplink_options, ((String)p_deeplink_options["match_session_id"]).utf8().get_data());
				}
			}

			ovrRequest req = ovr_Application_InstallAppUpdateAndRelaunch(deeplink_options);
			ovr_ApplicationOptions_Destroy(deeplink_options);

			Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
			_promises.push_back(return_promise);

			return return_promise;

		} else {
			ovr_ApplicationOptions_Destroy(deeplink_options);
			Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
			String rejection_msg = "A deeplink_message is required when supplying a non-empty deeplink_options dictionary.";
			return_promise->saved_rejection_response = Array::make(rejection_msg);
			_promises_to_reject.push_back(return_promise);

			return return_promise;
		}

	} else {
		ovr_ApplicationOptions_SetDeeplinkMessage(deeplink_options, "");

		ovrRequest req = ovr_Application_InstallAppUpdateAndRelaunch(deeplink_options);
		ovr_ApplicationOptions_Destroy(deeplink_options);

		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
		_promises.push_back(return_promise);

		return return_promise;
	}
}

/// Requests information about the app's launch.
/// @return A Dictionary with info about the app launch. This can be used to place the player in a specific place inside your app.
Dictionary GDOculusPlatform::application_get_launch_details() {
	ovrLaunchDetailsHandle launch_details_h = ovr_ApplicationLifecycle_GetLaunchDetails();

	Dictionary resp;

	resp["deeplink_message"] = ovr_LaunchDetails_GetDeeplinkMessage(launch_details_h);
	resp["destination_api_name"] = ovr_LaunchDetails_GetDestinationApiName(launch_details_h);
	resp["lobby_session_id"] = ovr_LaunchDetails_GetLobbySessionID(launch_details_h);
	resp["match_session_id"] = ovr_LaunchDetails_GetMatchSessionID(launch_details_h);
	resp["tracking_id"] = ovr_LaunchDetails_GetTrackingID(launch_details_h);
	resp["launch_source"] = ovr_LaunchDetails_GetLaunchSource(launch_details_h);

	// DEEPLINK, COORDINATED, INVITE, NORMAL, UNKNOWN
	ovrLaunchType launch_type = ovr_LaunchDetails_GetLaunchType(launch_details_h);
	resp["launch_type"] = ovrLaunchType_ToString(launch_type);

	ovrUserArrayHandle user_arr_h = ovr_LaunchDetails_GetUsers(launch_details_h);
	Dictionary users_response_dict;

	if (user_arr_h) {
		Array new_user_arr = Array();
		size_t user_arr_s = ovr_UserArray_GetSize(user_arr_h);

		for (size_t i = 0; i < user_arr_s; i++) {
			ovrUserHandle user_h = ovr_UserArray_GetElement(user_arr_h, i);
			Dictionary user_info = _get_user_information(user_h);

			new_user_arr.push_back(user_info);
		}

		users_response_dict["data"] = new_user_arr;
		users_response_dict["next_page_url"] = ovr_UserArray_GetNextUrl(user_arr_h);

	} else {
		users_response_dict["data"] = Array();
		users_response_dict["next_page_url"] = "";
	}

	resp["users"] = users_response_dict;

	return resp;
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// CHALLENGES
////////////////////////////////////////////////

/// Requests information about a single challenge.
/// @return A Dictionary with info about the challenge.
Ref<GDOculusPlatformPromise> GDOculusPlatform::challenges_get(const String &p_challenge_id) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrID challenge_id;
	if (ovrID_FromString(&challenge_id, p_challenge_id.utf8().get_data())) {
		ovrRequest req = ovr_Challenges_Get(challenge_id);

		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
		_promises.push_back(return_promise);

		return return_promise;

	} else {
		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
		String rejection_msg = "Invalid challenge ID.";
		return_promise->saved_rejection_response = Array::make(rejection_msg);
		_promises_to_reject.push_back(return_promise);

		return return_promise;
	}
}

/// Requests information about a list challenges. Several filters can be applied.
/// @return A Dictionary with info about the challenges.
Ref<GDOculusPlatformPromise> GDOculusPlatform::challenges_get_list(uint64_t p_limit, const Dictionary &p_challenge_options) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	if (p_limit < 0) {
		p_limit = 0;
	} else if (p_limit > INT32_MAX) {
		p_limit = INT32_MAX;
	}

	ovrChallengeOptionsHandle challenge_options = ovr_ChallengeOptions_Create();
	if (p_challenge_options.is_empty()) {
		ovr_ChallengeOptions_SetVisibility(challenge_options, ovrChallengeVisibility_Public);
		ovr_ChallengeOptions_SetViewerFilter(challenge_options, ovrChallengeViewerFilter_AllVisible);
		ovr_ChallengeOptions_SetIncludeActiveChallenges(challenge_options, true);
		ovr_ChallengeOptions_SetIncludeFutureChallenges(challenge_options, false);
		ovr_ChallengeOptions_SetIncludePastChallenges(challenge_options, false);

	} else {
		if (p_challenge_options.has("description")) {
			if (p_challenge_options.get("description", 0).get_type() == Variant::STRING) {
				ovr_ChallengeOptions_SetDescription(challenge_options, ((String)p_challenge_options.get("description", "")).utf8().get_data());
			} else {
				ovr_ChallengeOptions_Destroy(challenge_options);
				Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
				String rejection_msg = "Invalid challenge options description value. Description must be a String.";
				return_promise->saved_rejection_response = Array::make(rejection_msg);
				_promises_to_reject.push_back(return_promise);

				return return_promise;
			}
		}

		if (p_challenge_options.has("title")) {
			if (p_challenge_options.get("title", 0).get_type() == Variant::STRING) {
				ovr_ChallengeOptions_SetTitle(challenge_options, ((String)p_challenge_options.get("title", "")).utf8().get_data());
			} else {
				ovr_ChallengeOptions_Destroy(challenge_options);
				Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
				String rejection_msg = "Invalid challenge options title value. Title must be a String.";
				return_promise->saved_rejection_response = Array::make(rejection_msg);
				_promises_to_reject.push_back(return_promise);

				return return_promise;
			}
		}

		if (p_challenge_options.has("leaderboard_name")) {
			if (p_challenge_options.get("leaderboard_name", 0).get_type() == Variant::STRING) {
				ovr_ChallengeOptions_SetLeaderboardName(challenge_options, ((String)p_challenge_options.get("leaderboard_name", "")).utf8().get_data());
			} else {
				ovr_ChallengeOptions_Destroy(challenge_options);
				Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
				String rejection_msg = "Invalid challenge options leaderboard_name value. Leaderboard name must be a String.";
				return_promise->saved_rejection_response = Array::make(rejection_msg);
				_promises_to_reject.push_back(return_promise);

				return return_promise;
			}
		}

		if (p_challenge_options.has("start_date")) {
			if (p_challenge_options.get("start_date", "").get_type() == Variant::INT) {
				ovr_ChallengeOptions_SetStartDate(challenge_options, ((uint64_t)p_challenge_options.get("start_date", 0)));
			} else {
				ovr_ChallengeOptions_Destroy(challenge_options);
				Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
				String rejection_msg = "Invalid challenge options start_date value. Start date must be an int.";
				return_promise->saved_rejection_response = Array::make(rejection_msg);
				_promises_to_reject.push_back(return_promise);

				return return_promise;
			}
		}

		if (p_challenge_options.has("end_date")) {
			if (p_challenge_options.get("end_date", "").get_type() == Variant::INT) {
				ovr_ChallengeOptions_SetEndDate(challenge_options, ((uint64_t)p_challenge_options.get("end_date", 0)));
			} else {
				ovr_ChallengeOptions_Destroy(challenge_options);
				Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
				String rejection_msg = "Invalid challenge options end_date value. End date must be an int.";
				return_promise->saved_rejection_response = Array::make(rejection_msg);
				_promises_to_reject.push_back(return_promise);

				return return_promise;
			}
		}

		if (p_challenge_options.has("viewer_filter")) {
			if (p_challenge_options.get("viewer_filter", "").get_type() == Variant::INT) {
				ovr_ChallengeOptions_SetViewerFilter(challenge_options, (ovrChallengeViewerFilter)((uint64_t)p_challenge_options.get("viewer_filter", 0)));
			} else {
				ovr_ChallengeOptions_Destroy(challenge_options);
				Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
				String rejection_msg = "Invalid challenge options viewer_filter value. Viewer filter must be a ChallengeVisibilityViewerFilter.";
				return_promise->saved_rejection_response = Array::make(rejection_msg);
				_promises_to_reject.push_back(return_promise);

				return return_promise;
			}
		}

		if (p_challenge_options.has("visibility")) {
			if (p_challenge_options.get("visibility", "").get_type() == Variant::INT) {
				ovr_ChallengeOptions_SetVisibility(challenge_options, (ovrChallengeVisibility)((uint64_t)p_challenge_options.get("visibility", 0)));
			} else {
				ovr_ChallengeOptions_Destroy(challenge_options);
				Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
				String rejection_msg = "Invalid challenge options visibility value. Visibility must be a ChallengeVisibility.";
				return_promise->saved_rejection_response = Array::make(rejection_msg);
				_promises_to_reject.push_back(return_promise);

				return return_promise;
			}
		}

		if (p_challenge_options.has("include_active_challenges")) {
			if (p_challenge_options.get("include_active_challenges", "").get_type() == Variant::BOOL) {
				ovr_ChallengeOptions_SetIncludeActiveChallenges(challenge_options, ((bool)p_challenge_options.get("include_active_challenges", true)));
			} else {
				ovr_ChallengeOptions_Destroy(challenge_options);
				Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
				String rejection_msg = "Invalid challenge options include_active_challenges value. Include active challenges must be an bool.";
				return_promise->saved_rejection_response = Array::make(rejection_msg);
				_promises_to_reject.push_back(return_promise);

				return return_promise;
			}
		}

		if (p_challenge_options.has("include_future_challenges")) {
			if (p_challenge_options.get("include_future_challenges", "").get_type() == Variant::BOOL) {
				ovr_ChallengeOptions_SetIncludeFutureChallenges(challenge_options, ((bool)p_challenge_options.get("include_future_challenges", false)));
			} else {
				ovr_ChallengeOptions_Destroy(challenge_options);
				Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
				String rejection_msg = "Invalid challenge options include_future_challenges value. Include future challenges must be an bool.";
				return_promise->saved_rejection_response = Array::make(rejection_msg);
				_promises_to_reject.push_back(return_promise);

				return return_promise;
			}
		}

		if (p_challenge_options.has("include_past_challenges")) {
			if (p_challenge_options.get("include_past_challenges", "").get_type() == Variant::BOOL) {
				ovr_ChallengeOptions_SetIncludePastChallenges(challenge_options, ((bool)p_challenge_options.get("include_past_challenges", false)));
			} else {
				ovr_ChallengeOptions_Destroy(challenge_options);
				Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
				String rejection_msg = "Invalid challenge options include_past_challenges value. Include past challenges must be an bool.";
				return_promise->saved_rejection_response = Array::make(rejection_msg);
				_promises_to_reject.push_back(return_promise);

				return return_promise;
			}
		}
	}

	ovrRequest req = ovr_Challenges_GetList(challenge_options, p_limit);
	ovr_ChallengeOptions_Destroy(challenge_options);

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests the entries from a challenge. Several filters can be applied.
/// @return A Dictionary that contains an array of entries.
Ref<GDOculusPlatformPromise> GDOculusPlatform::challenges_get_entries(const String &p_challenge_id, uint64_t p_limit, LeaderboardFilterType p_filter, LeaderboardStartAt p_start_at) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	if (p_limit < 0) {
		p_limit = 0;
	} else if (p_limit > INT32_MAX) {
		p_limit = INT32_MAX;
	}

	ovrID challenge_id;
	if (ovrID_FromString(&challenge_id, p_challenge_id.utf8().get_data())) {
		ovrRequest req = ovr_Challenges_GetEntries(challenge_id, p_limit, (ovrLeaderboardFilterType)p_filter, (ovrLeaderboardStartAt)p_start_at);

		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
		_promises.push_back(return_promise);

		return return_promise;

	} else {
		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
		String rejection_msg = "Invalid challenge ID.";
		return_promise->saved_rejection_response = Array::make(rejection_msg);
		_promises_to_reject.push_back(return_promise);

		return return_promise;
	}
}

/// Requests the entries from a challenge after a given rank.
/// @return A Dictionary that contains an array of entries.
Ref<GDOculusPlatformPromise> GDOculusPlatform::challenges_get_entries_after_rank(const String &p_challenge_id, uint64_t p_limit, uint64_t p_after_rank) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	if (p_limit < 0) {
		p_limit = 0;
	} else if (p_limit > INT32_MAX) {
		p_limit = INT32_MAX;
	}

	ovrID challenge_id;
	if (ovrID_FromString(&challenge_id, p_challenge_id.utf8().get_data())) {
		ovrRequest req = ovr_Challenges_GetEntriesAfterRank(challenge_id, p_limit, p_after_rank);

		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
		_promises.push_back(return_promise);

		return return_promise;

	} else {
		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
		String rejection_msg = "Invalid challenge ID.";
		return_promise->saved_rejection_response = Array::make(rejection_msg);
		_promises_to_reject.push_back(return_promise);

		return return_promise;
	}
}

/// Requests the entries from a challenge, but only including entries of the given user ids.
/// @return A Dictionary that contains an array of entries.
Ref<GDOculusPlatformPromise> GDOculusPlatform::challenges_get_entries_by_ids(const String &p_challenge_id, uint64_t p_limit, const Array &p_user_ids, LeaderboardStartAt p_start_at) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	if (p_limit < 0) {
		p_limit = 0;
	} else if (p_limit > INT32_MAX) {
		p_limit = INT32_MAX;
	}

	ovrID challenge_id;
	if (ovrID_FromString(&challenge_id, p_challenge_id.utf8().get_data())) {
		int64_t ids_arr_size = p_user_ids.size();

		ovrID *ovr_ids = memnew_arr(ovrID, ids_arr_size);
		std::vector<ovrID> sav(ids_arr_size);

		for (size_t j = 0; j < ids_arr_size; j++) {
			ovr_ids[j] = 0;
		}

		for (int i = 0; i < ids_arr_size; i++) {
			if (p_user_ids[i].get_type() == Variant::STRING) {
				ovrID_FromString(&sav[i], ((String)p_user_ids[i]).utf8().get_data());
				ovr_ids[i] = sav[i];

			} else {
				memdelete_arr(ovr_ids);
				Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
				String rejection_msg = "Invalid user ID found in array. All user IDs names must be Strings.";
				return_promise->saved_rejection_response = Array::make(rejection_msg);
				_promises_to_reject.push_back(return_promise);

				return return_promise;
			}
		}

		ovrRequest req = ovr_Challenges_GetEntriesByIds(challenge_id, p_limit, (ovrLeaderboardStartAt)p_start_at, ovr_ids, ids_arr_size);
		memdelete_arr(ovr_ids);

		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
		_promises.push_back(return_promise);

		return return_promise;

	} else {
		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
		String rejection_msg = "Invalid challenge ID.";
		return_promise->saved_rejection_response = Array::make(rejection_msg);
		_promises_to_reject.push_back(return_promise);

		return return_promise;
	}
}

/// Tries to join the user to a challenge.
/// @return A Dictionary with info about the challenge.
Ref<GDOculusPlatformPromise> GDOculusPlatform::challenges_join(const String &p_challenge_id) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrID challenge_id;
	if (ovrID_FromString(&challenge_id, p_challenge_id.utf8().get_data())) {
		ovrRequest req = ovr_Challenges_Join(challenge_id);

		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
		_promises.push_back(return_promise);

		return return_promise;

	} else {
		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
		String rejection_msg = "Invalid challenge ID.";
		return_promise->saved_rejection_response = Array::make(rejection_msg);
		_promises_to_reject.push_back(return_promise);

		return return_promise;
	}
}

/// Requests the user withdrawal from a challenge.
/// @return A Dictionary with info about the challenge.
Ref<GDOculusPlatformPromise> GDOculusPlatform::challenges_leave(const String &p_challenge_id) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrID challenge_id;
	if (ovrID_FromString(&challenge_id, p_challenge_id.utf8().get_data())) {
		ovrRequest req = ovr_Challenges_Leave(challenge_id);

		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
		_promises.push_back(return_promise);

		return return_promise;

	} else {
		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
		String rejection_msg = "Invalid challenge ID.";
		return_promise->saved_rejection_response = Array::make(rejection_msg);
		_promises_to_reject.push_back(return_promise);

		return return_promise;
	}
}

/// Declines an invite to join a challenge.
/// @return A Dictionary with info about the challenge.
Ref<GDOculusPlatformPromise> GDOculusPlatform::challenges_decline_invite(const String &p_challenge_id) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrID challenge_id;
	if (ovrID_FromString(&challenge_id, p_challenge_id.utf8().get_data())) {
		ovrRequest req = ovr_Challenges_DeclineInvite(challenge_id);

		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
		_promises.push_back(return_promise);

		return return_promise;

	} else {
		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
		String rejection_msg = "Invalid challenge ID.";
		return_promise->saved_rejection_response = Array::make(rejection_msg);
		_promises_to_reject.push_back(return_promise);

		return return_promise;
	}
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// GROUP PRESENCE
/////////////////////////////////////////////////

/// Ckears the group presence information.
/// @returns A promise that will alway contain a bool as true if the request was successful
Ref<GDOculusPlatformPromise> GDOculusPlatform::grouppresence_clear() {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_GroupPresence_Clear();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Sends invites to join the current user to an array of users by their IDs
/// @returns A promise that will contain a Dictionary with the invites that were sent
Ref<GDOculusPlatformPromise> GDOculusPlatform::grouppresence_send_invites(const Array &p_user_ids) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	int64_t ids_arr_size = p_user_ids.size();

	ovrID *ovr_ids = memnew_arr(ovrID, ids_arr_size);
	std::vector<ovrID> sav(ids_arr_size);

	for (size_t j = 0; j < ids_arr_size; j++) {
		ovr_ids[j] = 0;
	}

	for (int i = 0; i < ids_arr_size; i++) {
		if (p_user_ids[i].get_type() == Variant::STRING) {
			ovrID_FromString(&sav[i], ((String)p_user_ids[i]).utf8().get_data());
			ovr_ids[i] = sav[i];

		} else {
			memdelete_arr(ovr_ids);
			Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
			String rejection_msg = "Invalid user ID found in array. All user IDs must be Strings.";
			return_promise->saved_rejection_response = Array::make(rejection_msg);
			_promises_to_reject.push_back(return_promise);

			return return_promise;
		}
	}

	ovrRequest req = ovr_GroupPresence_SendInvites(ovr_ids, ids_arr_size);
	memdelete_arr(ovr_ids);

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Sets the group presence.
/// @returns A promise that will alway contain a bool as true if the request was successful
Ref<GDOculusPlatformPromise> GDOculusPlatform::grouppresence_set(const Dictionary &p_group_presence_options) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrGroupPresenceOptionsHandle presence_opts = ovr_GroupPresenceOptions_Create();
	if (p_group_presence_options.is_empty()) {
		ovr_GroupPresenceOptions_Destroy(presence_opts);
		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
		String rejection_msg = "Invalid group presence options. Cannot be empty.";
		return_promise->saved_rejection_response = Array::make(rejection_msg);
		_promises_to_reject.push_back(return_promise);

		return return_promise;

	} else {
		if (p_group_presence_options.has("deeplink_message_override")) {
			if (p_group_presence_options.get("deeplink_message_override", 0).get_type() == Variant::STRING) {
				ovr_GroupPresenceOptions_SetDeeplinkMessageOverride(presence_opts, ((String)p_group_presence_options.get("deeplink_message_override", "")).utf8().get_data());
			} else {
				ovr_GroupPresenceOptions_Destroy(presence_opts);
				Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
				String rejection_msg = "Invalid group presence options deeplink_message_override value. Must be a String.";
				return_promise->saved_rejection_response = Array::make(rejection_msg);
				_promises_to_reject.push_back(return_promise);

				return return_promise;
			}
		}

		if (p_group_presence_options.has("destination_api_name")) {
			if (p_group_presence_options.get("destination_api_name", 0).get_type() == Variant::STRING) {
				ovr_GroupPresenceOptions_SetDestinationApiName(presence_opts, ((String)p_group_presence_options.get("destination_api_name", "")).utf8().get_data());
			} else {
				ovr_GroupPresenceOptions_Destroy(presence_opts);
				Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
				String rejection_msg = "Invalid group presence options destination_api_name value. Must be a String.";
				return_promise->saved_rejection_response = Array::make(rejection_msg);
				_promises_to_reject.push_back(return_promise);

				return return_promise;
			}
		}

		if (p_group_presence_options.has("lobby_session_id")) {
			if (p_group_presence_options.get("lobby_session_id", 0).get_type() == Variant::STRING) {
				ovr_GroupPresenceOptions_SetLobbySessionId(presence_opts, ((String)p_group_presence_options.get("lobby_session_id", "")).utf8().get_data());
			} else {
				ovr_GroupPresenceOptions_Destroy(presence_opts);
				Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
				String rejection_msg = "Invalid group presence options lobby_session_id value. Must be a String.";
				return_promise->saved_rejection_response = Array::make(rejection_msg);
				_promises_to_reject.push_back(return_promise);

				return return_promise;
			}
		}

		if (p_group_presence_options.has("match_session_id")) {
			if (p_group_presence_options.get("match_session_id", 0).get_type() == Variant::STRING) {
				ovr_GroupPresenceOptions_SetMatchSessionId(presence_opts, ((String)p_group_presence_options.get("match_session_id", "")).utf8().get_data());
			} else {
				ovr_GroupPresenceOptions_Destroy(presence_opts);
				Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
				String rejection_msg = "Invalid group presence options match_session_id value. Must be a String.";
				return_promise->saved_rejection_response = Array::make(rejection_msg);
				_promises_to_reject.push_back(return_promise);

				return return_promise;
			}
		}

		if (p_group_presence_options.has("is_joinable")) {
			if (p_group_presence_options.get("is_joinable", "").get_type() == Variant::BOOL) {
				ovr_GroupPresenceOptions_SetIsJoinable(presence_opts, ((bool)p_group_presence_options.get("is_joinable", true)));
			} else {
				ovr_GroupPresenceOptions_Destroy(presence_opts);
				Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
				String rejection_msg = "Invalid group presence options is_joinable value. Must be an bool.";
				return_promise->saved_rejection_response = Array::make(rejection_msg);
				_promises_to_reject.push_back(return_promise);

				return return_promise;
			}
		}
	}

	ovrRequest req = ovr_GroupPresence_Set(presence_opts);
	ovr_GroupPresenceOptions_Destroy(presence_opts);

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Overrides the deeplink message. The user must have a destination, otherwise there will be no deeplink message to override
/// @returns A promise that will alway contain a bool as true if the request was successful
Ref<GDOculusPlatformPromise> GDOculusPlatform::grouppresence_set_deeplink_message_override(const String &p_deeplink_message) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_GroupPresence_SetDeeplinkMessageOverride(p_deeplink_message.utf8().get_data());

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Sets the destination from a given API name
/// @returns A promise that will alway contain a bool as true if the request was successful
Ref<GDOculusPlatformPromise> GDOculusPlatform::grouppresence_set_destination(const String &p_api_name) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_GroupPresence_SetDestination(p_api_name.utf8().get_data());

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Sets whether the current match/lobby is joinable
/// @returns A promise that will alway contain a bool as true if the request was successful
Ref<GDOculusPlatformPromise> GDOculusPlatform::grouppresence_set_is_joinable(bool p_is_joinable) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_GroupPresence_SetIsJoinable(p_is_joinable);

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Sets the lobby session from an ID
/// @returns A promise that will alway contain a bool as true if the request was successful
Ref<GDOculusPlatformPromise> GDOculusPlatform::grouppresence_set_lobby_session(const String &p_id) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_GroupPresence_SetLobbySession(p_id.utf8().get_data());

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Sets the match session from an ID
/// @returns A promise that will alway contain a bool as true if the request was successful
Ref<GDOculusPlatformPromise> GDOculusPlatform::grouppresence_set_match_session(const String &p_id) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_GroupPresence_SetMatchSession(p_id.utf8().get_data());

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests a list of users that can be invited to the current lobby/match.
/// @returns A promise that will contain a Dictionary with the users.
Ref<GDOculusPlatformPromise> GDOculusPlatform::grouppresence_get_invitable_users(const Dictionary &p_options) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrInviteOptionsHandle invite_opts_h = ovr_InviteOptions_Create();

	if (p_options.has("suggested_users")) {
		if (p_options.get("suggested_users", 0).get_type() == Variant::ARRAY) {
			int64_t users_arr_s = ((Array)p_options.get("suggested_users", "")).size();
			for (int64_t i = 0; i < users_arr_s; i++) {
				if (((Array)p_options["suggested_users"])[i].get_type() == Variant::STRING) {
					ovrID user_id;
					if (ovrID_FromString(&user_id, ((String)((Array)p_options["suggested_users"])[i]).utf8().get_data())) {
						ovr_InviteOptions_AddSuggestedUser(invite_opts_h, user_id);

					} else {
						ovr_InviteOptions_Destroy(invite_opts_h);
						Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
						String rejection_msg = "Invalid user ID found in suggested_users.";
						return_promise->saved_rejection_response = Array::make(rejection_msg);
						_promises_to_reject.push_back(return_promise);

						return return_promise;
					}

				} else {
					ovr_InviteOptions_Destroy(invite_opts_h);
					Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
					String rejection_msg = "Invalid invitable users options suggested_users value. Must be an Array of Strings.";
					return_promise->saved_rejection_response = Array::make(rejection_msg);
					_promises_to_reject.push_back(return_promise);

					return return_promise;
				}
			}

		} else {
			ovr_InviteOptions_Destroy(invite_opts_h);
			Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
			String rejection_msg = "Invalid invitable users options suggested_users value. Must be an Array of Strings.";
			return_promise->saved_rejection_response = Array::make(rejection_msg);
			_promises_to_reject.push_back(return_promise);

			return return_promise;
		}
	}

	ovrRequest req = ovr_GroupPresence_GetInvitableUsers(invite_opts_h);
	ovr_InviteOptions_Destroy(invite_opts_h);

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Sends a request to get the invites sent by the user
/// @returns A promise that will contain a Dictionary with the invites sent
Ref<GDOculusPlatformPromise> GDOculusPlatform::grouppresence_get_sent_invites() {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_GroupPresence_GetSentInvites();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Sends a request to launch an invite flow panel to invite other users to join the current user in their session.
/// @returns A promise that will contain a bool indicating whether the user did send invites or not
Ref<GDOculusPlatformPromise> GDOculusPlatform::grouppresence_launch_invite_panel(const Dictionary &p_options) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrInviteOptionsHandle invite_opts_h = ovr_InviteOptions_Create();

	if (p_options.has("suggested_users")) {
		if (p_options.get("suggested_users", 0).get_type() == Variant::ARRAY) {
			int64_t users_arr_s = ((Array)p_options.get("suggested_users", "")).size();
			for (int64_t i = 0; i < users_arr_s; i++) {
				if (((Array)p_options["suggested_users"])[i].get_type() == Variant::STRING) {
					ovrID user_id;
					if (ovrID_FromString(&user_id, ((String)((Array)p_options["suggested_users"])[i]).utf8().get_data())) {
						ovr_InviteOptions_AddSuggestedUser(invite_opts_h, user_id);

					} else {
						ovr_InviteOptions_Destroy(invite_opts_h);
						Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
						String rejection_msg = "Invalid user ID found in suggested_users.";
						return_promise->saved_rejection_response = Array::make(rejection_msg);
						_promises_to_reject.push_back(return_promise);

						return return_promise;
					}

				} else {
					ovr_InviteOptions_Destroy(invite_opts_h);
					Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
					String rejection_msg = "Invalid launch invite panel options suggested_users value. Must be an Array of Strings.";
					return_promise->saved_rejection_response = Array::make(rejection_msg);
					_promises_to_reject.push_back(return_promise);

					return return_promise;
				}
			}

		} else {
			ovr_InviteOptions_Destroy(invite_opts_h);
			Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
			String rejection_msg = "Invalid launch invite panel options suggested_users value. Must be an Array of Strings.";
			return_promise->saved_rejection_response = Array::make(rejection_msg);
			_promises_to_reject.push_back(return_promise);

			return return_promise;
		}
	}

	ovrRequest req = ovr_GroupPresence_LaunchInvitePanel(invite_opts_h);
	ovr_InviteOptions_Destroy(invite_opts_h);

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Sends a request to launch an error dialog with predefined messages.
/// @returns A promise that will contain a bool that will always be true in the request was successful
Ref<GDOculusPlatformPromise> GDOculusPlatform::grouppresence_launch_multiplayer_error_dialog(MultiplayerErrorErrorKey p_error_key) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrMultiplayerErrorOptionsHandle mult_err_opts_h = ovr_MultiplayerErrorOptions_Create();
	ovr_MultiplayerErrorOptions_SetErrorKey(mult_err_opts_h, (ovrMultiplayerErrorErrorKey)p_error_key);

	ovrRequest req = ovr_GroupPresence_LaunchMultiplayerErrorDialog(mult_err_opts_h);
	ovr_MultiplayerErrorOptions_Destroy(mult_err_opts_h);

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Sends a request to launch a panel that lets the user rejoin a previous lobby/match
/// @returns A promise that will contain a bool indicating whether the user did rejoin or not
Ref<GDOculusPlatformPromise> GDOculusPlatform::grouppresence_launch_rejoin_dialog(const String &p_lobby_session_id, const String &p_match_session_id, const String &p_destination_api_name) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_GroupPresence_LaunchRejoinDialog(p_lobby_session_id.utf8().get_data(), p_match_session_id.utf8().get_data(), p_destination_api_name.utf8().get_data());

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Sends a request to launch a panel that displays the current users in the roster.
/// @returns A promise that will contain a bool that will always be true in the request was successful
Ref<GDOculusPlatformPromise> GDOculusPlatform::grouppresence_launch_roster_panel(const Dictionary &p_options) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRosterOptionsHandle roster_opts_h = ovr_RosterOptions_Create();

	if (p_options.has("suggested_users")) {
		if (p_options.get("suggested_users", 0).get_type() == Variant::ARRAY) {
			int64_t users_arr_s = ((Array)p_options.get("suggested_users", "")).size();
			for (int64_t i = 0; i < users_arr_s; i++) {
				if (((Array)p_options["suggested_users"])[i].get_type() == Variant::STRING) {
					ovrID user_id;
					if (ovrID_FromString(&user_id, ((String)((Array)p_options["suggested_users"])[i]).utf8().get_data())) {
						ovr_RosterOptions_AddSuggestedUser(roster_opts_h, user_id);

					} else {
						ovr_RosterOptions_Destroy(roster_opts_h);
						Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
						String rejection_msg = "Invalid user ID found in suggested_users.";
						return_promise->saved_rejection_response = Array::make(rejection_msg);
						_promises_to_reject.push_back(return_promise);

						return return_promise;
					}

				} else {
					ovr_RosterOptions_Destroy(roster_opts_h);
					Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
					String rejection_msg = "Invalid launch roster panel options suggested_users value. Must be an Array of Strings.";
					return_promise->saved_rejection_response = Array::make(rejection_msg);
					_promises_to_reject.push_back(return_promise);

					return return_promise;
				}
			}

		} else {
			ovr_RosterOptions_Destroy(roster_opts_h);
			Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
			String rejection_msg = "Invalid launch roster panel options suggested_users value. Must be an Array of Strings.";
			return_promise->saved_rejection_response = Array::make(rejection_msg);
			_promises_to_reject.push_back(return_promise);

			return return_promise;
		}
	}

	ovrRequest req = ovr_GroupPresence_LaunchRosterPanel(roster_opts_h);
	ovr_RosterOptions_Destroy(roster_opts_h);

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// MEDIA
/////////////////////////////////////////////////

/// Sends a request to share a photo to facebook.
/// @returns A promise that will contain a Dictionary with information about the request to share media to facebook.
Ref<GDOculusPlatformPromise> GDOculusPlatform::media_share_to_facebook(const String &p_post_text_suggestion, const String &p_file_path, MediaContentType p_content_type) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_Media_ShareToFacebook(p_post_text_suggestion.utf8().get_data(), p_file_path.utf8().get_data(), (ovrMediaContentType)p_content_type);

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// USER AGE CATEGORY
/////////////////////////////////////////////////

/// Requests the user age category
/// @return Promise that will contain an enum of type AccountAgeCategory
Ref<GDOculusPlatformPromise> GDOculusPlatform::useragecategory_get() {
#ifndef __ANDROID__
	// Try to connect pump_messages to process
	if (!_try_connecting_process()) {
		return false;
	}
#endif
	ovrRequest req = ovr_UserAgeCategory_Get();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Reports the AppAgeCategory to the Oculus backend
/// @return Promise that will contain a bool (true) if the request was successful
Ref<GDOculusPlatformPromise> GDOculusPlatform::useragecategory_report(AppAgeCategory p_app_age_category) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_UserAgeCategory_Report((ovrAppAgeCategory)p_app_age_category);

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// DEVICE APPLICATION INTEGRITY
/////////////////////////////////////////////////

/// Requests the integrity token. Ref: https://developer.oculus.com/documentation/native/ps-attestation-api/
/// @return Promise that will contain a String with the integrity token
Ref<GDOculusPlatformPromise> GDOculusPlatform::deviceappintegrity_get_integrity_token(const String &p_challenge_nonce) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_DeviceApplicationIntegrity_GetIntegrityToken(p_challenge_nonce.utf8().get_data());

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// COWATCHING
/////////////////////////////////////////////////

/// Requests the presenter data.
/// @return Promise that will contain a String with the presenter data
Ref<GDOculusPlatformPromise> GDOculusPlatform::cowatch_get_presenter_data() {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_Cowatching_GetPresenterData();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests the viewer data.
/// @return Promise that will contain a String with the viewers data
Ref<GDOculusPlatformPromise> GDOculusPlatform::cowatch_get_viewers_data() {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_Cowatching_GetViewersData();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Queries if the user is in a cowatching session.
/// @return Promise that will contain a bool that defines if the user in in a cowatching session.
Ref<GDOculusPlatformPromise> GDOculusPlatform::cowatch_is_in_session() {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_Cowatching_IsInSession();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Tries to join the current cowatching session.
/// @return Promise that will be true if succesful.
Ref<GDOculusPlatformPromise> GDOculusPlatform::cowatch_join_session() {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_Cowatching_JoinSession();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Request cowatching invite dialog.
/// @return Promise that will be true if succesful.
Ref<GDOculusPlatformPromise> GDOculusPlatform::cowatch_launch_invite_dialog() {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_Cowatching_LaunchInviteDialog();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Tries to leave the current cowatching session.
/// @return Promise that will be true if succesful.
Ref<GDOculusPlatformPromise> GDOculusPlatform::cowatch_leave_session() {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_Cowatching_LeaveSession();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests presenting in the current cowatching session.
/// @return Promise that will be true if succesful.
Ref<GDOculusPlatformPromise> GDOculusPlatform::cowatch_request_to_present() {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_Cowatching_RequestToPresent();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests resigning from presenting from the current cowatching session.
/// @return Promise that will be true if succesful.
Ref<GDOculusPlatformPromise> GDOculusPlatform::cowatch_resign_from_presenting() {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	ovrRequest req = ovr_Cowatching_ResignFromPresenting();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Sets the presenter data (video title and description).
/// @return Promise that will be true if succesful.
Ref<GDOculusPlatformPromise> GDOculusPlatform::cowatch_set_presenter_data(const String &p_video_title, const String &p_presenter_data) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	if (p_video_title.length() > 100 || p_presenter_data.length() > 500) {
		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
		String rejection_msg = "Invalid presenter data. Video title cannot exceed 100 characters and presenter data is limited to 500 characters.";
		return_promise->saved_rejection_response = Array::make(rejection_msg);
		_promises_to_reject.push_back(return_promise);

		return return_promise;
	}

	ovrRequest req = ovr_Cowatching_SetPresenterData(p_video_title.utf8().get_data(), p_presenter_data.utf8().get_data());

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Sets the viewer data.
/// @return Promise that will be true if succesful.
Ref<GDOculusPlatformPromise> GDOculusPlatform::cowatch_set_viewer_data(const String &p_viewer_data) {
#ifndef __ANDROID__
	return _empty_func_helper();
#endif
	if (p_viewer_data.length() > 500) {
		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
		String rejection_msg = "Invalid viewer data. Viewer data is limited to 500 characters.";
		return_promise->saved_rejection_response = Array::make(rejection_msg);
		_promises_to_reject.push_back(return_promise);

		return return_promise;
	}

	ovrRequest req = ovr_Cowatching_SetViewerData(p_viewer_data.utf8().get_data());

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// INTERNAL PROCESSING METHODS
/////////////////////////////////////////////////

///// USERS
/////////////////////////////////////////////////

/// Processes android asynchronous initialization
void GDOculusPlatform::_process_initialize_platform_async(ovrMessageHandle p_message) {
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrPlatformInitializeHandle platform_init_resp = ovr_Message_GetPlatformInitialize(p_message);
		ovrPlatformInitializeResult platform_init_result = ovr_PlatformInitialize_GetResult(platform_init_resp);

		if (platform_init_result == ovrPlatformInitialize_Success) {
			_fulfill_promise(msg_id, Array::make(true));
		} else {
			String gd_message = ovrPlatformInitializeResult_ToString(platform_init_result);

			_reject_promise(msg_id, Array::make(gd_message));
		}

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

/// Processes entitlement check
void GDOculusPlatform::_process_user_get_is_viewer_entitled(ovrMessageHandle p_message) {
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		_fulfill_promise(msg_id, Array::make(true));
	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

/// Processes the user information and transforms it into a dictionary
void GDOculusPlatform::_process_user_get_logged_in_user(ovrMessageHandle p_message) {
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrUserHandle user_info_handle = ovr_Message_GetUser(p_message);
		Dictionary user_info_resp = _get_user_information(user_info_handle);

		_fulfill_promise(msg_id, Array::make(user_info_resp));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

/// Processes the response from the user's nonce request
void GDOculusPlatform::_process_user_get_user_proof(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrUserProofHandle user_proof = ovr_Message_GetUserProof(p_message);
		String user_nonce = ovr_UserProof_GetNonce(user_proof);

		_fulfill_promise(msg_id, Array::make(user_nonce));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

/// Processes an access token of the current user.
void GDOculusPlatform::_process_user_get_user_access_token(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		String access_token = ovr_Message_GetString(p_message);

		_fulfill_promise(msg_id, Array::make(access_token));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

/// Processes blocked user ids from current user. Paginated
void GDOculusPlatform::_process_user_get_blocked_users(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrBlockedUserArrayHandle blocked_users_handle = ovr_Message_GetBlockedUserArray(p_message);
		size_t blocked_users_array_size = ovr_BlockedUserArray_GetSize(blocked_users_handle);
		Array blocked_users = Array();

		for (size_t i = 0; i < blocked_users_array_size; i++) {
			ovrBlockedUserHandle blocked_user_handle = ovr_BlockedUserArray_GetElement(blocked_users_handle, i);

			char native_id[OVRID_SIZE];
			ovrID blocked_user_id = ovr_BlockedUser_GetId(blocked_user_handle);
			ovrID_ToString(native_id, OVRID_SIZE, blocked_user_id);
			blocked_users.push_back(String(native_id));
		}

		Dictionary response_dict;
		response_dict["data"] = blocked_users;
		response_dict["next_page_url"] = ovr_BlockedUserArray_GetNextUrl(blocked_users_handle);

		_fulfill_promise(msg_id, Array::make(response_dict));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

/// Processes user information about an array of users. Paginated
/// Used by: user_get_logged_in_user_friends
void GDOculusPlatform::_process_user_get_next_array_page(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrUserArrayHandle user_arr_h = ovr_Message_GetUserArray(p_message);
		size_t user_friends_array_size = ovr_UserArray_GetSize(user_arr_h);
		Array users = Array();

		for (size_t i = 0; i < user_friends_array_size; i++) {
			ovrUserHandle user_handle = ovr_UserArray_GetElement(user_arr_h, i);
			Dictionary user_info = _get_user_information(user_handle);

			users.push_back(user_info);
		}

		Dictionary response_dict;
		response_dict["data"] = users;
		response_dict["next_page_url"] = ovr_UserArray_GetNextUrl(user_arr_h);

		_fulfill_promise(msg_id, Array::make(response_dict));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

/// Processes the org scoped id of a given user
void GDOculusPlatform::_process_user_get_org_scoped_id(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrOrgScopedIDHandle org_scoped_id_handle = ovr_Message_GetOrgScopedID(p_message);

		char native_id[OVRID_SIZE];
		ovrID org_scoped_id = ovr_OrgScopedID_GetID(org_scoped_id_handle);
		ovrID_ToString(native_id, OVRID_SIZE, org_scoped_id);

		_fulfill_promise(msg_id, Array::make(String(native_id)));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

/// Processes sdk accounts (accounts in the headset) of the current user
void GDOculusPlatform::_process_user_get_sdk_accounts(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrSdkAccountArrayHandle accounts_array_handle = ovr_Message_GetSdkAccountArray(p_message);
		size_t accounts_size = ovr_SdkAccountArray_GetSize(accounts_array_handle);
		Array response_arr = Array();

		for (size_t i = 0; i < accounts_size; i++) {
			ovrSdkAccountHandle sdk_account_handle = ovr_SdkAccountArray_GetElement(accounts_array_handle, i);

			ovrSdkAccountType sdk_account_type = ovr_SdkAccount_GetAccountType(sdk_account_handle);
			ovrID sdk_user_id = ovr_SdkAccount_GetUserId(sdk_account_handle);

			char native_id[OVRID_SIZE];
			ovrID_ToString(native_id, OVRID_SIZE, sdk_user_id);

			Dictionary sdk_account_info;
			sdk_account_info["account_type"] = ovrSdkAccountType_ToString(sdk_account_type);
			sdk_account_info["account_id"] = String(native_id);

			response_arr.push_back(sdk_account_info);
		}

		_fulfill_promise(msg_id, Array::make(response_arr));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

/// Processes the result of the block flow. Returns a Dictionary.
void GDOculusPlatform::_process_user_launch_block_flow(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrLaunchBlockFlowResultHandle block_flow_result_handle = ovr_Message_GetLaunchBlockFlowResult(p_message);

		Dictionary block_flow_result;
		block_flow_result["did_block"] = ovr_LaunchBlockFlowResult_GetDidBlock(block_flow_result_handle);
		block_flow_result["did_cancel"] = ovr_LaunchBlockFlowResult_GetDidCancel(block_flow_result_handle);

		_fulfill_promise(msg_id, Array::make(block_flow_result));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

/// Processes the result of the unblock flow. Returns a Dictionary.
void GDOculusPlatform::_process_user_launch_unblock_flow(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrLaunchUnblockFlowResultHandle unblock_flow_result_handle = ovr_Message_GetLaunchUnblockFlowResult(p_message);

		Dictionary unblock_flow_result;
		unblock_flow_result["did_unblock"] = ovr_LaunchUnblockFlowResult_GetDidUnblock(unblock_flow_result_handle);
		unblock_flow_result["did_cancel"] = ovr_LaunchUnblockFlowResult_GetDidCancel(unblock_flow_result_handle);

		_fulfill_promise(msg_id, Array::make(unblock_flow_result));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

/// Processes the result of the friend request flow. Returns a Dictionary.
void GDOculusPlatform::_process_user_launch_friend_request_flow(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrLaunchFriendRequestFlowResultHandle friend_req_flow_result_handle = ovr_Message_GetLaunchFriendRequestFlowResult(p_message);

		Dictionary friend_req_flow_result;
		friend_req_flow_result["did_send_request"] = ovr_LaunchFriendRequestFlowResult_GetDidSendRequest(friend_req_flow_result_handle);
		friend_req_flow_result["did_cancel"] = ovr_LaunchFriendRequestFlowResult_GetDidCancel(friend_req_flow_result_handle);

		_fulfill_promise(msg_id, Array::make(friend_req_flow_result));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

///// ACHIEVEMENTS
/////////////////////////////////////////////////

/// Processes the response from a request to update an achievement. Returns a Dictionary if fulfilled
void GDOculusPlatform::_process_achievements_update(ovrMessageHandle p_message) {
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrAchievementUpdateHandle achievents_update_handle = ovr_Message_GetAchievementUpdate(p_message);
		Dictionary achievements_update_resp;

		achievements_update_resp["name"] = String(ovr_AchievementUpdate_GetName(achievents_update_handle));
		achievements_update_resp["just_unlocked"] = ovr_AchievementUpdate_GetJustUnlocked(achievents_update_handle);

		_fulfill_promise(msg_id, Array::make(achievements_update_resp));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

/// Processes the response from a request of achievements_get_all_definitions or achievements_get_definitions_by_name
void GDOculusPlatform::_process_achievements_definitions(ovrMessageHandle p_message) {
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrAchievementDefinitionArrayHandle achiev_defs_handle = ovr_Message_GetAchievementDefinitionArray(p_message);
		size_t achiev_defs_array_size = ovr_AchievementDefinitionArray_GetSize(achiev_defs_handle);

		Array achievement_defs = Array();

		for (size_t i = 0; i < achiev_defs_array_size; i++) {
			ovrAchievementDefinitionHandle achiev_def_handle = ovr_AchievementDefinitionArray_GetElement(achiev_defs_handle, i);
			Dictionary achiev_def;

			achiev_def["name"] = ovr_AchievementDefinition_GetName(achiev_def_handle);
			achiev_def["bitfield_length"] = ovr_AchievementDefinition_GetBitfieldLength(achiev_def_handle);
			achiev_def["target"] = (uint64_t)ovr_AchievementDefinition_GetTarget(achiev_def_handle);

			ovrAchievementType achiev_type = ovr_AchievementDefinition_GetType(achiev_def_handle);
			achiev_def["type"] = ovrAchievementType_ToString(achiev_type);

			achievement_defs.push_back(achiev_def);
		}

		Dictionary response_dict;
		response_dict["data"] = achievement_defs;
		response_dict["next_page_url"] = ovr_AchievementDefinitionArray_GetNextUrl(achiev_defs_handle);

		_fulfill_promise(msg_id, Array::make(response_dict));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

/// Processes the response from a request of achievements_get_all_progress or achievements_get_progress_by_name
void GDOculusPlatform::_process_achievements_progress(ovrMessageHandle p_message) {
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrAchievementProgressArrayHandle achievs_prog_handle = ovr_Message_GetAchievementProgressArray(p_message);
		size_t achievs_prog_array_size = ovr_AchievementProgressArray_GetSize(achievs_prog_handle);
		Array achiev_progs = Array();

		for (size_t i = 0; i < achievs_prog_array_size; i++) {
			ovrAchievementProgressHandle achiev_prog_handle = ovr_AchievementProgressArray_GetElement(achievs_prog_handle, i);
			Dictionary achiev_prog;

			achiev_prog["name"] = ovr_AchievementProgress_GetName(achiev_prog_handle);
			achiev_prog["current_count"] = (uint64_t)ovr_AchievementProgress_GetCount(achiev_prog_handle);
			achiev_prog["current_bitfield"] = ovr_AchievementProgress_GetBitfield(achiev_prog_handle);
			achiev_prog["is_unlocked"] = ovr_AchievementProgress_GetIsUnlocked(achiev_prog_handle);
			achiev_prog["unlock_time"] = (uint64_t)ovr_AchievementProgress_GetUnlockTime(achiev_prog_handle);

			achiev_progs.push_back(achiev_prog);
		}

		Dictionary response_dict;
		response_dict["data"] = achiev_progs;
		response_dict["next_page_url"] = ovr_AchievementProgressArray_GetNextUrl(achievs_prog_handle);

		_fulfill_promise(msg_id, Array::make(response_dict));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

///// IAP
/////////////////////////////////////////////////

/// Processes the response from a request to get the viewer purchases. Used for both durable cache only and all purchases
void GDOculusPlatform::_process_iap_viewer_purchases(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrPurchaseArrayHandle v_purchases_arr_handle = ovr_Message_GetPurchaseArray(p_message);
		size_t v_purchases_arr_s = ovr_PurchaseArray_GetSize(v_purchases_arr_handle);
		Array purchases_a = Array();

		for (size_t i = 0; i < v_purchases_arr_s; i++) {
			ovrPurchaseHandle v_purchase_handle = ovr_PurchaseArray_GetElement(v_purchases_arr_handle, i);
			Dictionary v_purchase;

			v_purchase["sku"] = ovr_Purchase_GetSKU(v_purchase_handle);
			v_purchase["reporting_id"] = ovr_Purchase_GetReportingId(v_purchase_handle);
			v_purchase["purchase_str_id"] = ovr_Purchase_GetPurchaseStrID(v_purchase_handle);
			v_purchase["grant_time"] = (uint64_t)ovr_Purchase_GetGrantTime(v_purchase_handle);
			v_purchase["expiration_time"] = (uint64_t)ovr_Purchase_GetExpirationTime(v_purchase_handle);
			v_purchase["developer_payload"] = ovr_Purchase_GetDeveloperPayload(v_purchase_handle);

			purchases_a.push_back(v_purchase);
		}

		Dictionary response_dict;
		response_dict["data"] = purchases_a;
		response_dict["next_page_url"] = ovr_PurchaseArray_GetNextUrl(v_purchases_arr_handle);

		_fulfill_promise(msg_id, Array::make(response_dict));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

/// Processes the response from a request to get products by SKU
void GDOculusPlatform::_process_iap_products(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrProductArrayHandle products_arr_handle = ovr_Message_GetProductArray(p_message);
		size_t products_arr_s = ovr_ProductArray_GetSize(products_arr_handle);

		Array products_arr = Array();

		for (size_t i = 0; i < products_arr_s; i++) {
			ovrProductHandle product_handle = ovr_ProductArray_GetElement(products_arr_handle, i);
			Dictionary product;

			product["sku"] = ovr_Product_GetSKU(product_handle);
			product["name"] = ovr_Product_GetName(product_handle);
			product["formatted_price"] = ovr_Product_GetFormattedPrice(product_handle);
			product["description"] = ovr_Product_GetDescription(product_handle);

			products_arr.push_back(product);
		}

		Dictionary response_dict;
		response_dict["data"] = products_arr;
		response_dict["next_page_url"] = ovr_ProductArray_GetNextUrl(products_arr_handle);

		_fulfill_promise(msg_id, Array::make(response_dict));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

/// Processes the result of a request to consume a consumable item
void GDOculusPlatform::_process_iap_consume_purchase(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		_fulfill_promise(msg_id, Array::make(true));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

/// Processes the result of the block flow. Returns a Dictionary with purchase_str_id empty if the user did not complete the purchase.
void GDOculusPlatform::_process_iap_launch_checkout_flow(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrPurchaseHandle purchase_handle = ovr_Message_GetPurchase(p_message);

		Dictionary purchase;

		purchase["sku"] = ovr_Purchase_GetSKU(purchase_handle);
		purchase["reporting_id"] = ovr_Purchase_GetReportingId(purchase_handle);
		purchase["purchase_str_id"] = ovr_Purchase_GetPurchaseStrID(purchase_handle);
		purchase["grant_time"] = (uint64_t)ovr_Purchase_GetGrantTime(purchase_handle);
		purchase["expiration_time"] = (uint64_t)ovr_Purchase_GetExpirationTime(purchase_handle);
		purchase["developer_payload"] = ovr_Purchase_GetDeveloperPayload(purchase_handle);

		_fulfill_promise(msg_id, Array::make(purchase));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

///// ASSET FILE
/////////////////////////////////////////////////

/// Processes the response from a request to get a list of asset files
void GDOculusPlatform::_process_assetfile_get_list(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrAssetDetailsArrayHandle assetfile_arr_handle = ovr_Message_GetAssetDetailsArray(p_message);
		size_t assetfile_arr_size = ovr_AssetDetailsArray_GetSize(assetfile_arr_handle);

		Array resp_arr = Array();

		for (size_t i = 0; i < assetfile_arr_size; i++) {
			ovrAssetDetailsHandle assetfile_handle = ovr_AssetDetailsArray_GetElement(assetfile_arr_handle, i);
			Dictionary assetfile;

			ovrID assetfile_id = ovr_AssetDetails_GetAssetId(assetfile_handle);
			char native_id[OVRID_SIZE];
			ovrID_ToString(native_id, OVRID_SIZE, assetfile_id);

			String assetfile_type = ovr_AssetDetails_GetAssetType(assetfile_handle);

			assetfile["id"] = String(native_id);
			assetfile["type"] = assetfile_type;
			assetfile["download_status"] = ovr_AssetDetails_GetDownloadStatus(assetfile_handle);
			assetfile["file_path"] = ovr_AssetDetails_GetFilepath(assetfile_handle);
			assetfile["iap_status"] = ovr_AssetDetails_GetIapStatus(assetfile_handle);
			assetfile["metadata"] = ovr_AssetDetails_GetMetadata(assetfile_handle);

			if (assetfile_type == "language_pack") {
				ovrLanguagePackInfoHandle language_handle = ovr_AssetDetails_GetLanguage(assetfile_handle);
				if (language_handle) {
					Dictionary language_info;

					language_info["english_name"] = ovr_LanguagePackInfo_GetEnglishName(language_handle);
					language_info["native_name"] = ovr_LanguagePackInfo_GetNativeName(language_handle);
					language_info["tag"] = ovr_LanguagePackInfo_GetTag(language_handle); // BCP47 format

					assetfile["language_info"] = language_info;
				} else {
					assetfile["language_info"] = Dictionary();
				}
			}

			resp_arr.push_back(assetfile);
		}

		_fulfill_promise(msg_id, Array::make(resp_arr));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

/// Processes the response from a request to get the status of a single asset file
void GDOculusPlatform::_process_assetfile_get_status(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrAssetDetailsHandle assetfile_handle = ovr_Message_GetAssetDetails(p_message);
		Dictionary assetfile;

		ovrID assetfile_id = ovr_AssetDetails_GetAssetId(assetfile_handle);
		char native_id[OVRID_SIZE];
		ovrID_ToString(native_id, OVRID_SIZE, assetfile_id);

		String assetfile_type = ovr_AssetDetails_GetAssetType(assetfile_handle);

		assetfile["id"] = String(native_id);
		assetfile["type"] = assetfile_type;
		assetfile["download_status"] = ovr_AssetDetails_GetDownloadStatus(assetfile_handle);
		assetfile["file_path"] = ovr_AssetDetails_GetFilepath(assetfile_handle);
		assetfile["iap_status"] = ovr_AssetDetails_GetIapStatus(assetfile_handle);
		assetfile["metadata"] = ovr_AssetDetails_GetMetadata(assetfile_handle);

		if (assetfile_type == "language_pack") {
			ovrLanguagePackInfoHandle language_handle = ovr_AssetDetails_GetLanguage(assetfile_handle);
			Dictionary language_info;

			language_info["english_name"] = ovr_LanguagePackInfo_GetEnglishName(language_handle);
			language_info["native_name"] = ovr_LanguagePackInfo_GetNativeName(language_handle);
			language_info["tag"] = ovr_LanguagePackInfo_GetTag(language_handle); // BCP47 format

			assetfile["language_info"] = language_info;
		}

		_fulfill_promise(msg_id, Array::make(assetfile));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

/// Processes the response from a request to download a single asset file
void GDOculusPlatform::_process_assetfile_download(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrAssetFileDownloadResultHandle assetfile_download_handle = ovr_Message_GetAssetFileDownloadResult(p_message);
		Dictionary assetfile_download_resp;

		ovrID assetfile_id = ovr_AssetFileDownloadResult_GetAssetId(assetfile_download_handle);
		char native_id[OVRID_SIZE];
		ovrID_ToString(native_id, OVRID_SIZE, assetfile_id);

		assetfile_download_resp["id"] = String(native_id);
		assetfile_download_resp["file_path"] = ovr_AssetFileDownloadResult_GetFilepath(assetfile_download_handle);

		_fulfill_promise(msg_id, Array::make(assetfile_download_resp));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

/// Processes the response from a request to cancel a download of a single asset file
void GDOculusPlatform::_process_assetfile_download_cancel(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrAssetFileDownloadCancelResultHandle assetfile_download_c_handle = ovr_Message_GetAssetFileDownloadCancelResult(p_message);
		Dictionary assetfile_download_c_resp;

		ovrID assetfile_id = ovr_AssetFileDownloadCancelResult_GetAssetId(assetfile_download_c_handle);
		char native_id[OVRID_SIZE];
		ovrID_ToString(native_id, OVRID_SIZE, assetfile_id);

		assetfile_download_c_resp["id"] = String(native_id);
		assetfile_download_c_resp["file_path"] = ovr_AssetFileDownloadCancelResult_GetFilepath(assetfile_download_c_handle);
		assetfile_download_c_resp["success"] = ovr_AssetFileDownloadCancelResult_GetSuccess(assetfile_download_c_handle);

		_fulfill_promise(msg_id, Array::make(assetfile_download_c_resp));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

/// Processes the response from a request to delete a single asset file
void GDOculusPlatform::_process_assetfile_delete(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrAssetFileDeleteResultHandle assetfile_delete_handle = ovr_Message_GetAssetFileDeleteResult(p_message);
		Dictionary assetfile_delete_resp;

		ovrID assetfile_id = ovr_AssetFileDeleteResult_GetAssetId(assetfile_delete_handle);
		char native_id[OVRID_SIZE];
		ovrID_ToString(native_id, OVRID_SIZE, assetfile_id);

		assetfile_delete_resp["id"] = String(native_id);
		assetfile_delete_resp["file_path"] = ovr_AssetFileDeleteResult_GetFilepath(assetfile_delete_handle);
		assetfile_delete_resp["success"] = ovr_AssetFileDeleteResult_GetSuccess(assetfile_delete_handle);

		_fulfill_promise(msg_id, Array::make(assetfile_delete_resp));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

///// LEADERBOARD
/////////////////////////////////////////////////

/// Processes the response from a request to get a single leaderboard
void GDOculusPlatform::_process_leaderboard_get(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrLeaderboardArrayHandle leaderboard_arr_handle = ovr_Message_GetLeaderboardArray(p_message);

		ovrLeaderboardHandle leaderboard_handle = ovr_LeaderboardArray_GetElement(leaderboard_arr_handle, 0);
		Dictionary leaderboard;

		char native_id[OVRID_SIZE];
		ovrID leaderboard_id = ovr_Leaderboard_GetID(leaderboard_handle);
		ovrID_ToString(native_id, OVRID_SIZE, leaderboard_id);

		leaderboard["id"] = String(native_id);
		leaderboard["api_name"] = ovr_Leaderboard_GetApiName(leaderboard_handle);

		ovrDestinationHandle destination_handle = ovr_Leaderboard_GetDestination(leaderboard_handle);
		if (destination_handle) {
			leaderboard["destination"] = _get_destionation_info(destination_handle);
		} else {
			leaderboard["destination"] = Dictionary();
		}

		_fulfill_promise(msg_id, Array::make(leaderboard));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

/// Processes the response from a request to get entries of a leaderboard. This function automatically paginates through the data
void GDOculusPlatform::_process_leaderboard_get_entries(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrLeaderboardEntryArrayHandle entries_arr_handle = ovr_Message_GetLeaderboardEntryArray(p_message);
		Array entries = _handle_leaderboard_entries(entries_arr_handle);

		Dictionary response_dict;
		response_dict["data"] = entries;
		response_dict["previous_page_url"] = ovr_LeaderboardEntryArray_GetPreviousUrl(entries_arr_handle);
		response_dict["next_page_url"] = ovr_LeaderboardEntryArray_GetNextUrl(entries_arr_handle);
		response_dict["total_count"] = (uint64_t)ovr_LeaderboardEntryArray_GetTotalCount(entries_arr_handle);

		_fulfill_promise(msg_id, Array::make(response_dict));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

/// Processes the response from a request to write an entry to a leaderboard
void GDOculusPlatform::_process_leaderboard_write_entry(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrLeaderboardUpdateStatusHandle leaderboard_update_handle = ovr_Message_GetLeaderboardUpdateStatus(p_message);
		Dictionary leaderboard_update;

		uint32_t challenges_ids_s = ovr_LeaderboardUpdateStatus_GetUpdatedChallengeIdsSize(leaderboard_update_handle);
		Array challenges_ids = Array();
		for (size_t i = 0; i < challenges_ids_s; i++) {
			ovrID challenge_id = ovr_LeaderboardUpdateStatus_GetUpdatedChallengeId(leaderboard_update_handle, i);
			char native_id[OVRID_SIZE];
			ovrID_ToString(native_id, OVRID_SIZE, challenge_id);

			challenges_ids.push_back(String(native_id));
		}

		leaderboard_update["did_update"] = ovr_LeaderboardUpdateStatus_GetDidUpdate(leaderboard_update_handle);
		leaderboard_update["challenge_ids"] = challenges_ids;

		_fulfill_promise(msg_id, Array::make(leaderboard_update));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

///// ABUSE REPORT
/////////////////////////////////////////////////

/// Processes report request handled [response]
void GDOculusPlatform::_process_abuse_report_handled(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		_fulfill_promise(msg_id, Array::make(true));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

///// APPLICATION
/////////////////////////////////////////////////

/// Processes the result of launching another app from the current app
void GDOculusPlatform::_process_application_launch_other_app(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		String msg = ovr_Message_GetString(p_message);
		_fulfill_promise(msg_id, Array::make(msg));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

/// Processes the result of the version launch request
void GDOculusPlatform::_process_application_get_version(ovrMessageHandle p_message) {
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrApplicationVersionHandle version_h = ovr_Message_GetApplicationVersion(p_message);

		Dictionary version_info;

		version_info["current_code"] = ovr_ApplicationVersion_GetCurrentCode(version_h);
		version_info["latest_code"] = ovr_ApplicationVersion_GetLatestCode(version_h);
		version_info["current_name"] = ovr_ApplicationVersion_GetCurrentName(version_h);
		version_info["latest_name"] = ovr_ApplicationVersion_GetLatestName(version_h);
		version_info["release_date"] = (int64_t)ovr_ApplicationVersion_GetReleaseDate(version_h);
		version_info["update_size"] = ovr_ApplicationVersion_GetSize(version_h);

		_fulfill_promise(msg_id, Array::make(version_info));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

/// Processes the result of starting to download an app update
/// Also used for the response from cancelling the download as they
/// return the same data.
/// Also used for install_app_and_relaunch since it returns the same data.
void GDOculusPlatform::_process_application_start_app_download(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrAppDownloadResultHandle download_result_h = ovr_Message_GetAppDownloadResult(p_message);

		Dictionary download_result_info;

		ovrAppInstallResult download_result = ovr_AppDownloadResult_GetAppInstallResult(download_result_h);
		int64_t timestamp = ovr_AppDownloadResult_GetTimestamp(download_result_h);

		download_result_info["install_result"] = ovrAppInstallResult_ToString(download_result);
		download_result_info["timestamp"] = timestamp;

		_fulfill_promise(msg_id, Array::make(download_result_info));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

/// Processes the result of requesting the app download progress
void GDOculusPlatform::_process_application_check_app_download_progress(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrAppDownloadProgressResultHandle download_progress_h = ovr_Message_GetAppDownloadProgressResult(p_message);

		Dictionary download_progress;

		download_progress["total_bytes"] = (int64_t)ovr_AppDownloadProgressResult_GetDownloadBytes(download_progress_h);
		download_progress["downloaded_bytes"] = (int64_t)ovr_AppDownloadProgressResult_GetDownloadedBytes(download_progress_h);

		ovrAppStatus status_code = ovr_AppDownloadProgressResult_GetStatusCode(download_progress_h);
		download_progress["status"] = ovrAppStatus_ToString(status_code);

		_fulfill_promise(msg_id, Array::make(download_progress));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

///// CHALLENGES
/////////////////////////////////////////////////

/// Processes the response from a request to get a single challenge.
/// Used by: challenges_get, challenges_join, challenges_leave, challenges_decline_invite
void GDOculusPlatform::_process_challenges_get(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrChallengeHandle challenge_h = ovr_Message_GetChallenge(p_message);

		Dictionary challenge = _get_challenge_information(challenge_h);

		_fulfill_promise(msg_id, Array::make(challenge));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

/// Processes the response from a request to get a a list of challenges
/// Used by: challenges_get_list
void GDOculusPlatform::_process_challenges_get_list(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrChallengeArrayHandle challenge_array_h = ovr_Message_GetChallengeArray(p_message);
		size_t challenge_arr_s = ovr_ChallengeArray_GetSize(challenge_array_h);
		Array challenges_arr = Array();

		for (size_t i = 0; i < challenge_arr_s; i++) {
			ovrChallengeHandle challenge_element = ovr_ChallengeArray_GetElement(challenge_array_h, i);
			Dictionary challenge = _get_challenge_information(challenge_element);

			challenges_arr.push_back(challenge);
		}

		Dictionary response_dict;
		response_dict["data"] = challenges_arr;
		response_dict["previous_page_url"] = ovr_ChallengeArray_GetPreviousUrl(challenge_array_h);
		response_dict["next_page_url"] = ovr_ChallengeArray_GetNextUrl(challenge_array_h);
		response_dict["total_count"] = (uint64_t)ovr_ChallengeArray_GetTotalCount(challenge_array_h);

		_fulfill_promise(msg_id, Array::make(response_dict));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

/// Processes the response from a request to get a a list of challenge entries
/// Used by: challenges_get_entries, challenges_get_entries_after_rank, challenges_get_entries_by_ids
void GDOculusPlatform::_process_challenges_get_entries(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrChallengeEntryArrayHandle challenge_e_array_h = ovr_Message_GetChallengeEntryArray(p_message);
		size_t challenge_e_arr_s = ovr_ChallengeEntryArray_GetSize(challenge_e_array_h);
		Array challenges_e_arr = Array();

		for (size_t i = 0; i < challenge_e_arr_s; i++) {
			ovrChallengeEntryHandle challenge_e_element = ovr_ChallengeEntryArray_GetElement(challenge_e_array_h, i);
			Dictionary challenge_entry = _get_challenge_entry_information(challenge_e_element);

			challenges_e_arr.push_back(challenge_entry);
		}

		Dictionary response_dict;
		response_dict["data"] = challenges_e_arr;
		response_dict["previous_page_url"] = ovr_ChallengeEntryArray_GetPreviousUrl(challenge_e_array_h);
		response_dict["next_page_url"] = ovr_ChallengeEntryArray_GetNextUrl(challenge_e_array_h);
		response_dict["total_count"] = (uint64_t)ovr_ChallengeEntryArray_GetTotalCount(challenge_e_array_h);

		_fulfill_promise(msg_id, Array::make(response_dict));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

///// GROUP PRESENCE
/////////////////////////////////////////////////

// Used to handle a request that has no payload, but could have an error.
void GDOculusPlatform::_process_groupresence_no_payload(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		_fulfill_promise(msg_id, Array::make(true));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

// Processes the response from a send_invites request. Will return a Dictionary with the invites that were created
void GDOculusPlatform::_process_groupresence_send_invites(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrSendInvitesResultHandle result = ovr_Message_GetSendInvitesResult(p_message);
		ovrApplicationInviteArrayHandle invites_arr_h = ovr_SendInvitesResult_GetInvites(result);
		size_t app_inv_arr_s = ovr_ApplicationInviteArray_GetSize(invites_arr_h);
		Array inv_array = Array();

		for (size_t i = 0; i < app_inv_arr_s; i++) {
			ovrApplicationInviteHandle app_inv_h = ovr_ApplicationInviteArray_GetElement(invites_arr_h, i);
			Dictionary single_app_invite;

			char native_id[OVRID_SIZE];
			ovrID app_invite_id = ovr_ApplicationInvite_GetID(app_inv_h);
			ovrID_ToString(native_id, OVRID_SIZE, app_invite_id);

			single_app_invite["id"] = String(native_id);
			single_app_invite["lobby_session_id"] = ovr_ApplicationInvite_GetLobbySessionId(app_inv_h);
			single_app_invite["match_session_id"] = ovr_ApplicationInvite_GetMatchSessionId(app_inv_h);
			single_app_invite["is_active"] = ovr_ApplicationInvite_GetIsActive(app_inv_h);

			ovrUserHandle user_h = ovr_ApplicationInvite_GetRecipient(app_inv_h);
			if (user_h) {
				Dictionary user_info = _get_user_information(user_h);
				single_app_invite["recipient"] = user_info;
			} else {
				single_app_invite["recipient"] = Dictionary();
			}

			ovrDestinationHandle dest_h = ovr_ApplicationInvite_GetDestination(app_inv_h);
			if (dest_h) {
				single_app_invite["destination"] = _get_destionation_info(dest_h);
			} else {
				single_app_invite["destination"] = Dictionary();
			}

			inv_array.push_back(single_app_invite);
		}

		Dictionary response_dict;
		response_dict["data"] = inv_array;
		response_dict["next_page_url"] = ovr_ApplicationInviteArray_GetNextUrl(invites_arr_h);

		_fulfill_promise(msg_id, Array::make(response_dict));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

// Processes the response from a invite panel launch request. Will inform if the user did send the invites
void GDOculusPlatform::_process_groupresence_launch_invite_panel(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrInvitePanelResultInfoHandle invite_panel_res_h = ovr_Message_GetInvitePanelResultInfo(p_message);
		bool invites_sent = ovr_InvitePanelResultInfo_GetInvitesSent(invite_panel_res_h);

		_fulfill_promise(msg_id, Array::make(invites_sent));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

// Processes the response from a rejoin panel launch request. Will inform if the user did rejoin
void GDOculusPlatform::_process_groupresence_launch_rejoin_panel(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrRejoinDialogResultHandle rejoin_panel_res_h = ovr_Message_GetRejoinDialogResult(p_message);
		bool did_rejoin = ovr_RejoinDialogResult_GetRejoinSelected(rejoin_panel_res_h);

		_fulfill_promise(msg_id, Array::make(did_rejoin));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

///// MEDIA
/////////////////////////////////////////////////

// Processes the response from a request to share media to facebook
void GDOculusPlatform::_process_media_share_to_facebook(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrShareMediaResultHandle share_media_result_h = ovr_Message_GetShareMediaResult(p_message);
		ovrShareMediaStatus share_media_status = ovr_ShareMediaResult_GetStatus(share_media_result_h);

		Dictionary share_media_resp;

		// UNKNOWN, SHARED, CANCELED
		share_media_resp["share_media_status"] = ovrShareMediaStatus_ToString(share_media_status);

		_fulfill_promise(msg_id, Array::make(share_media_resp));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

///// USER AGE CATEOGRY
/////////////////////////////////////////////////

/// Processes the result of requesting the user age category
void GDOculusPlatform::_process_useragecategory_get(ovrMessageHandle p_message) {
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrUserAccountAgeCategoryHandle useragecategory_h = ovr_Message_GetUserAccountAgeCategory(p_message);
		ovrAccountAgeCategory acc_age_category = ovr_UserAccountAgeCategory_GetAgeCategory(useragecategory_h);

		_fulfill_promise(msg_id, Array::make((AccountAgeCategory)acc_age_category));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

/// Processes the response from reporting the user age category
void GDOculusPlatform::_process_useragecategory_report(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		_fulfill_promise(msg_id, Array::make(true));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

///// DEVICE APPLICATION INTEGRITY
/////////////////////////////////////////////////

/// Processes the result of requesting an integrity token
void GDOculusPlatform::_process_deviceappintegrity_get_integrity_token(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		String integrity_token = ovr_Message_GetString(p_message);

		_fulfill_promise(msg_id, Array::make(integrity_token));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

///// COWATCHING
/////////////////////////////////////////////////

// Processes the retult of requesting the presenter data.
void GDOculusPlatform::_process_cowatch_get_presenter_data(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		String msg = ovr_Message_GetString(p_message);
		_fulfill_promise(msg_id, Array::make(msg));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

// Processes the retult of requesting the viewer data.
void GDOculusPlatform::_process_cowatch_get_viewers_data(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrCowatchViewerArrayHandle viewer_data_arr_h = ovr_Message_GetCowatchViewerArray(p_message);

		Dictionary viewer_data_result = _get_cowatching_viewers_data(viewer_data_arr_h);

		_fulfill_promise(msg_id, Array::make(viewer_data_result));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

// Processes the retult of quering if the user is in a cowatching session.
void GDOculusPlatform::_process_cowatch_is_in_session(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrCowatchingStateHandle cowatching_state_h = ovr_Message_GetCowatchingState(p_message);
		bool is_in_session = ovr_CowatchingState_GetInSession(cowatching_state_h);

		_fulfill_promise(msg_id, Array::make(is_in_session));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

// Processes the retult of requesting to join a cowatching session.
void GDOculusPlatform::_process_cowatch_join_session(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		_fulfill_promise(msg_id, Array::make(true));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

// Processes the retult of requesting to launch an invite dialog for a cowatching session.
void GDOculusPlatform::_process_cowatch_launch_invite_dialog(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		_fulfill_promise(msg_id, Array::make(true));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

// Processes the retult of requesting to leave the current cowatching session.
void GDOculusPlatform::_process_cowatch_leave_session(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		_fulfill_promise(msg_id, Array::make(true));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

// Processes the retult of requesting to present in the current cowatching session.
void GDOculusPlatform::_process_cowatch_request_to_present(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		_fulfill_promise(msg_id, Array::make(true));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

// Processes the retult of requesting to stop presenting in the current cowatching session.
void GDOculusPlatform::_process_cowatch_resign_from_presenting(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		_fulfill_promise(msg_id, Array::make(true));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

// Processes the retult of setting the presenter data.
void GDOculusPlatform::_process_cowatch_set_presenter_data(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		_fulfill_promise(msg_id, Array::make(true));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

// Processes the retult of setting the viewer data.
void GDOculusPlatform::_process_cowatch_set_viewer_data(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		_fulfill_promise(msg_id, Array::make(true));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

// Processes the retult of a notification when a viewer changes its data.
void GDOculusPlatform::_process_cowatch_viewer_data_changed(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	Dictionary viewer_data_changed_result;

	ovrCowatchViewerUpdateHandle viewer_update_h = ovr_Message_GetCowatchViewerUpdate(p_message);

	ovrCowatchViewerArrayHandle participants_data_arr_h = ovr_CowatchViewerUpdate_GetDataList(viewer_update_h);

	ovrID viewer_id = ovr_CowatchViewerUpdate_GetId(viewer_update_h);
	char native_id[OVRID_SIZE];
	ovrID_ToString(native_id, OVRID_SIZE, viewer_id);

	Dictionary viewers_data_dict = _get_cowatching_viewers_data(participants_data_arr_h);

	viewer_data_changed_result["updated_viewer_id"] = String(native_id);
	viewer_data_changed_result["all_viewers_data"] = viewers_data_dict;

	emit_signal("cowatch_viewers_data_changed", viewer_data_changed_result);
}

///// PROCESSING HELPERS
/////////////////////////////////////////////////

/// Handles unhandled messages
void GDOculusPlatform::_handle_unhandled_message(ovrMessageHandle message) {
	String gd_message = ovr_Message_GetString(message);

	ovrMessageType msg_type = ovr_Message_GetType(message);
	String gd_msg_type = ovrMessageType_ToString(msg_type);

	Dictionary gd_msg;
	gd_msg["type"] = gd_msg_type;
	gd_msg["message"] = gd_message;

	emit_signal("unhandled_message", gd_msg);
}

/// Helper function to handle most common errors when processing.
void GDOculusPlatform::_handle_default_process_error(ovrMessageHandle p_message, ovrRequest p_msg_id) {
	ovrErrorHandle ovr_err = ovr_Message_GetError(p_message);
	String gd_message = ovr_Error_GetMessage(ovr_err);

	JSON json = JSON();
	Variant result = json.parse_string(gd_message);

	if (result && result.get_type() == Variant::DICTIONARY) {
		_reject_promise(p_msg_id, Array::make(result));
	} else {
		_reject_promise(p_msg_id, Array::make(gd_message));
	}
}

// Helper function to get a Dictionary with information about a single user.
Dictionary GDOculusPlatform::_get_user_information(const ovrUserHandle &p_user_h) {
	Dictionary user_info_resp;
	Dictionary user_info_presence;

	user_info_resp["display_name"] = ovr_User_GetDisplayName(p_user_h);

	char native_id[OVRID_SIZE];
	ovrID u_id = ovr_User_GetID(p_user_h);
	ovrID_ToString(native_id, OVRID_SIZE, u_id);
	user_info_resp["id"] = String(native_id);

	user_info_resp["oculus_id"] = ovr_User_GetOculusID(p_user_h);
	user_info_resp["image_url"] = ovr_User_GetImageUrl(p_user_h);
	user_info_resp["small_image_url"] = ovr_User_GetSmallImageUrl(p_user_h);

	user_info_resp["presence"] = user_info_presence;
#ifdef MIC
	user_info_presence["presence_status"] = ovrUserPresenceStatus_ToString(ovr_User_GetPresenceStatus(p_user_h));
	user_info_presence["presence_deeplink_message"] = ovr_User_GetPresenceDeeplinkMessage(p_user_h);
	user_info_presence["presence_destination_api_name"] = ovr_User_GetPresenceDestinationApiName(p_user_h);
	user_info_presence["presence_lobby_session_id"] = ovr_User_GetPresenceLobbySessionId(p_user_h);
	user_info_presence["presence_match_session_id"] = ovr_User_GetPresenceMatchSessionId(p_user_h);
#endif

	return user_info_resp;
}

// Helper function to get information about a single challenge
Dictionary GDOculusPlatform::_get_challenge_information(const ovrChallengeHandle &p_challenge_h) {
	Dictionary challenge;

	char native_id[OVRID_SIZE];
	ovrID challenge_id = ovr_Challenge_GetID(p_challenge_h);
	ovrID_ToString(native_id, OVRID_SIZE, challenge_id);

	challenge["id"] = String(native_id);
	challenge["title"] = ovr_Challenge_GetTitle(p_challenge_h);
	challenge["description"] = ovr_Challenge_GetDescription(p_challenge_h);
	challenge["start_date"] = (uint64_t)ovr_Challenge_GetStartDate(p_challenge_h);
	challenge["end_date"] = (uint64_t)ovr_Challenge_GetEndDate(p_challenge_h);

	// PUBLIC, PRIVATE, INVITE_ONLY, UNKNOWN
	ovrChallengeVisibility challenge_v = ovr_Challenge_GetVisibility(p_challenge_h);
	challenge["visibility"] = ovrChallengeVisibility_ToString(challenge_v);

	// USER_CREATED, DEVELOPER_CREATED, UNKNOWN
	ovrChallengeCreationType challenge_t = ovr_Challenge_GetCreationType(p_challenge_h);
	challenge["type"] = ovrChallengeCreationType_ToString(challenge_t);

	ovrLeaderboardHandle challenge_l = ovr_Challenge_GetLeaderboard(p_challenge_h);
	Dictionary challenge_leaderboard;

	char native_cl_id[OVRID_SIZE];
	ovrID cl_id = ovr_Leaderboard_GetID(challenge_l);
	ovrID_ToString(native_cl_id, OVRID_SIZE, cl_id);
	challenge_leaderboard["id"] = String(native_cl_id);

	challenge_leaderboard["api_name"] = ovr_Leaderboard_GetApiName(challenge_l);

	ovrDestinationHandle cl_destination_h = ovr_Leaderboard_GetDestination(challenge_l);
	if (cl_destination_h) {
		challenge_leaderboard["destination"] = _get_destionation_info(cl_destination_h);
	} else {
		challenge_leaderboard["destination"] = Dictionary();
	}

	challenge["leaderboard"] = challenge_leaderboard;

	ovrUserArrayHandle invited_users_arr_h = ovr_Challenge_GetInvitedUsers(p_challenge_h);
	if (invited_users_arr_h) {
		size_t user_array_size = ovr_UserArray_GetSize(invited_users_arr_h);
		Array invited_users = Array();

		for (size_t i = 0; i < user_array_size; i++) {
			ovrUserHandle user_handle = ovr_UserArray_GetElement(invited_users_arr_h, i);
			Dictionary user_info = _get_user_information(user_handle);

			invited_users.push_back(user_info);
		}

		Dictionary response_dict;
		response_dict["data"] = invited_users;
		response_dict["next_page_url"] = ovr_UserArray_GetNextUrl(invited_users_arr_h);

		challenge["invited_users"] = response_dict;
	} else {
		Dictionary response_dict;
		response_dict["data"] = Array();
		response_dict["next_page_url"] = "";

		challenge["invited_users"] = response_dict;
	}

	ovrUserArrayHandle participants_array_h = ovr_Challenge_GetParticipants(p_challenge_h);
	if (participants_array_h) {
		size_t user_array_size = ovr_UserArray_GetSize(participants_array_h);
		Array participant_users = Array();

		for (size_t i = 0; i < user_array_size; i++) {
			ovrUserHandle user_handle = ovr_UserArray_GetElement(participants_array_h, i);
			Dictionary user_info = _get_user_information(user_handle);

			participant_users.push_back(user_info);
		}

		Dictionary response_dict;
		response_dict["data"] = participant_users;
		response_dict["next_page_url"] = ovr_UserArray_GetNextUrl(participants_array_h);

		challenge["participants"] = response_dict;
	} else {
		Dictionary response_dict;
		response_dict["data"] = Array();
		response_dict["next_page_url"] = "";

		challenge["participants"] = response_dict;
	}

	return challenge;
}

// Helper function to get information about a single challenge entry
Dictionary GDOculusPlatform::_get_challenge_entry_information(const ovrChallengeEntryHandle &p_challenge_entry_h) {
	Dictionary entry_data;

	ovrID entry_id = ovr_ChallengeEntry_GetID(p_challenge_entry_h);
	char native_id[OVRID_SIZE];
	ovrID_ToString(native_id, OVRID_SIZE, entry_id);

	entry_data["id"] = String(native_id);
	entry_data["rank"] = ovr_ChallengeEntry_GetRank(p_challenge_entry_h);
	entry_data["score"] = (int64_t)ovr_ChallengeEntry_GetScore(p_challenge_entry_h);
	entry_data["timestamp"] = (uint64_t)ovr_ChallengeEntry_GetTimestamp(p_challenge_entry_h);
	entry_data["display_score"] = ovr_ChallengeEntry_GetDisplayScore(p_challenge_entry_h);
	entry_data["extra_data"] = ovr_ChallengeEntry_GetExtraData(p_challenge_entry_h);

	ovrUserHandle user = ovr_ChallengeEntry_GetUser(p_challenge_entry_h);
	Dictionary user_info = _get_user_information(user);

	entry_data["user"] = user_info;

	return entry_data;
}

void GDOculusPlatform::_handle_download_update(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	if (!ovr_Message_IsError(p_message)) {
		ovrAssetFileDownloadUpdateHandle download_update_handle = ovr_Message_GetAssetFileDownloadUpdate(p_message);

		char native_id[OVRID_SIZE];
		ovrID asset_id = ovr_AssetFileDownloadUpdate_GetAssetId(download_update_handle);
		ovrID_ToString(native_id, OVRID_SIZE, asset_id);

		Dictionary resp;

		String download_asset_id = native_id;
		bool download_completed = ovr_AssetFileDownloadUpdate_GetCompleted(download_update_handle);

		resp["id"] = download_asset_id;
		resp["completed"] = download_completed;
		resp["total_bytes"] = (uint64_t)ovr_AssetFileDownloadUpdate_GetBytesTotalLong(download_update_handle);
		resp["transferred_bytes"] = (int64_t)ovr_AssetFileDownloadUpdate_GetBytesTransferredLong(download_update_handle);

		emit_signal("assetfile_download_update", resp);

		if (download_completed) {
			emit_signal("assetfile_download_finished", download_asset_id);
		}

	} else {
		ovrErrorHandle download_update_err = ovr_Message_GetError(p_message);
		String gd_message = ovr_Error_GetMessage(download_update_err);

		ovrMessageType msg_type = ovr_Message_GetType(p_message);
		String gd_msg_type = ovrMessageType_ToString(msg_type);

		Dictionary gd_msg;
		gd_msg["type"] = gd_msg_type;
		gd_msg["message"] = gd_message;

		emit_signal("unhandled_message", gd_msg);
	}
}

/// Helper function to handle the entries array handle
Array GDOculusPlatform::_handle_leaderboard_entries(const ovrLeaderboardEntryArrayHandle &p_entries_arr_h) {
	Array entries = Array();
	size_t entries_arr_s = ovr_LeaderboardEntryArray_GetSize(p_entries_arr_h);

	for (size_t i = 0; i < entries_arr_s; i++) {
		Dictionary entry_data;

		ovrLeaderboardEntryHandle entry_handle = ovr_LeaderboardEntryArray_GetElement(p_entries_arr_h, i);

		ovrID entry_id = ovr_LeaderboardEntry_GetID(entry_handle);
		char native_id[OVRID_SIZE];
		ovrID_ToString(native_id, OVRID_SIZE, entry_id);

		entry_data["id"] = String(native_id);
		entry_data["rank"] = ovr_LeaderboardEntry_GetRank(entry_handle);
		entry_data["score"] = (int64_t)ovr_LeaderboardEntry_GetScore(entry_handle);
		entry_data["timestamp"] = (uint64_t)ovr_LeaderboardEntry_GetTimestamp(entry_handle);
		entry_data["display_score"] = ovr_LeaderboardEntry_GetDisplayScore(entry_handle);
		entry_data["extra_data"] = ovr_LeaderboardEntry_GetExtraData(entry_handle);

		ovrUserHandle user = ovr_LeaderboardEntry_GetUser(entry_handle);
		Dictionary user_info = _get_user_information(user);

		ovrSupplementaryMetricHandle supplementary_metric_handle = ovr_LeaderboardEntry_GetSupplementaryMetric(entry_handle);
		if (supplementary_metric_handle) {
			Dictionary supplementary_metric;

			ovrID sup_metric_id = ovr_SupplementaryMetric_GetID(supplementary_metric_handle);
			char native_metric_id[OVRID_SIZE];
			ovrID_ToString(native_metric_id, OVRID_SIZE, sup_metric_id);

			supplementary_metric["id"] = String(native_metric_id);
			supplementary_metric["metric"] = (int64_t)ovr_SupplementaryMetric_GetMetric(supplementary_metric_handle);

			entry_data["supplementary_metric"] = supplementary_metric;
		} else {
			entry_data["supplementary_metric"] = Dictionary();
		}

		entry_data["user"] = user_info;

		entries.push_back(entry_data);
	}

	return entries;
}

// Helper that returns a Dictionary with information about a given destination
Dictionary GDOculusPlatform::_get_destionation_info(const ovrDestinationHandle &p_destination_h) {
	Dictionary destination;

	destination["display_name"] = ovr_Destination_GetDisplayName(p_destination_h);
	destination["shareable_uri"] = ovr_Destination_GetShareableUri(p_destination_h);
	destination["api_name"] = ovr_Destination_GetApiName(p_destination_h);
	destination["deep_link_message"] = ovr_Destination_GetDeeplinkMessage(p_destination_h);

	return destination;
}

// Processes the result mainly from a next_page request of a application invite array handle
void GDOculusPlatform::_handle_process_app_invite_array(ovrMessageHandle p_message) {
#ifndef __ANDROID__
	return;
#endif
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		ovrApplicationInviteArrayHandle invites_arr_h = ovr_Message_GetApplicationInviteArray(p_message);
		size_t app_inv_arr_s = ovr_ApplicationInviteArray_GetSize(invites_arr_h);
		Array inv_array = Array();

		for (size_t i = 0; i < app_inv_arr_s; i++) {
			ovrApplicationInviteHandle app_inv_h = ovr_ApplicationInviteArray_GetElement(invites_arr_h, i);
			Dictionary single_app_invite;

			char native_id[OVRID_SIZE];
			ovrID app_invite_id = ovr_ApplicationInvite_GetID(app_inv_h);
			ovrID_ToString(native_id, OVRID_SIZE, app_invite_id);

			single_app_invite["id"] = String(native_id);
			single_app_invite["lobby_session_id"] = ovr_ApplicationInvite_GetLobbySessionId(app_inv_h);
			single_app_invite["match_session_id"] = ovr_ApplicationInvite_GetMatchSessionId(app_inv_h);
			single_app_invite["is_active"] = ovr_ApplicationInvite_GetIsActive(app_inv_h);

			ovrUserHandle user_h = ovr_ApplicationInvite_GetRecipient(app_inv_h);
			if (user_h) {
				Dictionary user_info = _get_user_information(user_h);
				single_app_invite["recipient"] = user_info;
			} else {
				single_app_invite["recipient"] = Dictionary();
			}

			ovrDestinationHandle dest_h = ovr_ApplicationInvite_GetDestination(app_inv_h);
			if (dest_h) {
				single_app_invite["destination"] = _get_destionation_info(dest_h);
			} else {
				single_app_invite["destination"] = Dictionary();
			}

			inv_array.push_back(single_app_invite);
		}

		Dictionary response_dict;
		response_dict["data"] = inv_array;
		response_dict["next_page_url"] = ovr_ApplicationInviteArray_GetNextUrl(invites_arr_h);

		_fulfill_promise(msg_id, Array::make(response_dict));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

Dictionary GDOculusPlatform::_get_cowatching_viewers_data(const ovrCowatchViewerArrayHandle &p_viewer_array_handle) {
	Dictionary viewer_data_resp;
	size_t viewers_count = ovr_CowatchViewerArray_GetSize(p_viewer_array_handle);

	Array viewers_data_array = Array();
	for (size_t i = 0; i < viewers_count; i++) {
		Dictionary viewer_data;

		ovrCowatchViewerHandle viewer_h = ovr_CowatchViewerArray_GetElement(p_viewer_array_handle, i);

		ovrID viewer_id = ovr_CowatchViewer_GetId(viewer_h);
		char native_id[OVRID_SIZE];
		ovrID_ToString(native_id, OVRID_SIZE, viewer_id);

		String viewer_data_str = ovr_CowatchViewer_GetData(viewer_h);

		viewer_data["id"] = String(native_id);
		viewer_data["data"] = viewer_data_str;

		viewers_data_array.push_back(viewer_data);
	}

	viewer_data_resp["data"] = viewers_data_array;
	viewer_data_resp["next_page_url"] = ovr_CowatchViewerArray_GetNextUrl(p_viewer_array_handle);

	return viewer_data_resp;
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// OTHER METHODS
/////////////////////////////////////////////////

/// Gets the Java environment. Currently only used for platform initialization
#ifdef __ANDROID__
bool GDOculusPlatform::_get_env(JNIEnv **p_env) {
	ERR_FAIL_NULL_V_MSG(jvm, false, "[GDOP] JVM is null");
	jint res = jvm->GetEnv((void **)p_env, JNI_VERSION_1_6);
	if (res == JNI_EDETACHED) {
		res = jvm->AttachCurrentThread(p_env, NULL);
		if (res == JNI_OK) {
			return true;
		} else {
			*p_env = NULL;
			return false;
		}
	} else {
		return false;
	}
}
#endif

#ifdef __ANDROID__
extern "C" {
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
	JNIEnv *env;
	if (vm->GetEnv((void **)&env, JNI_VERSION_1_6) != JNI_OK)
		return JNI_ERR;
	jvm = vm;
	return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL Java_org_godot_godotoculusplatform_GodotOculusPlatform_initPlatform(JNIEnv *env, jobject obj, jobject activity) {
	jactivity = reinterpret_cast<jobject>(env->NewGlobalRef(activity));
}
}
#endif