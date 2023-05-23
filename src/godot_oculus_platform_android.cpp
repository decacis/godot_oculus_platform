#include <godot_oculus_platform.h>
#include <godot_cpp/classes/json.hpp>
#include <godot_cpp/core/class_db.hpp>

#define OVRID_SIZE 21

static JavaVM *jvm;
static jobject jactivity;

using namespace godot;

GDOculusPlatform *GDOculusPlatform::singleton = nullptr;

void GDOculusPlatform::_bind_methods() {
	ClassDB::bind_method(D_METHOD("pump_messages"), &GDOculusPlatform::pump_messages);

	ClassDB::bind_method(D_METHOD("user_array_get_next_page", "user_array"), &GDOculusPlatform::user_array_get_next_page);
	ClassDB::bind_method(D_METHOD("leaderboard_entries_get_prev_page", "leaderboard_entries"), &GDOculusPlatform::leaderboard_entries_get_prev_page);
	ClassDB::bind_method(D_METHOD("leaderboard_entries_get_next_page", "leaderboard_entries"), &GDOculusPlatform::leaderboard_entries_get_next_page);

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

	ADD_SIGNAL(MethodInfo("unhandled_message", PropertyInfo(Variant::DICTIONARY, "message")));
	ADD_SIGNAL(MethodInfo("assetfile_download_update", PropertyInfo(Variant::DICTIONARY, "download_info")));
	ADD_SIGNAL(MethodInfo("assetfile_download_finished", PropertyInfo(Variant::STRING, "asset_id")));
	ADD_SIGNAL(MethodInfo("abouse_report_form_requested"));
	ADD_SIGNAL(MethodInfo("app_launch_intent_changed", PropertyInfo(Variant::STRING, "intent_type")));

	BIND_ENUM_CONSTANT(LEADERBOARD_FILTER_TYPE_NONE); // 0
	BIND_ENUM_CONSTANT(LEADERBOARD_FILTER_TYPE_FRIENDS); // 1

	BIND_ENUM_CONSTANT(LEADERBOARD_START_AT_TOP); // 0
	BIND_ENUM_CONSTANT(LEADERBOARD_START_AT_CENTERED_ON_VIEWER); // 1

	BIND_ENUM_CONSTANT(REPORT_REQUEST_HANDLED); // 1
	BIND_ENUM_CONSTANT(REPORT_REQUEST_UNHANDLED); // 2
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

/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// INTERNAL METHODS
/////////////////////////////////////////////////

/// Retrieve existing promise from ID.
bool GDOculusPlatform::_get_promise(uint64_t p_promise_id, Ref<GDOculusPlatformPromise> &p_promise) {
	for (auto &p : _promises) {
		if (p->has_id(p_promise_id)) {
			p_promise = p;
			return true;
		}
	}

	ERR_FAIL_V_MSG(false, vformat("Unable to get promise with ID: %s", p_promise_id));
}

bool GDOculusPlatform::_fulfill_promise(uint64_t p_promise_id, Array val) {
	for (auto &p : _promises) {
		if (p->has_id(p_promise_id)) {
			p->fulfill(val);
			_promises.erase(p);
			return true;
		}
	}

	ERR_FAIL_V_MSG(false, vformat("Unable to fulfill promise with ID: %s", p_promise_id));
}

bool GDOculusPlatform::_reject_promise(uint64_t p_promise_id, Array val) {
	for (auto &p : _promises) {
		if (p->has_id(p_promise_id)) {
			p->reject(val);
			_promises.erase(p);
			return true;
		}
	}

	ERR_FAIL_V_MSG(false, vformat("Unable to reject promise with ID: %s", p_promise_id));
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

Ref<GDOculusPlatformPromise> GDOculusPlatform::user_array_get_next_page(Ref<GDOPUserArray> p_user_array) {
	if (p_user_array->get_has_next_page()) {
		ovrRequest req = ovr_User_GetNextUserArrayPage(p_user_array->array_handle);

		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
		_promises.push_back(return_promise);

		return return_promise;
	} else {
		WARN_PRINT_ED("GDOPUserArray does not have a next page. Returning same GDOPUserArray.");

		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_fulfill_promise_id()));
		return_promise->saved_fulfill_response = Array::make(p_user_array);
		_promises_to_fulfill.push_back(return_promise);

		return return_promise;
	}
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::leaderboard_entries_get_next_page(Ref<GDOPLeaderboardEntries> p_leaderboard_entries) {
	if (p_leaderboard_entries->get_has_next_page()) {
		ovrRequest req = ovr_Leaderboard_GetNextEntries(p_leaderboard_entries->array_handle);

		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
		_promises.push_back(return_promise);

		return return_promise;
	} else {
		WARN_PRINT_ED("GDOPLeaderboardEntries does not have a next page. Returning same GDOPLeaderboardEntries.");

		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_fulfill_promise_id()));
		return_promise->saved_fulfill_response = Array::make(p_leaderboard_entries);
		_promises_to_fulfill.push_back(return_promise);

		return return_promise;
	}
}

