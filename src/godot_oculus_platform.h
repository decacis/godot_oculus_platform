#ifndef GDOCULUSPLATFORM_H
#define GDOCULUSPLATFORM_H

#include <include/OVR_Platform.h>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/dictionary.hpp>

#include "gdop_promise.h"

namespace godot {

class GDOculusPlatform : public Object {
	GDCLASS(GDOculusPlatform, Object)

protected:
	static GDOculusPlatform *singleton;
	static void _bind_methods();

#ifdef __ANDROID__
private:
	bool progress_connected = false;

	Vector<Ref<GDOculusPlatformPromise>> _promises;
	Vector<Ref<GDOculusPlatformPromise>> _promises_to_reject;
	Vector<Ref<GDOculusPlatformPromise>> _promises_to_fulfill;

	bool _get_promise(uint64_t p_promise_id, Ref<GDOculusPlatformPromise> &p_promise);

	bool _fulfill_promise(uint64_t p_promise_id, const Array &val);
	bool _reject_promise(uint64_t p_promise_id, const Array &val);

	uint64_t _get_reject_promise_id();
	uint64_t _get_fulfill_promise_id();

	void _reject_promises();
	void _fulfill_promises();

	uint64_t _last_promise_rejected_id = 0;
	uint64_t _last_promise_fulfilled_id = 0;

	bool _get_env(JNIEnv **p_env);

	void _handle_default_process_error(ovrMessageHandle p_message, ovrRequest p_msg_id);

	void _process_initialize_android_async(ovrMessageHandle p_message);

	bool _try_connecting_process();

	// USER
	void _process_user_get_is_viewer_entitled(ovrMessageHandle p_message);
	void _process_user_get_logged_in_user(ovrMessageHandle p_message);
	void _process_user_get_user_proof(ovrMessageHandle p_message);
	void _process_user_get_user_access_token(ovrMessageHandle p_message);
	void _process_user_get_blocked_users(ovrMessageHandle p_message);
	void _process_user_get_org_scoped_id(ovrMessageHandle p_message);
	void _process_user_get_sdk_accounts(ovrMessageHandle p_message);
	void _process_user_launch_block_flow(ovrMessageHandle p_message);
	void _process_user_launch_unblock_flow(ovrMessageHandle p_message);
	void _process_user_launch_friend_request_flow(ovrMessageHandle p_message);

	// ACHIEVEMENTS
	void _process_achievements_update(ovrMessageHandle p_message);
	void _process_achievements_definitions(ovrMessageHandle p_message);
	void _process_achievements_progress(ovrMessageHandle p_message);

	// IAP
	void _process_iap_viewer_purchases(ovrMessageHandle p_message);
	void _process_iap_products(ovrMessageHandle p_message);
	void _process_iap_consume_purchase(ovrMessageHandle p_message);
	void _process_iap_launch_checkout_flow(ovrMessageHandle p_message);

	// ASSET FILE
	void _process_assetfile_get_list(ovrMessageHandle p_message);
	void _process_assetfile_get_status(ovrMessageHandle p_message);
	void _process_assetfile_download(ovrMessageHandle p_message);
	void _process_assetfile_download_cancel(ovrMessageHandle p_message);
	void _process_assetfile_delete(ovrMessageHandle p_message);

	// LEADERBOARD
	void _process_leaderboard_get(ovrMessageHandle p_message);
	void _process_leaderboard_get_entries(ovrMessageHandle p_message);
	void _process_leaderboard_write_entry(ovrMessageHandle p_message);

	// ABUSE REPORT
	void _process_abuse_report_handled(ovrMessageHandle p_message);

	// APPLICATION
	void _process_application_get_version(ovrMessageHandle p_message);
	void _process_application_launch_other_app(ovrMessageHandle p_message);
	void _process_application_start_app_download(ovrMessageHandle p_message);
	void _process_application_check_app_download_progress(ovrMessageHandle p_message);

