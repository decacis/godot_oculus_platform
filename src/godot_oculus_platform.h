#ifndef GDOCULUSPLATFORM_H
#define GDOCULUSPLATFORM_H

#include <include/OVR_Platform.h>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/dictionary.hpp>

#include "custom_types/gdop_challenge_array.h"
#include "custom_types/gdop_challenge_entries.h"
#include "custom_types/gdop_leaderboard_entries.h"
#include "custom_types/gdop_user_array.h"
#include "gdop_promise.h"

namespace godot {

class GDOculusPlatform : public Object {
	GDCLASS(GDOculusPlatform, Object)

protected:
	static GDOculusPlatform *singleton;
	static void _bind_methods();

#ifdef __ANDROID__
private:
	Vector<Ref<GDOculusPlatformPromise>> _promises;
	Vector<Ref<GDOculusPlatformPromise>> _promises_to_reject;
	Vector<Ref<GDOculusPlatformPromise>> _promises_to_fulfill;

	bool _get_promise(uint64_t p_promise_id, Ref<GDOculusPlatformPromise> &p_promise);

	bool _fulfill_promise(uint64_t p_promise_id, Array val);
	bool _reject_promise(uint64_t p_promise_id, Array val);

	uint64_t _get_reject_promise_id();
	uint64_t _get_fulfill_promise_id();

	void _reject_promises();
	void _fulfill_promises();

	uint64_t _last_promise_rejected_id = 0;
	uint64_t _last_promise_fulfilled_id = 0;

	bool _get_env(JNIEnv **p_env);

	void _handle_default_process_error(ovrMessageHandle p_message, ovrRequest p_msg_id);

	void _process_initialize_android_async(ovrMessageHandle p_message);

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

	// CHALLENGES
	void _process_challenges_get(ovrMessageHandle p_message);
	void _process_challenges_get_list(ovrMessageHandle p_message);
	void _process_challenges_get_entries(ovrMessageHandle p_message);
	void _process_challenges_join_leave_decline(ovrMessageHandle p_message);

	// LEADERBOARD HELPERS
	Array _handle_leaderboard_entries(ovrLeaderboardEntryArrayHandle &p_entries_arr_handle);

	// ASSET FILE HELPERS
	void _handle_download_update(ovrMessageHandle p_message);

	// USER HELPERS
	Dictionary _get_user_information(ovrUserHandle &p_user_handle);

	// CHALLENGE HELPERS
	Dictionary _get_challenge_information(ovrChallengeHandle &p_challenge_h);
	Dictionary _get_challenge_entry_information(ovrChallengeEntryHandle &p_challenge_entry_h);

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

	// PAGINATION
	Ref<GDOculusPlatformPromise> user_array_get_next_page(Ref<GDOPUserArray> p_user_array);
	Ref<GDOculusPlatformPromise> leaderboard_entries_get_next_page(Ref<GDOPLeaderboardEntries> p_leaderboard_entries);
	Ref<GDOculusPlatformPromise> leaderboard_entries_get_prev_page(Ref<GDOPLeaderboardEntries> p_leaderboard_entries);
	Ref<GDOculusPlatformPromise> challenge_array_get_next_page(Ref<GDOPChallengeArray> p_challenge_array);
	Ref<GDOculusPlatformPromise> challenge_array_get_prev_page(Ref<GDOPChallengeArray> p_challenge_array);
	Ref<GDOculusPlatformPromise> challenge_entries_get_next_page(Ref<GDOPChallengeEntries> p_challenge_entries);
	Ref<GDOculusPlatformPromise> challenge_entries_get_prev_page(Ref<GDOPChallengeEntries> p_challenge_entries);

	// INITIALIZATION
	bool initialize_android(String p_app_id);
	Ref<GDOculusPlatformPromise> initialize_android_async(String p_app_id);

	// ABUSE REPORT
	Ref<GDOculusPlatformPromise> abuse_report_request_handled(ReportRequestResponse p_report_req_resp);

	// USER
	String user_get_logged_in_user_id();
	String user_get_logged_in_user_locale();
	Ref<GDOculusPlatformPromise> user_get_is_viewer_entitled();
	Ref<GDOculusPlatformPromise> user_get_user(String p_user_id);
	Ref<GDOculusPlatformPromise> user_get_logged_in_user();
	Ref<GDOculusPlatformPromise> user_get_user_proof();
	Ref<GDOculusPlatformPromise> user_get_user_access_token();
	Ref<GDOculusPlatformPromise> user_get_blocked_users();
	Ref<GDOculusPlatformPromise> user_get_logged_in_user_friends();
	Ref<GDOculusPlatformPromise> user_get_org_scoped_id(String p_user_id);
	Ref<GDOculusPlatformPromise> user_get_sdk_accounts();
	Ref<GDOculusPlatformPromise> user_launch_block_flow(String p_user_id);
	Ref<GDOculusPlatformPromise> user_launch_unblock_flow(String p_user_id);
	Ref<GDOculusPlatformPromise> user_launch_friend_request_flow(String p_user_id);

