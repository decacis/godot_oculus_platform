#ifndef GDOCULUSPLATFORM_H
#define GDOCULUSPLATFORM_H

#include <include/OVR_Platform.h>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/dictionary.hpp>

#include "gop_promise.h"

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

	bool _get_promise(uint64_t p_promise_id, Ref<GDOculusPlatformPromise> &p_promise);
	uint64_t _get_reject_promise_id();
	void _reject_promises();

	uint64_t _last_promise_rejected_id = 0;

	bool _get_env(JNIEnv **p_env);

	void _handle_default_process_error(ovrMessageHandle p_message, ovrRequest p_msg_id, Ref<GDOculusPlatformPromise> &p_promise);

	void _process_initialize_android_async(ovrMessageHandle p_message);

	// USER
	void _process_user_get_is_viewer_entitled(ovrMessageHandle p_message);
	void _process_user_get_logged_in_user(ovrMessageHandle p_message);
	void _process_user_get_user_proof(ovrMessageHandle p_message);
	void _process_user_get_user_access_token(ovrMessageHandle p_message);
	void _process_user_get_blocked_users(ovrMessageHandle p_message);
	void _process_user_get_logged_in_user_friends(ovrMessageHandle p_message);
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
	void _process_leaderboard_get_entries(ovrMessageHandle p_message, int p_mode = 1);
	void _process_leaderboard_write_entry(ovrMessageHandle p_message);

	// LEADERBOARD HELPERS
	void _handle_leaderboard_entries(ovrLeaderboardEntryArrayHandle p_entries_arr_handle, int p_promise_arr_ind, Ref<GDOculusPlatformPromise> &p_promise);

	// ASSET FILE HELPERS
	void _handle_download_update(ovrMessageHandle p_message);

	// USER HELPERS
	Dictionary _get_user_information(ovrUserHandle p_user_handle);

	void _handle_unhandled_message(ovrMessageHandle p_message);
#endif

public:
	static GDOculusPlatform *get_singleton();
	GDOculusPlatform();
	~GDOculusPlatform();

	enum LeaderboardFilterType {
		LEADERBOARD_FILTER_TYPE_NONE = ovrLeaderboard_FilterNone,
		LEADERBOARD_FILTER_TYPE_FRIENDS = ovrLeaderboard_FilterFriends,
		LEADERBOARD_FILTER_TYPE_UNKNOWN = ovrLeaderboard_FilterUnknown,
		LEADERBOARD_FILTER_TYPE_USER_IDS = ovrLeaderboard_FilterUserIds
	};

	enum LeaderboardStartAt {
		LEADERBOARD_START_AT_TOP = ovrLeaderboard_StartAtTop,
		LEADERBOARD_START_AT_CENTERED_ON_VIEWER = ovrLeaderboard_StartAtCenteredOnViewer,
		LEADERBOARD_START_AT_CENTERED_ON_VIEWER_OR_TOP = ovrLeaderboard_StartAtCenteredOnViewerOrTop,
		LEADERBOARD_START_AT_UNKNOWN = ovrLeaderboard_StartAtUnknown
	};

	bool initialize_android(String p_app_id);
	Ref<GDOculusPlatformPromise> initialize_android_async(String p_app_id);

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
	Ref<GDOculusPlatformPromise> leaderboard_get_entries(String p_leaderboard_name, uint64_t p_limit, LeaderboardFilterType p_filter = LEADERBOARD_FILTER_TYPE_NONE, LeaderboardStartAt p_start_at = LEADERBOARD_START_AT_CENTERED_ON_VIEWER_OR_TOP);
	Ref<GDOculusPlatformPromise> leaderboard_get_entries_after_rank(String p_leaderboard_name, uint64_t p_limit, uint64_t p_after_rank);
	Ref<GDOculusPlatformPromise> leaderboard_get_entries_by_ids(String p_leaderboard_name, uint64_t p_limit, LeaderboardStartAt p_start_at, Array p_user_ids);
	Ref<GDOculusPlatformPromise> leaderboard_write_entry(String p_leaderboard_name, uint64_t p_score, bool p_force_update, String p_extra_data = String(""));
	Ref<GDOculusPlatformPromise> leaderboard_write_entry_with_supplementary_metric(String p_leaderboard_name, uint64_t p_score, uint64_t p_supplementary_metric, bool p_force_update, String p_extra_data = String(""));

	void pump_messages();
};

} // namespace godot

VARIANT_ENUM_CAST(GDOculusPlatform::LeaderboardFilterType);
VARIANT_ENUM_CAST(GDOculusPlatform::LeaderboardStartAt);

#endif // GDOCULUSPLATFORM_H