	// CHALLENGES
	void _process_challenges_get(ovrMessageHandle p_message);
	void _process_challenges_get_list(ovrMessageHandle p_message);
	void _process_challenges_get_entries(ovrMessageHandle p_message);
	void _process_challenges_join_leave_decline(ovrMessageHandle p_message);

	// GROUP PRESENCE
	void _process_groupresence_no_payload(ovrMessageHandle p_message);
	void _process_groupresence_send_invites(ovrMessageHandle p_message);
	void _process_groupresence_launch_invite_panel(ovrMessageHandle p_message);
	void _process_groupresence_launch_rejoin_panel(ovrMessageHandle p_message);

	// MEDIA
	void _process_media_share_to_facebook(ovrMessageHandle p_message);

	// USER AGE GROUP
	void _process_useragecategory_get(ovrMessageHandle p_message);
	void _process_useragecategory_report(ovrMessageHandle p_message);

	// DEVICE APPLICATION INTEGRITY
	void _process_deviceappintegrity_get_integrity_token(ovrMessageHandle p_message);

	// LEADERBOARD HELPERS
	Array _handle_leaderboard_entries(const ovrLeaderboardEntryArrayHandle &p_entries_arr_h);

	// ASSET FILE HELPERS
	void _handle_download_update(ovrMessageHandle p_message);

	// USER HELPERS
	Dictionary _get_user_information(const ovrUserHandle &p_user_h);

	// CHALLENGE HELPERS
	Dictionary _get_challenge_information(const ovrChallengeHandle &p_challenge_h);
	Dictionary _get_challenge_entry_information(const ovrChallengeEntryHandle &p_challenge_entry_h);

	// DESTINATION HELPERS
	Dictionary _get_destionation_info(const ovrDestinationHandle &p_destination_h);

	// GROUP PRESENCE HELPERS
	void _handle_process_app_invite_array(ovrMessageHandle p_message);

	void _handle_unhandled_message(ovrMessageHandle p_message);
	void _process_user_get_next_array_page(ovrMessageHandle p_message);
#endif

public:
	static GDOculusPlatform *get_singleton();
	GDOculusPlatform();
	~GDOculusPlatform();

	enum ReportRequestResponse {
		REPORT_REQUEST_HANDLED = ovrReportRequestResponse_Handled,
		REPORT_REQUEST_UNHANDLED = ovrReportRequestResponse_Unhandled
	};

	enum LeaderboardFilterType {
		LEADERBOARD_FILTER_TYPE_NONE = ovrLeaderboard_FilterNone,
		LEADERBOARD_FILTER_TYPE_FRIENDS = ovrLeaderboard_FilterFriends
	};

	enum LeaderboardStartAt {
		LEADERBOARD_START_AT_TOP = ovrLeaderboard_StartAtTop,
		LEADERBOARD_START_AT_CENTERED_ON_VIEWER = ovrLeaderboard_StartAtCenteredOnViewer,
		LEADERBOARD_START_AT_CENTERED_ON_VIEWER_OR_TOP = ovrLeaderboard_StartAtCenteredOnViewerOrTop,
	};

	enum ChallengeVisibilityViewerFilter {
		CHALLENGE_VISIBILITY_VIEWER_ALL_VISIBLE = ovrChallengeViewerFilter_AllVisible,
		CHALLENGE_VISIBILITY_VIEWER_PARTICIPATING = ovrChallengeViewerFilter_Participating,
		CHALLENGE_VISIBILITY_VIEWER_INVITED = ovrChallengeViewerFilter_Invited,
		CHALLENGE_VISIBILITY_VIEWER_PARTICIPATING_OR_INVITED = ovrChallengeViewerFilter_ParticipatingOrInvited
	};

	enum ChallengeVisibility {
		CHALLENGE_VISIBILITY_INVITE_ONLY = ovrChallengeVisibility_InviteOnly,
		CHALLENGE_VISIBILITY_PUBLIC = ovrChallengeVisibility_Public,
		CHALLENGE_VISIBILITY_PRIVATE = ovrChallengeVisibility_Private
	};

