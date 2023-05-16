#include "godot_oculus_platform.h"
#include <godot_cpp/core/class_db.hpp>

#ifdef __ANDROID__
static JavaVM *jvm;
static jobject jactivity;
#endif

using namespace godot;

GDOculusPlatform *GDOculusPlatform::singleton = nullptr;

void GDOculusPlatform::_bind_methods() {
	ClassDB::bind_method(D_METHOD("pump_messages"), &GDOculusPlatform::pump_messages);

	ClassDB::bind_method(D_METHOD("initialize_android", "app_id"), &GDOculusPlatform::initialize_android);
	ClassDB::bind_method(D_METHOD("initialize_android_async", "app_id"), &GDOculusPlatform::initialize_android_async);

	// USER
	ClassDB::bind_method(D_METHOD("get_is_viewer_entitled"), &GDOculusPlatform::get_is_viewer_entitled);
	ClassDB::bind_method(D_METHOD("get_logged_in_user"), &GDOculusPlatform::get_logged_in_user);
	ClassDB::bind_method(D_METHOD("get_user", "user_id"), &GDOculusPlatform::get_user);
	ClassDB::bind_method(D_METHOD("get_user_proof"), &GDOculusPlatform::get_user_proof);
	ClassDB::bind_method(D_METHOD("get_user_access_token"), &GDOculusPlatform::get_user_access_token);
	ClassDB::bind_method(D_METHOD("get_blocked_users"), &GDOculusPlatform::get_blocked_users);
	ClassDB::bind_method(D_METHOD("get_logged_in_user_friends"), &GDOculusPlatform::get_logged_in_user_friends);
	ClassDB::bind_method(D_METHOD("get_org_scoped_id", "user_id"), &GDOculusPlatform::get_org_scoped_id);
	ClassDB::bind_method(D_METHOD("get_sdk_accounts"), &GDOculusPlatform::get_sdk_accounts);
	ClassDB::bind_method(D_METHOD("launch_block_flow", "user_id"), &GDOculusPlatform::launch_block_flow);
	ClassDB::bind_method(D_METHOD("launch_unblock_flow", "user_id"), &GDOculusPlatform::launch_unblock_flow);
	ClassDB::bind_method(D_METHOD("launch_friend_request_flow", "user_id"), &GDOculusPlatform::launch_friend_request_flow);

	ADD_SIGNAL(MethodInfo("unhandled_message", PropertyInfo(Variant::DICTIONARY, "message")));
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
	for (int i = 0; i < _promises.size(); i++) {
		Ref<GDOculusPlatformPromise> temp_promise = _promises.get(i);
		if (temp_promise->get_ids().has(p_promise_id)) {
			p_promise = temp_promise;
			_promises.remove_at(i);
			return true;
		}
	}

	ERR_FAIL_V_MSG(false, vformat("Unable to get promise with ID: %s", p_promise_id));
}

/// Rejects all promises in the rejection queue.
void GDOculusPlatform::_reject_promises() {
	for (int i = _promises_to_reject.size() - 1; i > -1; i--) {
		Ref<GDOculusPlatformPromise> temp_promise = _promises_to_reject.get(i);
		_promises_to_reject.remove_at(i);

		temp_promise->reject(temp_promise->saved_rejection_response);
	}
}

/// Returns a unique promise id. Only used for promises that should be rejected straight away.
uint64_t GDOculusPlatform::_get_reject_promise_id() {
	_last_promise_rejected_id += 1;
	return _last_promise_rejected_id;
}

