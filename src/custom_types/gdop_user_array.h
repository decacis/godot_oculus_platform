#ifndef GDOP_USER_ARRAY_H
#define GDOP_USER_ARRAY_H

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/ref_counted.hpp>

#include <godot_cpp/variant/array.hpp>

#include <include/OVR_Platform.h>

namespace godot {

class GDOPUserArray : public RefCounted {
	GDCLASS(GDOPUserArray, RefCounted)

protected:
	static void _bind_methods();

private:
	Array users;

public:
	GDOPUserArray();
	GDOPUserArray(ovrUserArrayHandle p_array_handle);
	~GDOPUserArray();

	ovrUserArrayHandle array_handle;
	bool has_next_page = false;

	bool get_has_next_page() const;

	Array get_users() const;
	void set_users(const Array p_users_array);
	void add_users(Array p_users_array);
};

} // namespace godot

#endif // GDOP_USER_ARRAY_H