	enum MultiplayerErrorErrorKey {
		MULTIPLAYER_ERR_KEY_DEST_UNAVAILABLE = ovrMultiplayerErrorErrorKey_DestinationUnavailable,
		MULTIPLAYER_ERR_KEY_DLC_REQUIRED = ovrMultiplayerErrorErrorKey_DlcRequired,
		MULTIPLAYER_ERR_KEY_GENERAL = ovrMultiplayerErrorErrorKey_General,
		MULTIPLAYER_ERR_KEY_GROUP_FULL = ovrMultiplayerErrorErrorKey_GroupFull,
		MULTIPLAYER_ERR_KEY_INVITER_NOT_JOINABLE = ovrMultiplayerErrorErrorKey_InviterNotJoinable,
		MULTIPLAYER_ERR_KEY_LVL_NOT_HIGH_ENOUGH = ovrMultiplayerErrorErrorKey_LevelNotHighEnough,
		MULTIPLAYER_ERR_KEY_LVL_NOT_UNLOCKED = ovrMultiplayerErrorErrorKey_LevelNotUnlocked,
		MULTIPLAYER_ERR_KEY_NETWORK_TIMEOUT = ovrMultiplayerErrorErrorKey_NetworkTimeout,
		MULTIPLAYER_ERR_KEY_NO_LONGER_AVAILABLE = ovrMultiplayerErrorErrorKey_NoLongerAvailable,
		MULTIPLAYER_ERR_KEY_UPDATE_REQUIRED = ovrMultiplayerErrorErrorKey_UpdateRequired,
		MULTIPLAYER_ERR_KEY_TUTORIAL_REQUIRED = ovrMultiplayerErrorErrorKey_TutorialRequired
	};

	enum MediaContentType {
		MEDIA_CONTENT_TYPE_PHOTO = ovrMediaContentType_Photo
	};

	enum AccountAgeCategory {
		ACCOUNTAGECATEGORY_UNKNOWN = ovrAccountAgeCategory_Unknown,
		ACCOUNTAGECATEGORY_CHILD = ovrAccountAgeCategory_Ch,
		ACCOUNTAGECATEGORY_TEEN = ovrAccountAgeCategory_Tn,
		ACCOUNTAGECATEGORY_ADULT = ovrAccountAgeCategory_Ad
	};

	enum AppAgeCategory {
		APPAGECATEGORY_CHILD = ovrAppAgeCategory_Ch,
		APPAGECATEGORY_NON_CHILD = ovrAppAgeCategory_Nch
	};

	// INITIALIZATION
	bool is_platform_initialized();
	bool initialize_android(const String &p_app_id, const Dictionary &p_initialization_options);
	Ref<GDOculusPlatformPromise> initialize_android_async(const String &p_app_id);

	// ABUSE REPORT
	Ref<GDOculusPlatformPromise> abuse_report_request_handled(ReportRequestResponse p_report_req_resp);

	// USER
	String user_get_logged_in_user_id();
	String user_get_logged_in_user_locale();
	Ref<GDOculusPlatformPromise> user_get_is_viewer_entitled();
	Ref<GDOculusPlatformPromise> user_get_user(const String &p_user_id);
	Ref<GDOculusPlatformPromise> user_get_logged_in_user();
	Ref<GDOculusPlatformPromise> user_get_user_proof();
	Ref<GDOculusPlatformPromise> user_get_user_access_token();
	Ref<GDOculusPlatformPromise> user_get_blocked_users();
	Ref<GDOculusPlatformPromise> user_get_logged_in_user_friends();
	Ref<GDOculusPlatformPromise> user_get_org_scoped_id(const String &p_user_id);
	Ref<GDOculusPlatformPromise> user_get_sdk_accounts();
	Ref<GDOculusPlatformPromise> user_launch_block_flow(const String &p_user_id);
	Ref<GDOculusPlatformPromise> user_launch_unblock_flow(const String &p_user_id);
	Ref<GDOculusPlatformPromise> user_launch_friend_request_flow(const String &p_user_id);