	// ACHIEVEMENTS
	Ref<GDOculusPlatformPromise> achievements_add_count(String p_achievement_name, uint64_t p_count);
	Ref<GDOculusPlatformPromise> achievements_add_fields(String p_achievement_name, String p_fields);
	Ref<GDOculusPlatformPromise> achievements_unlock(String p_achievement_name);
	Ref<GDOculusPlatformPromise> achievements_get_all_definitions();
	Ref<GDOculusPlatformPromise> achievements_get_all_progress();
	Ref<GDOculusPlatformPromise> achievements_get_definitions_by_name(Array p_achievement_names);
	Ref<GDOculusPlatformPromise> achievements_get_progress_by_name(Array p_achievement_names);

	// IAP
	Ref<GDOculusPlatformPromise> iap_get_viewer_purchases();
	Ref<GDOculusPlatformPromise> iap_get_products_by_sku(Array p_sku_list);
	Ref<GDOculusPlatformPromise> iap_consume_purchase(String p_sku);
	Ref<GDOculusPlatformPromise> iap_launch_checkout_flow(String p_sku);

	// ASSET FILE
	Ref<GDOculusPlatformPromise> assetfile_get_list();
	Ref<GDOculusPlatformPromise> assetfile_status_by_id(String p_asset_id);
	Ref<GDOculusPlatformPromise> assetfile_status_by_name(String p_asset_name);
	Ref<GDOculusPlatformPromise> assetfile_download_by_id(String p_asset_id);
	Ref<GDOculusPlatformPromise> assetfile_download_by_name(String p_asset_name);
	Ref<GDOculusPlatformPromise> assetfile_download_cancel_by_id(String p_asset_id);
	Ref<GDOculusPlatformPromise> assetfile_download_cancel_by_name(String p_asset_name);
	Ref<GDOculusPlatformPromise> assetfile_delete_by_id(String p_asset_id);
	Ref<GDOculusPlatformPromise> assetfile_delete_by_name(String p_asset_name);

	// LEADERBOARD
	Ref<GDOculusPlatformPromise> leaderboard_get(String p_leaderboard_name);
	Ref<GDOculusPlatformPromise> leaderboard_get_entries(String p_leaderboard_name, uint64_t p_limit, LeaderboardFilterType p_filter = LeaderboardFilterType::LEADERBOARD_FILTER_TYPE_NONE, LeaderboardStartAt p_start_at = LeaderboardStartAt::LEADERBOARD_START_AT_TOP);
	Ref<GDOculusPlatformPromise> leaderboard_get_entries_after_rank(String p_leaderboard_name, uint64_t p_limit, uint64_t p_after_rank);
	Ref<GDOculusPlatformPromise> leaderboard_get_entries_by_ids(String p_leaderboard_name, uint64_t p_limit, Array p_user_ids, LeaderboardStartAt p_start_at = LeaderboardStartAt::LEADERBOARD_START_AT_TOP);
	Ref<GDOculusPlatformPromise> leaderboard_write_entry(String p_leaderboard_name, uint64_t p_score, bool p_force_update = false, Dictionary p_extra = Dictionary());

	// APPLICATION
	Ref<GDOculusPlatformPromise> application_get_version();
	Ref<GDOculusPlatformPromise> application_launch_other_app(String p_app_id, Dictionary p_deeplink_options = Dictionary());
	Dictionary application_get_launch_details();

	// CHALLENGES
	Ref<GDOculusPlatformPromise> challenges_get(String p_challenge_id);
	Ref<GDOculusPlatformPromise> challenges_get_list(uint64_t p_limit = 10, Dictionary p_challenge_options = Dictionary());
	Ref<GDOculusPlatformPromise> challenges_get_entries(String p_challenge_id, uint64_t p_limit, LeaderboardFilterType p_filter = LeaderboardFilterType::LEADERBOARD_FILTER_TYPE_NONE, LeaderboardStartAt p_start_at = LeaderboardStartAt::LEADERBOARD_START_AT_TOP);
	Ref<GDOculusPlatformPromise> challenges_get_entries_after_rank(String p_challenge_id, uint64_t p_limit, uint64_t p_after_rank);
	Ref<GDOculusPlatformPromise> challenges_get_entries_by_ids(String p_challenge_id, uint64_t p_limit, Array p_user_ids, LeaderboardStartAt p_start_at = LeaderboardStartAt::LEADERBOARD_START_AT_TOP);
	Ref<GDOculusPlatformPromise> challenges_join(String p_challenge_id);
	Ref<GDOculusPlatformPromise> challenges_leave(String p_challenge_id);
	Ref<GDOculusPlatformPromise> challenges_decline_invite(String p_challenge_id);

	void pump_messages();
};

} // namespace godot

VARIANT_ENUM_CAST(GDOculusPlatform::LeaderboardFilterType);
VARIANT_ENUM_CAST(GDOculusPlatform::LeaderboardStartAt);
VARIANT_ENUM_CAST(GDOculusPlatform::ReportRequestResponse);
VARIANT_ENUM_CAST(GDOculusPlatform::ChallengeVisibilityViewerFilter);
VARIANT_ENUM_CAST(GDOculusPlatform::ChallengeVisibility);

#endif // GDOCULUSPLATFORM_H