/// Checks the OVR messages queue and handles them according to their type.
void GDOculusPlatform::pump_messages() {
	_reject_promises();

#ifdef __ANDROID__
	ovrMessageHandle message = nullptr;

	// Process messages
	while ((message = ovr_PopMessage()) != nullptr) {
		switch (ovr_Message_GetType(message)) {
			case ovrMessage_PlatformInitializeAndroidAsynchronous:
				_process_initialize_android_async(message);
				break;

			case ovrMessage_Entitlement_GetIsViewerEntitled:
				_process_get_is_viewer_entitled(message);
				break;

			case ovrMessage_User_GetLoggedInUser:
				_process_get_logged_in_user(message);
				break;

			case ovrMessage_User_Get:
				_process_get_logged_in_user(message);
				break;

			case ovrMessage_User_GetUserProof:
				_process_get_user_proof(message);
				break;

			case ovrMessage_User_GetAccessToken:
				_process_get_user_access_token(message);
				break;

			case ovrMessage_User_GetBlockedUsers:
				_process_get_blocked_users(message);
				break;

			case ovrMessage_User_GetNextBlockedUserArrayPage:
				_process_get_blocked_users(message);
				break;

			case ovrMessage_User_GetLoggedInUserFriends:
				_process_get_logged_in_user_friends(message);
				break;

			case ovrMessage_User_GetNextUserArrayPage:
				_process_get_logged_in_user_friends(message);
				break;

			case ovrMessage_User_GetOrgScopedID:
				_process_get_org_scoped_id(message);
				break;

			case ovrMessage_User_GetSdkAccounts:
				_process_get_sdk_accounts(message);
				break;

			case ovrMessage_User_LaunchBlockFlow:
				_process_launch_block_flow(message);
				break;

			case ovrMessage_User_LaunchUnblockFlow:
				_process_launch_unblock_flow(message);
				break;

			case ovrMessage_User_LaunchFriendRequestFlow:
				_process_launch_friend_request_flow(message);
				break;

			default:
				_handle_unhandled_message(message);
		}

		ovr_FreeMessage(message);
	}
#endif
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// PLATFORM INITIALIZATION
/////////////////////////////////////////////////

/// Initialize Android Oculus Platform synchronously.
bool GDOculusPlatform::initialize_android(String p_app_id) {
#ifdef __ANDROID__
	if (!ovr_IsPlatformInitialized()) {
		JNIEnv *gdjenv;
		_get_env(&gdjenv);

		if (ovr_PlatformInitializeAndroid(p_app_id.utf8().get_data(), jactivity, gdjenv) == ovrPlatformInitialize_Success) {
			return true;
		}

	} else {
		return true;
	}
#endif

	return false;
}

/// Initialize Android Oculus Platform asynchronously.
/// @param p_app_id App ID
/// @return Promise to be resolved when the platform finishes initializing
Ref<GDOculusPlatformPromise> GDOculusPlatform::initialize_android_async(String p_app_id) {
#ifdef __ANDROID__
	JNIEnv *gdjenv;
	_get_env(&gdjenv);

	ovrRequest req = ovr_PlatformInitializeAndroidAsynchronous(p_app_id.utf8().get_data(), jactivity, gdjenv);

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;

#else
	Ref<GDOculusPlatformPromise> promise;
	return promise;
#endif
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// USER
/////////////////////////////////////////////////

/// Checks if the user is entitled to the current application.
/// @return Promise that will be fulfilled if the user is entitled to the app. It will be rejected (error) if the user is not entitled
Ref<GDOculusPlatformPromise> GDOculusPlatform::get_is_viewer_entitled() {
#ifdef __ANDROID__
	ovrRequest req = ovr_Entitlement_GetIsViewerEntitled();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;

#else
	Ref<GDOculusPlatformPromise> promise;
	return promise;
#endif
}

/// Requests information about the current user.
/// @return Promise that will be fulfilled with the user's id, oculus_id, display_name, image_url, small_image_url and various Presence related information.
Ref<GDOculusPlatformPromise> GDOculusPlatform::get_logged_in_user() {
#ifdef __ANDROID__
	ovrRequest req = ovr_User_GetLoggedInUser();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;

#else
	Ref<GDOculusPlatformPromise> promise;
	return promise;
#endif
}

/// Requests information about an user from its ID.
/// @return Promise that will be fulfilled with the user's id, oculus_id, display_name, image_url, small_image_url and various Presence related information.
Ref<GDOculusPlatformPromise> GDOculusPlatform::get_user(String p_user_id) {
#ifdef __ANDROID__
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

#else
	Ref<GDOculusPlatformPromise> promise;
	return promise;
#endif
}

/// Requests a nonce used to verify the user.
/// @return Promise that will be fulfilled with the a nonce that can be used to verify the user.
Ref<GDOculusPlatformPromise> GDOculusPlatform::get_user_proof() {
#ifdef __ANDROID__
	ovrRequest req = ovr_User_GetUserProof();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;

#else
	Ref<GDOculusPlatformPromise> promise;
	return promise;
#endif
}

/// Requests the user access token suitable to make REST calls against graph.oculus.com.
/// @return Promise that will be contain a String token if fulfilled
Ref<GDOculusPlatformPromise> GDOculusPlatform::get_user_access_token() {
#ifdef __ANDROID__
	ovrRequest req = ovr_User_GetAccessToken();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;

#else
	Ref<GDOculusPlatformPromise> promise;
	return promise;
#endif
}

/// Requests the user IDs of users blocked by the current user.
/// @return Promise that will contain user IDs as an Array of Strings if fulfilled
Ref<GDOculusPlatformPromise> GDOculusPlatform::get_blocked_users() {
#ifdef __ANDROID__
	ovrRequest req = ovr_User_GetBlockedUsers();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;

#else
	Ref<GDOculusPlatformPromise> promise;
	return promise;
#endif
}

/// Requests the user IDs of the current user's friends.
/// @return Promise that will contain an Array of Dictionaries with information about each friend. Same format as the Dictionary returned by get_user()
Ref<GDOculusPlatformPromise> GDOculusPlatform::get_logged_in_user_friends() {
#ifdef __ANDROID__
	ovrRequest req = ovr_User_GetLoggedInUserFriends();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;

#else
	Ref<GDOculusPlatformPromise> promise;
	return promise;
#endif
}

/// Requests the scoped org ID of a given user
/// @return Promise that will contain the org scoped ID of the given user as a String if fulfilled
Ref<GDOculusPlatformPromise> GDOculusPlatform::get_org_scoped_id(String p_user_id) {
#ifdef __ANDROID__
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

#else
	Ref<GDOculusPlatformPromise> promise;
	return promise;
#endif
}

/// Requests all the accounts belonging to this user.
/// @return Promise that will contain an Array of Dictionaries with the type of account and its ID, if fulfilled.
Ref<GDOculusPlatformPromise> GDOculusPlatform::get_sdk_accounts() {
#ifdef __ANDROID__
	ovrRequest req = ovr_User_GetSdkAccounts();

	Ref<GDOculusPlatformPromise> return_promise = memnew(GDOculusPlatformPromise(req));
	_promises.push_back(return_promise);

	return return_promise;

#else
	Ref<GDOculusPlatformPromise> promise;
	return promise;
#endif
}

/// Requests a block flow to block an user by its ID.
/// @return Promise that will contain a Dictionary with information if the user blocked or cancelled the request.
Ref<GDOculusPlatformPromise> GDOculusPlatform::launch_block_flow(String p_user_id) {
#ifdef __ANDROID__
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

#else
	Ref<GDOculusPlatformPromise> promise;
	return promise;
#endif
}

/// Requests an unblock flow to unblock an user by its ID.
/// @return Promise that will contain a Dictionary with information if the user unblocked or cancelled the request.
Ref<GDOculusPlatformPromise> GDOculusPlatform::launch_unblock_flow(String p_user_id) {
#ifdef __ANDROID__
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

#else
	Ref<GDOculusPlatformPromise> promise;
	return promise;
#endif
}

/// Requests a friend request flow to send a friend request to a user with a given ID.
/// @return Promise that will contain a Dictionary with information if the user sent the friend request or cancelled.
Ref<GDOculusPlatformPromise> GDOculusPlatform::launch_friend_request_flow(String p_user_id) {
#ifdef __ANDROID__
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

#else
	Ref<GDOculusPlatformPromise> promise;
	return promise;
#endif
}

#ifdef __ANDROID__
/////////////////////////////////////////////////
/////////////////////////////////////////////////
///// INTERNAL PROCESSING METHODS
/////////////////////////////////////////////////

/// Processes android asynchronous initialization
void GDOculusPlatform::_process_initialize_android_async(ovrMessageHandle p_message) {
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);
	Ref<GDOculusPlatformPromise> promise;

	if (!ovr_Message_IsError(p_message)) {
		ovrPlatformInitializeHandle platform_init_resp = ovr_Message_GetPlatformInitialize(p_message);
		ovrPlatformInitializeResult platform_init_result = ovr_PlatformInitialize_GetResult(platform_init_resp);

		if (platform_init_result == ovrPlatformInitialize_Success) {
			if (_get_promise(msg_id, promise)) {
				promise->fulfill(Array::make(true));
			}

		} else {
			String gd_message = ovrPlatformInitializeResult_ToString(platform_init_result);

			if (_get_promise(msg_id, promise)) {
				promise->reject(Array::make(gd_message));
			}
		}

	} else {
		_handle_default_process_error(p_message, msg_id, promise);
	}
}

/// Processes entitlement check
void GDOculusPlatform::_process_get_is_viewer_entitled(ovrMessageHandle p_message) {
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);
	Ref<GDOculusPlatformPromise> promise;

	if (!ovr_Message_IsError(p_message)) {
		if (_get_promise(msg_id, promise)) {
			promise->fulfill(Array::make(true));
		}

	} else {
		_handle_default_process_error(p_message, msg_id, promise);
	}
}