Ref<GDOculusPlatformPromise> GDOculusPlatform::leaderboard_entries_get_prev_page(Ref<GDOPLeaderboardEntries> p_leaderboard_entries) {
	if (p_leaderboard_entries->get_has_prev_page()) {
		ovrRequest req = ovr_Leaderboard_GetPreviousEntries(p_leaderboard_entries->array_handle);

		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
		_promises.push_back(return_promise);

		return return_promise;
	} else {
		WARN_PRINT_ED("GDOPLeaderboardEntries does not have a previous page. Returning same GDOPLeaderboardEntries.");

		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_fulfill_promise_id()));
		return_promise->saved_fulfill_response = Array::make(p_leaderboard_entries);
		_promises_to_fulfill.push_back(return_promise);

		return return_promise;
	}
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
				_process_initialize_android_async(message);
				break;

			case ovrMessage_Entitlement_GetIsViewerEntitled:
				_process_user_get_is_viewer_entitled(message);
				break;

			case ovrMessage_User_GetLoggedInUser:
				_process_user_get_logged_in_user(message);
				break;

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
				_process_user_get_logged_in_user_friends(message);
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

				// case ovrMessage_Leaderboard_GetNextLeaderboardArrayPage:
				// 	_process_leaderboard_get(message);
				// 	break;

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
				emit_signal("abouse_report_form_requested");
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

			case ovrMessage_Notification_ApplicationLifecycle_LaunchIntentChanged:
				emit_signal("app_launch_intent_changed", String(ovr_Message_GetString(message)));
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

/// Initialize Android Oculus Platform synchronously.
bool GDOculusPlatform::initialize_android(String p_app_id) {
	if (!ovr_IsPlatformInitialized()) {
		JNIEnv *gdjenv;
		_get_env(&gdjenv);

		if (ovr_PlatformInitializeAndroid(p_app_id.utf8().get_data(), jactivity, gdjenv) == ovrPlatformInitialize_Success) {
			return true;
		}

		return false;

	} else {
		return true;
	}
}

