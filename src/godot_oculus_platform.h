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

	// USER HELPERS
	Dictionary _get_user_information(ovrUserHandle p_user_handle);

	void _handle_unhandled_message(ovrMessageHandle p_message);
#endif

public:
	static GDOculusPlatform *get_singleton();
	GDOculusPlatform();
	~GDOculusPlatform();

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

	void pump_messages();
};

} // namespace godot

#endif // GDOCULUSPLATFORM_H