/// Processes the user information and transforms it into a dictionary
void GDOculusPlatform::_process_get_logged_in_user(ovrMessageHandle p_message) {
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);
	Ref<GDOculusPlatformPromise> promise;

	if (!ovr_Message_IsError(p_message)) {
		ovrUserHandle user_info_handle = ovr_Message_GetUser(p_message);
		Dictionary user_info_resp = _get_user_information(user_info_handle);

		if (_get_promise(msg_id, promise)) {
			promise->fulfill(Array::make(user_info_resp));
		}

	} else {
		_handle_default_process_error(p_message, msg_id, promise);
	}
}

/// Processes the response from the user's nonce request
void GDOculusPlatform::_process_get_user_proof(ovrMessageHandle p_message) {
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);
	Ref<GDOculusPlatformPromise> promise;

	if (!ovr_Message_IsError(p_message)) {
		ovrUserProofHandle user_proof = ovr_Message_GetUserProof(p_message);
		String user_nonce = ovr_UserProof_GetNonce(user_proof);

		if (_get_promise(msg_id, promise)) {
			promise->fulfill(Array::make(user_nonce));
		}

	} else {
		_handle_default_process_error(p_message, msg_id, promise);
	}
}

/// Processes an access token of the current user.
void GDOculusPlatform::_process_get_user_access_token(ovrMessageHandle p_message) {
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);
	Ref<GDOculusPlatformPromise> promise;

	if (!ovr_Message_IsError(p_message)) {
		String access_token = ovr_Message_GetString(p_message);

		if (_get_promise(msg_id, promise)) {
			promise->fulfill(Array::make(access_token));
		}

	} else {
		_handle_default_process_error(p_message, msg_id, promise);
	}
}

