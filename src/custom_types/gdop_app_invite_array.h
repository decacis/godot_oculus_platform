#ifndef GDOP_APP_INVITE_ARRAY_H
#define GDOP_APP_INVITE_ARRAY_H

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/ref_counted.hpp>

#include <godot_cpp/variant/array.hpp>

#include <include/OVR_Platform.h>

namespace godot {

class GDOPAppInviteArray : public RefCounted {
	GDCLASS(GDOPAppInviteArray, RefCounted)

protected:
	static void _bind_methods();

	String _to_string() const;

private:
	Array invites;

public:
	GDOPAppInviteArray();
	GDOPAppInviteArray(ovrApplicationInviteArrayHandle p_array_handle);
	~GDOPAppInviteArray();

	ovrApplicationInviteArrayHandle array_handle;
	bool has_next_page = false;

	bool get_has_next_page() const;

	Array get_invites() const;
	void set_invites(const Array p_invites_array);
};

} // namespace godot

#endif // GDOP_APP_INVITE_ARRAY_H