	// ACHIEVEMENTS
	Ref<GDOculusPlatformPromise> achievements_add_count(const String &p_achievement_name, uint64_t p_count);
	Ref<GDOculusPlatformPromise> achievements_add_fields(const String &p_achievement_name, const String &p_fields);
	Ref<GDOculusPlatformPromise> achievements_unlock(const String &p_achievement_name);
	Ref<GDOculusPlatformPromise> achievements_get_all_definitions();
	Ref<GDOculusPlatformPromise> achievements_get_all_progress();
	Ref<GDOculusPlatformPromise> achievements_get_definitions_by_name(const Array &p_achievement_names);
	Ref<GDOculusPlatformPromise> achievements_get_progress_by_name(const Array &p_achievement_names);

	// IAP
	Ref<GDOculusPlatformPromise> iap_get_viewer_purchases();
	Ref<GDOculusPlatformPromise> iap_get_products_by_sku(const Array &p_sku_list);
	Ref<GDOculusPlatformPromise> iap_consume_purchase(const String &p_sku);
	Ref<GDOculusPlatformPromise> iap_launch_checkout_flow(const String &p_sku);

	// ASSET FILE
	Ref<GDOculusPlatformPromise> assetfile_get_list();
	Ref<GDOculusPlatformPromise> assetfile_status_by_id(const String &p_asset_id);
	Ref<GDOculusPlatformPromise> assetfile_status_by_name(const String &p_asset_name);
	Ref<GDOculusPlatformPromise> assetfile_download_by_id(const String &p_asset_id);
	Ref<GDOculusPlatformPromise> assetfile_download_by_name(const String &p_asset_name);
	Ref<GDOculusPlatformPromise> assetfile_download_cancel_by_id(const String &p_asset_id);
	Ref<GDOculusPlatformPromise> assetfile_download_cancel_by_name(const String &p_asset_name);
	Ref<GDOculusPlatformPromise> assetfile_delete_by_id(const String &p_asset_id);
	Ref<GDOculusPlatformPromise> assetfile_delete_by_name(const String &p_asset_name);

	// LEADERBOARD
	Ref<GDOculusPlatformPromise> leaderboard_get(const String &p_leaderboard_name);
	Ref<GDOculusPlatformPromise> leaderboard_get_entries(const String &p_leaderboard_name, uint64_t p_limit, LeaderboardFilterType p_filter, LeaderboardStartAt p_start_at);
	Ref<GDOculusPlatformPromise> leaderboard_get_entries_after_rank(const String &p_leaderboard_name, uint64_t p_limit, uint64_t p_after_rank);
	Ref<GDOculusPlatformPromise> leaderboard_get_entries_by_ids(const String &p_leaderboard_name, uint64_t p_limit, const Array &p_user_ids, LeaderboardStartAt p_start_at);
	Ref<GDOculusPlatformPromise> leaderboard_write_entry(const String &p_leaderboard_name, uint64_t p_score, bool p_force_update, const Dictionary &p_extra);

	// APPLICATION
	Ref<GDOculusPlatformPromise> application_get_version();
	Ref<GDOculusPlatformPromise> application_launch_other_app(const String &p_app_id, const Dictionary &p_deeplink_options);
	Ref<GDOculusPlatformPromise> application_start_app_download();
	Ref<GDOculusPlatformPromise> application_check_app_download_progress();
	Ref<GDOculusPlatformPromise> application_cancel_app_download();
	Ref<GDOculusPlatformPromise> application_install_app_update_and_relaunch(const Dictionary &p_deeplink_options);
	Dictionary application_get_launch_details();