/// Processes blocked user ids from current user. Paginated
void GDOculusPlatform::_process_get_blocked_users(ovrMessageHandle p_message) {
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);
	Ref<GDOculusPlatformPromise> promise;

	if (!ovr_Message_IsError(p_message)) {
		ovrBlockedUserArrayHandle blocked_users_handle = ovr_Message_GetBlockedUserArray(p_message);
		size_t blocked_users_array_size = ovr_BlockedUserArray_GetSize(blocked_users_handle);

		if (_get_promise(msg_id, promise)) {
			if (promise->get_ids().size() == 1 && promise->saved_fulfill_response.is_empty()) { // Only the first time
				promise->saved_fulfill_response = Array::make(Array());
			}

			for (size_t i = 0; i < blocked_users_array_size; i++) {
				ovrBlockedUserHandle blocked_user_handle = ovr_BlockedUserArray_GetElement(blocked_users_handle, i);

				char native_id[21];
				ovrID blocked_user_id = ovr_BlockedUser_GetId(blocked_user_handle);
				ovrID_ToString(native_id, sizeof(native_id), blocked_user_id);
				((Array)promise->saved_fulfill_response[0]).push_back(String(native_id));
			}

			if (!ovr_BlockedUserArray_HasNextPage(blocked_users_handle)) {
				promise->fulfill(promise->saved_fulfill_response);

			} else {
				ovrRequest new_req = ovr_User_GetNextBlockedUserArrayPage(blocked_users_handle);
				promise->add_id(new_req);
				_promises.push_back(promise);
			}
		}

	} else {
		_handle_default_process_error(p_message, msg_id, promise);
	}
}