/// Initialize Android Oculus Platform asynchronously.
/// @param p_app_id App ID
/// @return Promise to be resolved when the platform finishes initializing
Ref<GDOculusPlatformPromise> GDOculusPlatform::initialize_android_async(String p_app_id) {
	JNIEnv *gdjenv;
	_get_env(&gdjenv);

	ovrRequest req = ovr_PlatformInitializeAndroidAsynchronous(p_app_id.utf8().get_data(), jactivity, gdjenv);

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
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
	ovrRequest req = ovr_Entitlement_GetIsViewerEntitled();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests information about the current user.
/// @return Promise that will be fulfilled with the user's id, oculus_id, display_name, image_url, small_image_url and various Presence related information.
Ref<GDOculusPlatformPromise> GDOculusPlatform::user_get_logged_in_user() {
	ovrRequest req = ovr_User_GetLoggedInUser();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests information about an user from its ID.
/// @return Promise that will be fulfilled with the user's id, oculus_id, display_name, image_url, small_image_url and various Presence related information.
Ref<GDOculusPlatformPromise> GDOculusPlatform::user_get_user(String p_user_id) {
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
	ovrRequest req = ovr_User_GetUserProof();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests the user access token suitable to make REST calls against graph.oculus.com.
/// @return Promise that will be contain a String token if fulfilled
Ref<GDOculusPlatformPromise> GDOculusPlatform::user_get_user_access_token() {
	ovrRequest req = ovr_User_GetAccessToken();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests the user IDs of users blocked by the current user.
/// @return Promise that will contain user IDs as an Array of Strings if fulfilled
Ref<GDOculusPlatformPromise> GDOculusPlatform::user_get_blocked_users() {
	ovrRequest req = ovr_User_GetBlockedUsers();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests the user IDs of the current user's friends.
/// @return Promise that will contain an Array of Dictionaries with information about each friend. Same format as the Dictionary returned by get_user()
Ref<GDOculusPlatformPromise> GDOculusPlatform::user_get_logged_in_user_friends() {
	ovrRequest req = ovr_User_GetLoggedInUserFriends();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests the scoped org ID of a given user
/// @return Promise that will contain the org scoped ID of the given user as a String if fulfilled
Ref<GDOculusPlatformPromise> GDOculusPlatform::user_get_org_scoped_id(String p_user_id) {
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
	ovrRequest req = ovr_User_GetSdkAccounts();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests a block flow to block an user by its ID.
/// @return Promise that will contain a Dictionary with information if the user blocked or cancelled the request.
Ref<GDOculusPlatformPromise> GDOculusPlatform::user_launch_block_flow(String p_user_id) {
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
Ref<GDOculusPlatformPromise> GDOculusPlatform::user_launch_unblock_flow(String p_user_id) {
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
Ref<GDOculusPlatformPromise> GDOculusPlatform::user_launch_friend_request_flow(String p_user_id) {
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
Ref<GDOculusPlatformPromise> GDOculusPlatform::achievements_add_count(String p_achievement_name, uint64_t p_count) {
	ovrRequest req = ovr_Achievements_AddCount(p_achievement_name.utf8().get_data(), p_count);

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests an update for an achievement of type BITFIELD.
/// @return Promise that will contain a Dictionary with info about the result of the update request.
Ref<GDOculusPlatformPromise> GDOculusPlatform::achievements_add_fields(String p_achievement_name, String p_fields) {
	ovrRequest req = ovr_Achievements_AddFields(p_achievement_name.utf8().get_data(), p_fields.utf8().get_data());

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests an update (to unlock) for an achievement of any type.
/// @return Promise that will contain a Dictionary with info about the result of the update request.
Ref<GDOculusPlatformPromise> GDOculusPlatform::achievements_unlock(String p_achievement_name) {
	ovrRequest req = ovr_Achievements_Unlock(p_achievement_name.utf8().get_data());

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests all the achievement definitions.
/// @return Promise that will contain an Array of Dictionaries with info about each achievement.
Ref<GDOculusPlatformPromise> GDOculusPlatform::achievements_get_all_definitions() {
	ovrRequest req = ovr_Achievements_GetAllDefinitions();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests all the achievement progress.
/// @return Promise that will contain an Array of Dictionaries with info about each achievement.
Ref<GDOculusPlatformPromise> GDOculusPlatform::achievements_get_all_progress() {
	ovrRequest req = ovr_Achievements_GetAllProgress();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests achievements definitions by name
/// @return Promise that will contain an Array of Dictionaries with info about each achievement.
Ref<GDOculusPlatformPromise> GDOculusPlatform::achievements_get_definitions_by_name(Array p_achievement_names) {
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
Ref<GDOculusPlatformPromise> GDOculusPlatform::achievements_get_progress_by_name(Array p_achievement_names) {
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
	ovrRequest req = ovr_IAP_GetViewerPurchases();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests a list of products by their SKU
/// @return Promise that contains an Array of Dictionaries with information about each product
Ref<GDOculusPlatformPromise> GDOculusPlatform::iap_get_products_by_sku(Array p_sku_list) {
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
Ref<GDOculusPlatformPromise> GDOculusPlatform::iap_consume_purchase(String p_sku) {
	ovrRequest req = ovr_IAP_ConsumePurchase(p_sku.utf8().get_data());

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Launches the checkout flow
/// @return Promise that contains a Dictionary with information about the product. purchase_str_id will be empty if the user did not complete the purchase
Ref<GDOculusPlatformPromise> GDOculusPlatform::iap_launch_checkout_flow(String p_sku) {
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
	ovrRequest req = ovr_AssetFile_GetList();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests information about a single asset file by ID.
/// @return Promise that contains a Dictionary with information about the assetfile. Language packs have extra information.
Ref<GDOculusPlatformPromise> GDOculusPlatform::assetfile_status_by_id(String p_asset_id) {
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
Ref<GDOculusPlatformPromise> GDOculusPlatform::assetfile_status_by_name(String p_asset_name) {
	ovrRequest req = ovr_AssetFile_StatusByName(p_asset_name.utf8().get_data());

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests to download an asset file by ID.
/// @return Promise that contains the result of the request as a Dictionary.
Ref<GDOculusPlatformPromise> GDOculusPlatform::assetfile_download_by_id(String p_asset_id) {
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
Ref<GDOculusPlatformPromise> GDOculusPlatform::assetfile_download_by_name(String p_asset_name) {
	ovrRequest req = ovr_AssetFile_DownloadByName(p_asset_name.utf8().get_data());

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests to cancel a download of an assetfile by ID.
/// @return Promise that contains the result of the request as a Dictionary. The dictionary includes a "success" key to indicate if the request was successful
Ref<GDOculusPlatformPromise> GDOculusPlatform::assetfile_download_cancel_by_id(String p_asset_id) {
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
Ref<GDOculusPlatformPromise> GDOculusPlatform::assetfile_download_cancel_by_name(String p_asset_name) {
	ovrRequest req = ovr_AssetFile_DownloadCancelByName(p_asset_name.utf8().get_data());

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests to delete an assetfile by ID.
/// @return Promise that contains the result of the request as a Dictionary. The dictionary includes a "success" key to indicate if the request was successful
Ref<GDOculusPlatformPromise> GDOculusPlatform::assetfile_delete_by_id(String p_asset_id) {
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
Ref<GDOculusPlatformPromise> GDOculusPlatform::assetfile_delete_by_name(String p_asset_name) {
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
Ref<GDOculusPlatformPromise> GDOculusPlatform::leaderboard_get(String p_leaderboard_name) {
	ovrRequest req = ovr_Leaderboard_Get(p_leaderboard_name.utf8().get_data());

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests entries of a given leaderboard. Several filters can be applied to narrow down the result.
/// @return Promise that contains an Array of Dictionaries as entries of the leaderboard, if fulfilled.
Ref<GDOculusPlatformPromise> GDOculusPlatform::leaderboard_get_entries(String p_leaderboard_name, uint64_t p_limit, LeaderboardFilterType p_filter, LeaderboardStartAt p_start_at) {
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
Ref<GDOculusPlatformPromise> GDOculusPlatform::leaderboard_get_entries_after_rank(String p_leaderboard_name, uint64_t p_limit, uint64_t p_after_rank) {
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
Ref<GDOculusPlatformPromise> GDOculusPlatform::leaderboard_get_entries_by_ids(String p_leaderboard_name, uint64_t p_limit, Array p_user_ids, LeaderboardStartAt p_start_at) {
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
Ref<GDOculusPlatformPromise> GDOculusPlatform::leaderboard_write_entry(String p_leaderboard_name, uint64_t p_score, bool p_force_update, Dictionary p_extra) {
	if (p_score < 0) {
		p_score = 0;
	}

	if (!p_extra.has("supplementary_metric")) {
		if (!p_extra.has("extra_data")) {
			p_extra["extra_data"] = String("");

		} else if (p_extra.get("extra_data", "").get_type() != Variant::STRING) {
			Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
			String rejection_msg = "Extra data must be a String.";
			return_promise->saved_rejection_response = Array::make(rejection_msg);
			_promises_to_reject.push_back(return_promise);

			return return_promise;
		}

		ovrRequest req = ovr_Leaderboard_WriteEntry(p_leaderboard_name.utf8().get_data(), p_score, ((String)p_extra["extra_data"]).utf8().get_data(), ((String)p_extra["extra_data"]).utf8().length(), p_force_update);

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

		if (!p_extra.has("extra_data")) {
			p_extra["extra_data"] = String("");

		} else if (p_extra.get("extra_data", "").get_type() != Variant::STRING) {
			Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
			String rejection_msg = "Extra data must be a String.";
			return_promise->saved_rejection_response = Array::make(rejection_msg);
			_promises_to_reject.push_back(return_promise);

			return return_promise;
		}

		if ((uint64_t)p_extra.get("supplementary_metric", 0) < 0) {
			p_extra["supplementary_metric"] = 0;
		}

		ovrRequest req = ovr_Leaderboard_WriteEntryWithSupplementaryMetric(p_leaderboard_name.utf8().get_data(), p_score, (int64_t)p_extra["supplementary_metric"], ((String)p_extra["extra_data"]).utf8().get_data(), ((String)p_extra["extra_data"]).utf8().length(), p_force_update);

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
	ovrRequest req = ovr_Application_GetVersion();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;
}

/// Requests the platform to launch another app.
/// @return Promise that will contain a message with information about the request.
Ref<GDOculusPlatformPromise> GDOculusPlatform::application_launch_other_app(String p_app_id, Dictionary p_deeplink_options) {
	ovrApplicationOptionsHandle deeplink_options = ovr_ApplicationOptions_Create();
	ovrID app_id;

	if (ovrID_FromString(&app_id, p_app_id.utf8().get_data())) {
		if (!p_deeplink_options.is_empty()) {
			if (p_deeplink_options.has("deeplink_message")) {
				if (!p_deeplink_options.get("deeplink_message", 0).get_type() != Variant::STRING) {
					Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
					String rejection_msg = "The deeplink_message value must be a String.";
					return_promise->saved_rejection_response = Array::make(rejection_msg);
					_promises_to_reject.push_back(return_promise);

					return return_promise;

				} else {
					ovr_ApplicationOptions_SetDeeplinkMessage(deeplink_options, ((String)p_deeplink_options["deeplink_message"]).utf8().get_data());
				}

				if (p_deeplink_options.has("destination_api_name")) {
					if (!p_deeplink_options.get("destination_api_name", 0).get_type() != Variant::STRING) {
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
					if (!p_deeplink_options.get("lobby_session_id", 0).get_type() != Variant::STRING) {
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
					if (!p_deeplink_options.get("match_session_id", 0).get_type() != Variant::STRING) {
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

				Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
				_promises.push_back(return_promise);

				return return_promise;

			} else {
				Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
				String rejection_msg = "A deeplink_message is required when supplying a non-empty deeplink_options dictionary.";
				return_promise->saved_rejection_response = Array::make(rejection_msg);
				_promises_to_reject.push_back(return_promise);

				return return_promise;
			}

		} else {
			ovr_ApplicationOptions_SetDeeplinkMessage(deeplink_options, "");

			ovrRequest req = ovr_Application_LaunchOtherApp(app_id, deeplink_options);

			Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
			_promises.push_back(return_promise);

			return return_promise;
		}

	} else {
		Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(_get_reject_promise_id()));
		String rejection_msg = "Invalid app id.";
		return_promise->saved_rejection_response = Array::make(rejection_msg);
		_promises_to_reject.push_back(return_promise);

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
	Ref<GDOPUserArray> user_arr = memnew(GDOPUserArray(user_arr_h));

	if (user_arr_h) {
		Array new_user_arr = Array();
		size_t user_arr_s = ovr_UserArray_GetSize(user_arr_h);

		for (size_t i = 0; i < user_arr_s; i++) {
			ovrUserHandle user_h = ovr_UserArray_GetElement(user_arr_h, i);
			Dictionary user_info = _get_user_information(user_h);

			new_user_arr.push_back(user_info);
		}

		user_arr->has_next_page = ovr_UserArray_HasNextPage(user_arr_h);
		user_arr->set_users(new_user_arr);
	} else {
		user_arr->set_users(Array());
	}

	resp["users"] = user_arr;

	return resp;
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// INTERNAL PROCESSING METHODS
/////////////////////////////////////////////////

void GDOculusPlatform::_process_user_get_next_array_page(ovrMessageHandle p_message) {
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {

		ovrUserArrayHandle user_friends_handle = ovr_Message_GetUserArray(p_message);
		Ref<GDOPUserArray> users_array = memnew(GDOPUserArray(user_friends_handle));
		size_t user_friends_array_size = ovr_UserArray_GetSize(user_friends_handle);
		Array users = Array();

		for (size_t i = 0; i < user_friends_array_size; i++) {
			ovrUserHandle user_handle = ovr_UserArray_GetElement(user_friends_handle, i);
			Dictionary user_info = _get_user_information(user_handle);

			users.push_back(user_info);
		}

		users_array->set_users(users);
		users_array->has_next_page = ovr_UserArray_HasNextPage(user_friends_handle);

		_fulfill_promise(msg_id, Array::make(users_array));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

///// USERS
/////////////////////////////////////////////////

/// Processes android asynchronous initialization
void GDOculusPlatform::_process_initialize_android_async(ovrMessageHandle p_message) {
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
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);
	Ref<GDOculusPlatformPromise> promise;

	if (!ovr_Message_IsError(p_message)) {
		ovrBlockedUserArrayHandle blocked_users_handle = ovr_Message_GetBlockedUserArray(p_message);
		size_t blocked_users_array_size = ovr_BlockedUserArray_GetSize(blocked_users_handle);

		if (_get_promise(msg_id, promise)) {
			if (promise->get_ids_count() == 1 && promise->saved_fulfill_response.is_empty()) { // Only the first time
				promise->saved_fulfill_response = Array::make(Array());
			}

			for (size_t i = 0; i < blocked_users_array_size; i++) {
				ovrBlockedUserHandle blocked_user_handle = ovr_BlockedUserArray_GetElement(blocked_users_handle, i);

				char native_id[OVRID_SIZE];
				ovrID blocked_user_id = ovr_BlockedUser_GetId(blocked_user_handle);
				ovrID_ToString(native_id, OVRID_SIZE, blocked_user_id);
				((Array)promise->saved_fulfill_response[0]).push_back(String(native_id));
			}

			if (!ovr_BlockedUserArray_HasNextPage(blocked_users_handle)) {
				_promises.erase(promise);
				promise->fulfill(promise->saved_fulfill_response);

			} else {
				ovrRequest new_req = ovr_User_GetNextBlockedUserArrayPage(blocked_users_handle);
				promise->add_id(new_req);
			}
		}

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

/// Processes user information about the current user's friends. Paginated
void GDOculusPlatform::_process_user_get_logged_in_user_friends(ovrMessageHandle p_message) {
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {

		ovrUserArrayHandle user_friends_handle = ovr_Message_GetUserArray(p_message);
		Ref<GDOPUserArray> users_array = memnew(GDOPUserArray(user_friends_handle));
		size_t user_friends_array_size = ovr_UserArray_GetSize(user_friends_handle);
		Array users = Array();

		for (size_t i = 0; i < user_friends_array_size; i++) {
			ovrUserHandle user_handle = ovr_UserArray_GetElement(user_friends_handle, i);
			Dictionary user_info = _get_user_information(user_handle);

			users.push_back(user_info);
		}

		users_array->set_users(users);
		users_array->has_next_page = ovr_UserArray_HasNextPage(user_friends_handle);

		_fulfill_promise(msg_id, Array::make(users_array));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

/// Processes the org scoped id of a given user
void GDOculusPlatform::_process_user_get_org_scoped_id(ovrMessageHandle p_message) {
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
	Ref<GDOculusPlatformPromise> promise;

	if (!ovr_Message_IsError(p_message)) {
		ovrAchievementDefinitionArrayHandle achiev_defs_handle = ovr_Message_GetAchievementDefinitionArray(p_message);
		size_t achiev_defs_array_size = ovr_AchievementDefinitionArray_GetSize(achiev_defs_handle);

		if (_get_promise(msg_id, promise)) {
			if (promise->get_ids_count() == 1 && promise->saved_fulfill_response.is_empty()) { // Only the first time
				promise->saved_fulfill_response = Array::make(Array());
			}

			for (size_t i = 0; i < achiev_defs_array_size; i++) {
				ovrAchievementDefinitionHandle achiev_def_handle = ovr_AchievementDefinitionArray_GetElement(achiev_defs_handle, i);
				Dictionary achiev_def;

				achiev_def["name"] = ovr_AchievementDefinition_GetName(achiev_def_handle);
				achiev_def["bitfield_length"] = ovr_AchievementDefinition_GetBitfieldLength(achiev_def_handle);
				achiev_def["target"] = (uint64_t)ovr_AchievementDefinition_GetTarget(achiev_def_handle);

				ovrAchievementType achiev_type = ovr_AchievementDefinition_GetType(achiev_def_handle);
				achiev_def["type"] = ovrAchievementType_ToString(achiev_type);

				((Array)promise->saved_fulfill_response[0]).push_back(achiev_def);
			}

			if (!ovr_AchievementDefinitionArray_HasNextPage(achiev_defs_handle)) {
				_promises.erase(promise);
				promise->fulfill(promise->saved_fulfill_response);

			} else {
				ovrRequest new_req = ovr_Achievements_GetNextAchievementDefinitionArrayPage(achiev_defs_handle);
				promise->add_id(new_req);
			}
		}

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

/// Processes the response from a request of achievements_get_all_progress or achievements_get_progress_by_name
void GDOculusPlatform::_process_achievements_progress(ovrMessageHandle p_message) {
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);
	Ref<GDOculusPlatformPromise> promise;

	if (!ovr_Message_IsError(p_message)) {
		ovrAchievementProgressArrayHandle achievs_prog_handle = ovr_Message_GetAchievementProgressArray(p_message);
		size_t achievs_prog_array_size = ovr_AchievementProgressArray_GetSize(achievs_prog_handle);

		if (_get_promise(msg_id, promise)) {
			if (promise->get_ids_count() == 1 && promise->saved_fulfill_response.is_empty()) { // Only the first time
				promise->saved_fulfill_response = Array::make(Array());
			}

			for (size_t i = 0; i < achievs_prog_array_size; i++) {
				ovrAchievementProgressHandle achiev_prog_handle = ovr_AchievementProgressArray_GetElement(achievs_prog_handle, i);
				Dictionary achiev_prog;

				achiev_prog["name"] = ovr_AchievementProgress_GetName(achiev_prog_handle);
				achiev_prog["current_count"] = (uint64_t)ovr_AchievementProgress_GetCount(achiev_prog_handle);
				achiev_prog["current_bitfield"] = ovr_AchievementProgress_GetBitfield(achiev_prog_handle);
				achiev_prog["is_unlocked"] = ovr_AchievementProgress_GetIsUnlocked(achiev_prog_handle);
				achiev_prog["unlock_time"] = (uint64_t)ovr_AchievementProgress_GetUnlockTime(achiev_prog_handle);

				((Array)promise->saved_fulfill_response[0]).push_back(achiev_prog);
			}

			if (!ovr_AchievementProgressArray_HasNextPage(achievs_prog_handle)) {
				_promises.erase(promise);
				promise->fulfill(promise->saved_fulfill_response);

			} else {
				ovrRequest new_req = ovr_Achievements_GetNextAchievementProgressArrayPage(achievs_prog_handle);
				promise->add_id(new_req);
			}
		}

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

///// IAP
/////////////////////////////////////////////////

/// Processes the response from a request to get the viewer purchases. Used for both durable cache only and all purchases
void GDOculusPlatform::_process_iap_viewer_purchases(ovrMessageHandle p_message) {
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);
	Ref<GDOculusPlatformPromise> promise;

	if (!ovr_Message_IsError(p_message)) {
		ovrPurchaseArrayHandle v_purchases_arr_handle = ovr_Message_GetPurchaseArray(p_message);
		size_t v_purchases_arr_s = ovr_PurchaseArray_GetSize(v_purchases_arr_handle);

		if (_get_promise(msg_id, promise)) {
			if (promise->get_ids_count() == 1 && promise->saved_fulfill_response.is_empty()) { // Only the first time
				promise->saved_fulfill_response = Array::make(Array());
			}

			for (size_t i = 0; i < v_purchases_arr_s; i++) {
				ovrPurchaseHandle v_purchase_handle = ovr_PurchaseArray_GetElement(v_purchases_arr_handle, i);
				Dictionary v_purchase;

				v_purchase["sku"] = ovr_Purchase_GetSKU(v_purchase_handle);
				v_purchase["reporting_id"] = ovr_Purchase_GetReportingId(v_purchase_handle);
				v_purchase["purchase_str_id"] = ovr_Purchase_GetPurchaseStrID(v_purchase_handle);
				v_purchase["grant_time"] = (uint64_t)ovr_Purchase_GetGrantTime(v_purchase_handle);
				v_purchase["expiration_time"] = (uint64_t)ovr_Purchase_GetExpirationTime(v_purchase_handle);
				v_purchase["developer_payload"] = ovr_Purchase_GetDeveloperPayload(v_purchase_handle);

				((Array)promise->saved_fulfill_response[0]).push_back(v_purchase);
			}

			if (!ovr_PurchaseArray_HasNextPage(v_purchases_arr_handle)) {
				_promises.erase(promise);
				promise->fulfill(promise->saved_fulfill_response);

			} else {
				ovrRequest new_req = ovr_IAP_GetNextPurchaseArrayPage(v_purchases_arr_handle);
				promise->add_id(new_req);
			}
		}

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

/// Processes the response from a request to get products by SKU
void GDOculusPlatform::_process_iap_products(ovrMessageHandle p_message) {
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);
	Ref<GDOculusPlatformPromise> promise;

	if (!ovr_Message_IsError(p_message)) {
		ovrProductArrayHandle products_arr_handle = ovr_Message_GetProductArray(p_message);
		size_t products_arr_s = ovr_ProductArray_GetSize(products_arr_handle);

		if (_get_promise(msg_id, promise)) {
			if (promise->get_ids_count() == 1 && promise->saved_fulfill_response.is_empty()) { // Only the first time
				promise->saved_fulfill_response = Array::make(Array());
			}

			for (size_t i = 0; i < products_arr_s; i++) {
				ovrProductHandle product_handle = ovr_ProductArray_GetElement(products_arr_handle, i);
				Dictionary product;

				product["sku"] = ovr_Product_GetSKU(product_handle);
				product["name"] = ovr_Product_GetName(product_handle);
				product["formatted_price"] = ovr_Product_GetFormattedPrice(product_handle);
				product["description"] = ovr_Product_GetDescription(product_handle);

				((Array)promise->saved_fulfill_response[0]).push_back(product);
			}

			if (!ovr_ProductArray_HasNextPage(products_arr_handle)) {
				_promises.erase(promise);
				promise->fulfill(promise->saved_fulfill_response);

			} else {
				ovrRequest new_req = ovr_IAP_GetNextProductArrayPage(products_arr_handle);
				promise->add_id(new_req);
			}
		}

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

/// Processes the result of a request to consume a consumable item
void GDOculusPlatform::_process_iap_consume_purchase(ovrMessageHandle p_message) {
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {
		_fulfill_promise(msg_id, Array::make(true));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

/// Processes the result of the block flow. Returns a Dictionary with purchase_str_id empty if the user did not complete the purchase.
void GDOculusPlatform::_process_iap_launch_checkout_flow(ovrMessageHandle p_message) {
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
				Dictionary language_info;

				language_info["english_name"] = ovr_LanguagePackInfo_GetEnglishName(language_handle);
				language_info["native_name"] = ovr_LanguagePackInfo_GetNativeName(language_handle);
				language_info["tag"] = ovr_LanguagePackInfo_GetTag(language_handle); // BCP47 format

				assetfile["language_info"] = language_info;
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
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);
	Ref<GDOculusPlatformPromise> promise;

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
			Dictionary destination;

			destination["display_name"] = ovr_Destination_GetDisplayName(destination_handle);
			destination["api_name"] = ovr_Destination_GetApiName(destination_handle);
			destination["deep_link_message"] = ovr_Destination_GetDeeplinkMessage(destination_handle);

			leaderboard["destination"] = destination;
		}else{
			leaderboard["destination"] = Dictionary();
		}

		_fulfill_promise(msg_id, Array::make(leaderboard));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

/// Processes the response from a request to get entries of a leaderboard. This function automatically paginates through the data
void GDOculusPlatform::_process_leaderboard_get_entries(ovrMessageHandle p_message) {
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);

	if (!ovr_Message_IsError(p_message)) {

		ovrLeaderboardEntryArrayHandle entries_arr_handle = ovr_Message_GetLeaderboardEntryArray(p_message);
		Array entries = _handle_leaderboard_entries(entries_arr_handle);

		Ref<GDOPLeaderboardEntries> l_entries = memnew(GDOPLeaderboardEntries(entries_arr_handle));
		l_entries->set_entries(entries);
		l_entries->has_prev_page = ovr_LeaderboardEntryArray_HasPreviousPage(entries_arr_handle);
		l_entries->has_next_page = ovr_LeaderboardEntryArray_HasNextPage(entries_arr_handle);
		l_entries->total_count = ovr_LeaderboardEntryArray_GetTotalCount(entries_arr_handle);

		_fulfill_promise(msg_id, Array::make(l_entries));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
}

/// Processes the response from a request to write an entry to a leaderboard
void GDOculusPlatform::_process_leaderboard_write_entry(ovrMessageHandle p_message) {
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

		_fulfill_promise(msg_id, Array::make(version_info));

	} else {
		_handle_default_process_error(p_message, msg_id);
	}
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
Dictionary GDOculusPlatform::_get_user_information(ovrUserHandle p_user_handle) {
	Dictionary user_info_resp;
	Dictionary user_info_presence;

	user_info_resp["display_name"] = ovr_User_GetDisplayName(p_user_handle);

	char native_id[OVRID_SIZE];
	ovrID u_id = ovr_User_GetID(p_user_handle);
	ovrID_ToString(native_id, OVRID_SIZE, u_id);
	user_info_resp["id"] = String(native_id);

	user_info_resp["oculus_id"] = ovr_User_GetOculusID(p_user_handle);
	user_info_resp["image_url"] = ovr_User_GetImageUrl(p_user_handle);
	user_info_resp["small_image_url"] = ovr_User_GetSmallImageUrl(p_user_handle);

	user_info_resp["presence"] = user_info_presence;
	user_info_presence["presence_status"] = ovrUserPresenceStatus_ToString(ovr_User_GetPresenceStatus(p_user_handle));
	user_info_presence["presence_deeplink_message"] = ovr_User_GetPresenceDeeplinkMessage(p_user_handle);
	user_info_presence["presence_destination_api_name"] = ovr_User_GetPresenceDestinationApiName(p_user_handle);
	user_info_presence["presence_lobby_session_id"] = ovr_User_GetPresenceLobbySessionId(p_user_handle);
	user_info_presence["presence_match_session_id"] = ovr_User_GetPresenceMatchSessionId(p_user_handle);

	return user_info_resp;
}

void GDOculusPlatform::_handle_download_update(ovrMessageHandle p_message) {
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
Array GDOculusPlatform::_handle_leaderboard_entries(ovrLeaderboardEntryArrayHandle p_entries_arr_handle) {
	Array entries = Array();
	size_t entries_arr_s = ovr_LeaderboardEntryArray_GetSize(p_entries_arr_handle);

	for (size_t i = 0; i < entries_arr_s; i++) {
		Dictionary entry_data;

		ovrLeaderboardEntryHandle entry_handle = ovr_LeaderboardEntryArray_GetElement(p_entries_arr_handle, i);

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
		}

		entry_data["user"] = user_info;

		entries.push_back(entry_data);
	}

	return entries;
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// OTHER METHODS
/////////////////////////////////////////////////

/// Gets the Java environment. Currently only used for platform initialization
bool GDOculusPlatform::_get_env(JNIEnv **p_env) {
	ERR_FAIL_NULL_V_MSG(jvm, false, "JVM is null");
	jint res = jvm->GetEnv((void **)p_env, JNI_VERSION_1_6);
	if (res == JNI_EDETACHED) {
		res = jvm->AttachCurrentThread(p_env, NULL);
		if (res == JNI_OK)
			return true;
		else {
			*p_env = NULL;
			ERR_FAIL_COND_V(res != JNI_OK, false);
			return false;
		}
	} else
		return false;
}

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
