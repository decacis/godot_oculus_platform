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
	ClassDB::bind_method(D_METHOD("leaderboard_write_entry", "leaderboard_name", "score", "force_update", "extra_data"), &GDOculusPlatform::leaderboard_write_entry);
	ClassDB::bind_method(D_METHOD("leaderboard_write_entry_with_supplementary_metric", "leaderboard_name", "score", "supplementary_metric", "force_update", "extra_data"), &GDOculusPlatform::leaderboard_write_entry_with_supplementary_metric);

	ADD_SIGNAL(MethodInfo("unhandled_message", PropertyInfo(Variant::DICTIONARY, "message")));
	ADD_SIGNAL(MethodInfo("assetfile_download_update", PropertyInfo(Variant::DICTIONARY, "download_info")));
	ADD_SIGNAL(MethodInfo("assetfile_download_finished", PropertyInfo(Variant::STRING, "asset_id")));

	BIND_ENUM_CONSTANT(LEADERBOARD_FILTER_TYPE_NONE);		// 0
	BIND_ENUM_CONSTANT(LEADERBOARD_FILTER_TYPE_FRIENDS);	// 1
	BIND_ENUM_CONSTANT(LEADERBOARD_FILTER_TYPE_UNKNOWN);	// 2
	BIND_ENUM_CONSTANT(LEADERBOARD_FILTER_TYPE_USER_IDS);	// 3

	BIND_ENUM_CONSTANT(LEADERBOARD_START_AT_TOP);						// 0
	BIND_ENUM_CONSTANT(LEADERBOARD_START_AT_CENTERED_ON_VIEWER);		// 1
	BIND_ENUM_CONSTANT(LEADERBOARD_START_AT_CENTERED_ON_VIEWER_OR_TOP);	// 2
	BIND_ENUM_CONSTANT(LEADERBOARD_START_AT_UNKNOWN);					// 3
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

/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// PLATFORM INITIALIZATION
/////////////////////////////////////////////////

bool GDOculusPlatform::initialize_android(String p_app_id) {
	return false;
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::initialize_android_async(String p_app_id) {
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

Ref<GDOculusPlatformPromise> GDOculusPlatform::user_get_user(String p_user_id) {
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

Ref<GDOculusPlatformPromise> GDOculusPlatform::user_get_org_scoped_id(String p_user_id) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::user_get_sdk_accounts() {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::user_launch_block_flow(String p_user_id) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::user_launch_unblock_flow(String p_user_id) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::user_launch_friend_request_flow(String p_user_id) {
	return _empty_func_helper();
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// ACHIEVEMENTS
/////////////////////////////////////////////////

Ref<GDOculusPlatformPromise> GDOculusPlatform::achievements_add_count(String p_achievement_name, uint64_t p_count) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::achievements_add_fields(String p_achievement_name, String p_fields) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::achievements_unlock(String p_achievement_name) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::achievements_get_all_definitions() {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::achievements_get_all_progress() {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::achievements_get_definitions_by_name(Array p_achievement_names) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::achievements_get_progress_by_name(Array p_achievement_names) {
	return _empty_func_helper();
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// IAP
/////////////////////////////////////////////////

Ref<GDOculusPlatformPromise> GDOculusPlatform::iap_get_viewer_purchases() {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::iap_get_products_by_sku(Array p_sku_list) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::iap_consume_purchase(String p_sku) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::iap_launch_checkout_flow(String p_sku) {
	return _empty_func_helper();
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// ASSET FILE
/////////////////////////////////////////////////

Ref<GDOculusPlatformPromise> GDOculusPlatform::assetfile_get_list() {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::assetfile_status_by_id(String p_asset_id) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::assetfile_status_by_name(String p_asset_name) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::assetfile_download_by_id(String p_asset_id) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::assetfile_download_by_name(String p_asset_name) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::assetfile_download_cancel_by_id(String p_asset_id) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::assetfile_download_cancel_by_name(String p_asset_name) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::assetfile_delete_by_id(String p_asset_id) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::assetfile_delete_by_name(String p_asset_name) {
	return _empty_func_helper();
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// LEADERBOARD
/////////////////////////////////////////////////

Ref<GDOculusPlatformPromise> GDOculusPlatform::leaderboard_get(String p_leaderboard_name) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::leaderboard_get_entries(String p_leaderboard_name, uint64_t p_limit, LeaderboardFilterType p_filter, LeaderboardStartAt p_start_at) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::leaderboard_get_entries_after_rank(String p_leaderboard_name, uint64_t p_limit, uint64_t p_after_rank) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::leaderboard_get_entries_by_ids(String p_leaderboard_name, uint64_t p_limit, LeaderboardStartAt p_start_at, Array p_user_ids) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::leaderboard_write_entry(String p_leaderboard_name, uint64_t p_score, bool p_force_update, String p_extra_data) {
	return _empty_func_helper();
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::leaderboard_write_entry_with_supplementary_metric(String p_leaderboard_name, uint64_t p_score, uint64_t p_supplementary_metric, bool p_force_update, String p_extra_data) {
	return _empty_func_helper();
}