/// Processes user information about the current user's friends. Paginated
void GDOculusPlatform::_process_get_logged_in_user_friends(ovrMessageHandle p_message) {
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);
	Ref<GDOculusPlatformPromise> promise;

	if (!ovr_Message_IsError(p_message)) {
		ovrUserArrayHandle user_friends_handle = ovr_Message_GetUserArray(p_message);
		size_t user_friends_array_size = ovr_UserArray_GetSize(user_friends_handle);

		if (_get_promise(msg_id, promise)) {
			if (promise->get_ids().size() == 1 && promise->saved_fulfill_response.is_empty()) { // Only the first time
				promise->saved_fulfill_response = Array::make(Array());
			}

			for (size_t i = 0; i < user_friends_array_size; i++) {
				ovrUserHandle user_handle = ovr_UserArray_GetElement(user_friends_handle, i);
				Dictionary user_info = _get_user_information(user_handle);

				((Array)promise->saved_fulfill_response[0]).push_back(user_info);
			}

			if (!ovr_UserArray_HasNextPage(user_friends_handle)) {
				promise->fulfill(promise->saved_fulfill_response);

			} else {
				ovrRequest new_req = ovr_User_GetNextUserArrayPage(user_friends_handle);
				promise->add_id(new_req);
				_promises.push_back(promise);
			}
		}

	} else {
		_handle_default_process_error(p_message, msg_id, promise);
	}
}

/// Processes the org scoped id of a given user
void GDOculusPlatform::_process_get_org_scoped_id(ovrMessageHandle p_message) {
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);
	Ref<GDOculusPlatformPromise> promise;

	if (!ovr_Message_IsError(p_message)) {
		ovrOrgScopedIDHandle org_scoped_id_handle = ovr_Message_GetOrgScopedID(p_message);

		char native_id[21];
		ovrID org_scoped_id = ovr_OrgScopedID_GetID(org_scoped_id_handle);
		ovrID_ToString(native_id, sizeof(native_id), org_scoped_id);

		if (_get_promise(msg_id, promise)) {
			promise->fulfill(Array::make(String(native_id)));
		}

	} else {
		_handle_default_process_error(p_message, msg_id, promise);
	}
}

/// Processes sdk accounts (accounts in the headset) of the current user
void GDOculusPlatform::_process_get_sdk_accounts(ovrMessageHandle p_message) {
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);
	Ref<GDOculusPlatformPromise> promise;

	if (!ovr_Message_IsError(p_message)) {
		ovrSdkAccountArrayHandle accounts_array_handle = ovr_Message_GetSdkAccountArray(p_message);
		size_t accounts_size = ovr_SdkAccountArray_GetSize(accounts_array_handle);
		Array response_arr = Array();

		for (size_t i = 0; i < accounts_size; i++) {
			ovrSdkAccountHandle sdk_account_handle = ovr_SdkAccountArray_GetElement(accounts_array_handle, i);
			ovrSdkAccountType sdk_account_type = ovr_SdkAccount_GetAccountType(sdk_account_handle);
			ovrID sdk_user_id = ovr_SdkAccount_GetUserId(sdk_account_handle);

			String gd_sdk_account_type = ovrSdkAccountType_ToString(sdk_account_type);

			char native_id[21];
			ovrID_ToString(native_id, sizeof(native_id), sdk_user_id);

			Dictionary sdk_account_info;
			sdk_account_info["account_type"] = gd_sdk_account_type;
			sdk_account_info["account_id"] = gd_sdk_account_type;

			response_arr.push_back(sdk_account_info);
		}

		if (_get_promise(msg_id, promise)) {
			promise->fulfill(Array::make(response_arr));
		}

	} else {
		_handle_default_process_error(p_message, msg_id, promise);
	}
}

