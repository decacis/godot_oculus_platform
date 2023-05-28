#include <godot_oculus_platform.h>
#include <godot_cpp/core/class_db.hpp>

/*
This file is basically empty. Here, we only define the functions and signals
that you can call from GDScript because this plugin only works on Android.

When adding a new function that can be called from GDScript, you have to add it
to this file and to godot_oculus_platform_android.cpp as well. Here you can
skip the body of the function if it returns void, and return a default
value if it should return something.
*/

using namespace godot;

GDOculusPlatform *GDOculusPlatform::singleton = nullptr;

void GDOculusPlatform::_bind_methods() {
	ClassDB::bind_method(D_METHOD("pump_messages"), &GDOculusPlatform::pump_messages);

	// PAGINATION
	ClassDB::bind_method(D_METHOD("user_array_get_next_page", "user_array"), &GDOculusPlatform::user_array_get_next_page);
	ClassDB::bind_method(D_METHOD("leaderboard_entries_get_prev_page", "leaderboard_entries"), &GDOculusPlatform::leaderboard_entries_get_prev_page);
	ClassDB::bind_method(D_METHOD("leaderboard_entries_get_next_page", "leaderboard_entries"), &GDOculusPlatform::leaderboard_entries_get_next_page);
	ClassDB::bind_method(D_METHOD("challenge_array_get_prev_page", "challenge_array"), &GDOculusPlatform::challenge_array_get_prev_page);
	ClassDB::bind_method(D_METHOD("challenge_array_get_next_page", "challenge_array"), &GDOculusPlatform::challenge_array_get_next_page);
	ClassDB::bind_method(D_METHOD("challenge_entries_get_prev_page", "challenge_entries"), &GDOculusPlatform::challenge_entries_get_prev_page);
	ClassDB::bind_method(D_METHOD("challenge_entries_get_next_page", "challenge_entries"), &GDOculusPlatform::challenge_entries_get_next_page);

	// INITIALIZATION
	ClassDB::bind_method(D_METHOD("initialize_android", "app_id"), &GDOculusPlatform::initialize_android);
	ClassDB::bind_method(D_METHOD("initialize_android_async", "app_id"), &GDOculusPlatform::initialize_android_async);

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
	ClassDB::bind_method(D_METHOD("application_launch_other_app", "app_id", "deeplink_options"), &GDOculusPlatform::application_launch_other_app);
	ClassDB::bind_method(D_METHOD("application_get_launch_details"), &GDOculusPlatform::application_get_launch_details);

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

	ADD_SIGNAL(MethodInfo("unhandled_message", PropertyInfo(Variant::DICTIONARY, "message")));
	ADD_SIGNAL(MethodInfo("assetfile_download_update", PropertyInfo(Variant::DICTIONARY, "download_info")));
	ADD_SIGNAL(MethodInfo("assetfile_download_finished", PropertyInfo(Variant::STRING, "asset_id")));
	ADD_SIGNAL(MethodInfo("abouse_report_form_requested"));
	ADD_SIGNAL(MethodInfo("app_launch_intent_changed", PropertyInfo(Variant::STRING, "intent_type")));

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

void GDOculusPlatform::pump_messages() {}

Ref<GDOculusPlatformPromise> _empty_func_helper() {
	Ref<GDOculusPlatformPromise> promise;
	ERR_FAIL_V_MSG(promise, "Godot Oculus Platform only works with the Meta Quest (android).");
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::user_array_get_next_page(const Ref<GDOPUserArray> &p_user_array) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::leaderboard_entries_get_next_page(const Ref<GDOPLeaderboardEntries> &p_leaderboard_entries) {
	return _empty_func_helper();
}
Ref<GDOculusPlatformPromise> GDOculusPlatform::leaderboard_entries_get_prev_page(const Ref<GDOPLeaderboardEntries> &p_leaderboard_entries) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::challenge_array_get_next_page(const Ref<GDOPChallengeArray> &p_challenge_array) {
	return _empty_func_helper();
}
Ref<GDOculusPlatformPromise> GDOculusPlatform::challenge_array_get_prev_page(const Ref<GDOPChallengeArray> &p_challenge_array) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::challenge_entries_get_next_page(const Ref<GDOPChallengeEntries> &p_challenge_entries) {
	return _empty_func_helper();
}
Ref<GDOculusPlatformPromise> GDOculusPlatform::challenge_entries_get_prev_page(const Ref<GDOPChallengeEntries> &p_challenge_entries) {
	return _empty_func_helper();
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// PLATFORM INITIALIZATION
/////////////////////////////////////////////////

bool GDOculusPlatform::initialize_android(const String &p_app_id) {
	return false;
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::initialize_android_async(const String &p_app_id) {
	return _empty_func_helper();
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// USER
/////////////////////////////////////////////////

String GDOculusPlatform::user_get_logged_in_user_id() {
	String empty_str = "";
	return empty_str;
}

String GDOculusPlatform::user_get_logged_in_user_locale() {
	String empty_str = "";
	return empty_str;
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::user_get_is_viewer_entitled() {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::user_get_logged_in_user() {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::user_get_user(const String &p_user_id) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::user_get_user_proof() {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::user_get_user_access_token() {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::user_get_blocked_users() {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::user_get_logged_in_user_friends() {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::user_get_org_scoped_id(const String &p_user_id) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::user_get_sdk_accounts() {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::user_launch_block_flow(const String &p_user_id) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::user_launch_unblock_flow(const String &p_user_id) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::user_launch_friend_request_flow(const String &p_user_id) {
	return _empty_func_helper();
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// ACHIEVEMENTS
/////////////////////////////////////////////////

Ref<GDOculusPlatformPromise> GDOculusPlatform::achievements_add_count(const String &p_achievement_name, uint64_t p_count) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::achievements_add_fields(const String &p_achievement_name, const String &p_fields) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::achievements_unlock(const String &p_achievement_name) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::achievements_get_all_definitions() {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::achievements_get_all_progress() {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::achievements_get_definitions_by_name(const Array &p_achievement_names) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::achievements_get_progress_by_name(const Array &p_achievement_names) {
	return _empty_func_helper();
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// IAP
/////////////////////////////////////////////////

Ref<GDOculusPlatformPromise> GDOculusPlatform::iap_get_viewer_purchases() {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::iap_get_products_by_sku(const Array &p_sku_list) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::iap_consume_purchase(const String &p_sku) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::iap_launch_checkout_flow(const String &p_sku) {
	return _empty_func_helper();
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// ASSET FILE
/////////////////////////////////////////////////

Ref<GDOculusPlatformPromise> GDOculusPlatform::assetfile_get_list() {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::assetfile_status_by_id(const String &p_asset_id) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::assetfile_status_by_name(const String &p_asset_name) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::assetfile_download_by_id(const String &p_asset_id) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::assetfile_download_by_name(const String &p_asset_name) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::assetfile_download_cancel_by_id(const String &p_asset_id) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::assetfile_download_cancel_by_name(const String &p_asset_name) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::assetfile_delete_by_id(const String &p_asset_id) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::assetfile_delete_by_name(const String &p_asset_name) {
	return _empty_func_helper();
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// LEADERBOARD
/////////////////////////////////////////////////

Ref<GDOculusPlatformPromise> GDOculusPlatform::leaderboard_get(const String &p_leaderboard_name) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::leaderboard_get_entries(const String &p_leaderboard_name, uint64_t p_limit, LeaderboardFilterType p_filter, LeaderboardStartAt p_start_at) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::leaderboard_get_entries_after_rank(const String &p_leaderboard_name, uint64_t p_limit, uint64_t p_after_rank) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::leaderboard_get_entries_by_ids(const String &p_leaderboard_name, uint64_t p_limit, const Array &p_user_ids, LeaderboardStartAt p_start_at) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::leaderboard_write_entry(const String &p_leaderboard_name, uint64_t p_score, bool p_force_update, const Dictionary &p_extra) {
	return _empty_func_helper();
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// ABUSE REPORT
/////////////////////////////////////////////////

Ref<GDOculusPlatformPromise> GDOculusPlatform::abuse_report_request_handled(ReportRequestResponse p_report_req_resp) {
	return _empty_func_helper();
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// APPLICATION
/////////////////////////////////////////////////

Ref<GDOculusPlatformPromise> GDOculusPlatform::application_get_version() {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::application_launch_other_app(const String &p_app_id, const Dictionary &p_deeplink_options) {
	return _empty_func_helper();
};

Dictionary GDOculusPlatform::application_get_launch_details() {
	return Dictionary();
};

/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// CHALLENGES
/////////////////////////////////////////////////

Ref<GDOculusPlatformPromise> GDOculusPlatform::challenges_get(const String &p_challenge_id) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::challenges_get_list(uint64_t p_limit, const Dictionary &p_challenge_options) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::challenges_get_entries(const String &p_challenge_id, uint64_t p_limit, LeaderboardFilterType p_filter, LeaderboardStartAt p_start_at) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::challenges_get_entries_after_rank(const String &p_challenge_id, uint64_t p_limit, uint64_t p_after_rank) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::challenges_get_entries_by_ids(const String &p_challenge_id, uint64_t p_limit, const Array &p_user_ids, LeaderboardStartAt p_start_at) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::challenges_join(const String &p_challenge_id) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::challenges_leave(const String &p_challenge_id) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::challenges_decline_invite(const String &p_challenge_id) {
	return _empty_func_helper();
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// GROUP PRESENCE
/////////////////////////////////////////////////

Ref<GDOculusPlatformPromise> GDOculusPlatform::grouppresence_clear() {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::grouppresence_send_invites(const Array &p_user_ids) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::grouppresence_set(const Dictionary &p_group_presence_options) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::grouppresence_set_deeplink_message_override(const String &p_deeplink_message) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::grouppresence_set_destination(const String &p_api_name) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::grouppresence_set_is_joinable(bool p_is_joinable) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::grouppresence_set_lobby_session(const String &p_id) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::grouppresence_set_match_session(const String &p_id) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::grouppresence_get_invitable_users(const Dictionary &p_options) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::grouppresence_get_sent_invites() {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::grouppresence_launch_invite_panel(const Dictionary &p_options) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::grouppresence_launch_multiplayer_error_dialog(MultiplayerErrorErrorKey p_error_key) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::grouppresence_launch_rejoin_dialog(const String &p_lobby_session_id, const String &p_match_session_id, const String &p_destination_api_name) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::grouppresence_launch_roster_panel(const Dictionary &p_options) {
	return _empty_func_helper();
}
