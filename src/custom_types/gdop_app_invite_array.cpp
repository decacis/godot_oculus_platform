#include "gdop_app_invite_array.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void GDOPAppInviteArray::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_invites"), &GDOPAppInviteArray::get_invites);
	ClassDB::bind_method(D_METHOD("set_invites", "app_invites_array"), &GDOPAppInviteArray::set_invites);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "invites"), "set_invites", "get_invites");

	ClassDB::bind_method(D_METHOD("get_has_next_page"), &GDOPAppInviteArray::get_has_next_page);
}

GDOPAppInviteArray::GDOPAppInviteArray() {}
GDOPAppInviteArray::GDOPAppInviteArray(ovrApplicationInviteArrayHandle p_array_handle) {
	if (p_array_handle) {
		array_handle = p_array_handle;
	}
}
GDOPAppInviteArray::~GDOPAppInviteArray() {}

String GDOPAppInviteArray::_to_string() const {
	return "[GDOPAppInviteArray::" + uitos(get_instance_id()) + "]";
}

bool GDOPAppInviteArray::get_has_next_page() const {
	return has_next_page;
}

Array GDOPAppInviteArray::get_invites() const {
	return invites;
}

void GDOPAppInviteArray::set_invites(const Array p_invites_array) {
	invites = p_invites_array;
}