/// Processes the result of the block flow. Returns a Dictionary.
void GDOculusPlatform::_process_launch_block_flow(ovrMessageHandle p_message) {
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);
	Ref<GDOculusPlatformPromise> promise;

	if (!ovr_Message_IsError(p_message)) {
		ovrLaunchBlockFlowResultHandle block_flow_result_handle = ovr_Message_GetLaunchBlockFlowResult(p_message);

		Dictionary block_flow_result;
		block_flow_result["did_block"] = ovr_LaunchBlockFlowResult_GetDidBlock(block_flow_result_handle);
		block_flow_result["did_cancel"] = ovr_LaunchBlockFlowResult_GetDidCancel(block_flow_result_handle);

		if (_get_promise(msg_id, promise)) {
			promise->fulfill(Array::make(block_flow_result));
		}

	} else {
		_handle_default_process_error(p_message, msg_id, promise);
	}
}

/// Processes the result of the unblock flow. Returns a Dictionary.
void GDOculusPlatform::_process_launch_unblock_flow(ovrMessageHandle p_message) {
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);
	Ref<GDOculusPlatformPromise> promise;

	if (!ovr_Message_IsError(p_message)) {
		ovrLaunchUnblockFlowResultHandle unblock_flow_result_handle = ovr_Message_GetLaunchUnblockFlowResult(p_message);

		Dictionary unblock_flow_result;
		unblock_flow_result["did_unblock"] = ovr_LaunchUnblockFlowResult_GetDidUnblock(unblock_flow_result_handle);
		unblock_flow_result["did_cancel"] = ovr_LaunchUnblockFlowResult_GetDidCancel(unblock_flow_result_handle);

		if (_get_promise(msg_id, promise)) {
			promise->fulfill(Array::make(unblock_flow_result));
		}

	} else {
		_handle_default_process_error(p_message, msg_id, promise);
	}
}

/// Processes the result of the friend request flow. Returns a Dictionary.
void GDOculusPlatform::_process_launch_friend_request_flow(ovrMessageHandle p_message) {
	ovrRequest msg_id = ovr_Message_GetRequestID(p_message);
	Ref<GDOculusPlatformPromise> promise;

	if (!ovr_Message_IsError(p_message)) {
		ovrLaunchFriendRequestFlowResultHandle friend_req_flow_result_handle = ovr_Message_GetLaunchFriendRequestFlowResult(p_message);

		Dictionary friend_req_flow_result;
		friend_req_flow_result["did_send_request"] = ovr_LaunchFriendRequestFlowResult_GetDidSendRequest(friend_req_flow_result_handle);
		friend_req_flow_result["did_cancel"] = ovr_LaunchFriendRequestFlowResult_GetDidCancel(friend_req_flow_result_handle);

		if (_get_promise(msg_id, promise)) {
			promise->fulfill(Array::make(friend_req_flow_result));
		}

	} else {
		_handle_default_process_error(p_message, msg_id, promise);
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
void GDOculusPlatform::_handle_default_process_error(ovrMessageHandle p_message, ovrRequest p_msg_id, Ref<GDOculusPlatformPromise> &p_promise) {
	ovrErrorHandle ovr_err = ovr_Message_GetError(p_message);
	String gd_message = ovr_Error_GetMessage(ovr_err);

	if (_get_promise(p_msg_id, p_promise)) {
		p_promise->reject(Array::make(gd_message));
	}
}

// Helper function to get a Dictionary with information about a single user.
Dictionary GDOculusPlatform::_get_user_information(ovrUserHandle p_user_handle) {
	Dictionary user_info_resp;
	Dictionary user_info_presence;

	user_info_resp["display_name"] = ovr_User_GetDisplayName(p_user_handle);

	char native_id[21];
	ovrID u_id = ovr_User_GetID(p_user_handle);
	ovrID_ToString(native_id, sizeof(native_id), u_id);
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
#endif