	// CHALLENGES
	Ref<GDOculusPlatformPromise> challenges_get(const String &p_challenge_id);
	Ref<GDOculusPlatformPromise> challenges_get_list(uint64_t p_limit = 10, const Dictionary &p_challenge_options = Dictionary());
	Ref<GDOculusPlatformPromise> challenges_get_entries(const String &p_challenge_id, uint64_t p_limit, LeaderboardFilterType p_filter, LeaderboardStartAt p_start_at);
	Ref<GDOculusPlatformPromise> challenges_get_entries_after_rank(const String &p_challenge_id, uint64_t p_limit, uint64_t p_after_rank);
	Ref<GDOculusPlatformPromise> challenges_get_entries_by_ids(const String &p_challenge_id, uint64_t p_limit, const Array &p_user_ids, LeaderboardStartAt p_start_at);
	Ref<GDOculusPlatformPromise> challenges_join(const String &p_challenge_id);
	Ref<GDOculusPlatformPromise> challenges_leave(const String &p_challenge_id);
	Ref<GDOculusPlatformPromise> challenges_decline_invite(const String &p_challenge_id);

	// GROUP PRESENCE
	Ref<GDOculusPlatformPromise> grouppresence_clear();
	Ref<GDOculusPlatformPromise> grouppresence_send_invites(const Array &p_user_ids);
	Ref<GDOculusPlatformPromise> grouppresence_set(const Dictionary &p_group_presence_options);
	Ref<GDOculusPlatformPromise> grouppresence_set_deeplink_message_override(const String &p_deeplink_message);
	Ref<GDOculusPlatformPromise> grouppresence_set_destination(const String &p_api_name);
	Ref<GDOculusPlatformPromise> grouppresence_set_is_joinable(bool p_is_joinable);
	Ref<GDOculusPlatformPromise> grouppresence_set_lobby_session(const String &p_id);
	Ref<GDOculusPlatformPromise> grouppresence_set_match_session(const String &p_id);
	Ref<GDOculusPlatformPromise> grouppresence_get_invitable_users(const Dictionary &p_options = Dictionary());
	Ref<GDOculusPlatformPromise> grouppresence_get_sent_invites();
	Ref<GDOculusPlatformPromise> grouppresence_launch_invite_panel(const Dictionary &p_options = Dictionary());
	Ref<GDOculusPlatformPromise> grouppresence_launch_multiplayer_error_dialog(MultiplayerErrorErrorKey p_error_key);
	Ref<GDOculusPlatformPromise> grouppresence_launch_rejoin_dialog(const String &p_lobby_session_id, const String &p_match_session_id, const String &p_destination_api_name);
	Ref<GDOculusPlatformPromise> grouppresence_launch_roster_panel(const Dictionary &p_options = Dictionary());

	// MEDIA
	Ref<GDOculusPlatformPromise> media_share_to_facebook(const String &p_post_text_suggestion, const String &p_file_path, MediaContentType p_content_type);

	// USER AGE CATEGORY
	Ref<GDOculusPlatformPromise> useragecategory_get();
	Ref<GDOculusPlatformPromise> useragecategory_report(AppAgeCategory p_app_age_category);

	// DEVICE APPLICATION INTEGRITY
	Ref<GDOculusPlatformPromise> deviceappintegrity_get_integrity_token(const String &p_challenge_nonce);

	void pump_messages();
};

} // namespace godot

VARIANT_ENUM_CAST(GDOculusPlatform::LeaderboardFilterType);
VARIANT_ENUM_CAST(GDOculusPlatform::LeaderboardStartAt);
VARIANT_ENUM_CAST(GDOculusPlatform::ReportRequestResponse);
VARIANT_ENUM_CAST(GDOculusPlatform::ChallengeVisibilityViewerFilter);
VARIANT_ENUM_CAST(GDOculusPlatform::ChallengeVisibility);
VARIANT_ENUM_CAST(GDOculusPlatform::MultiplayerErrorErrorKey);
VARIANT_ENUM_CAST(GDOculusPlatform::MediaContentType);
VARIANT_ENUM_CAST(GDOculusPlatform::AccountAgeCategory);
VARIANT_ENUM_CAST(GDOculusPlatform::AppAgeCategory);

#endif // GDOCULUSPLATFORM_H
