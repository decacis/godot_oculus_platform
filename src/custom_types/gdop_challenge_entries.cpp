#include "gdop_challenge_entries.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void GDOPChallengeEntries::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_entries"), &GDOPChallengeEntries::get_entries);
	ClassDB::bind_method(D_METHOD("set_entries", "entries_array"), &GDOPChallengeEntries::set_entries);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "entries"), "set_entries", "get_entries");

	ClassDB::bind_method(D_METHOD("get_has_next_page"), &GDOPChallengeEntries::get_has_next_page);

	ClassDB::bind_method(D_METHOD("get_has_prev_page"), &GDOPChallengeEntries::get_has_prev_page);

	ClassDB::bind_method(D_METHOD("get_total_count"), &GDOPChallengeEntries::get_total_count);
}

GDOPChallengeEntries::GDOPChallengeEntries() {}
GDOPChallengeEntries::GDOPChallengeEntries(ovrChallengeEntryArrayHandle p_array_handle) {
	array_handle = p_array_handle;
}
GDOPChallengeEntries::~GDOPChallengeEntries() {}

uint64_t GDOPChallengeEntries::get_total_count() const {
	return total_count;
}

bool GDOPChallengeEntries::get_has_next_page() const {
	return has_next_page;
}

bool GDOPChallengeEntries::get_has_prev_page() const {
	return has_prev_page;
}

Array GDOPChallengeEntries::get_entries() const {
	return entries;
}

void GDOPChallengeEntries::set_entries(const Array p_entries_array) {
	entries = p_entries_array;
}
