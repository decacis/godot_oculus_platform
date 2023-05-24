#include "gdop_leaderboard_entries.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void GDOPLeaderboardEntries::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_entries"), &GDOPLeaderboardEntries::get_entries);
	ClassDB::bind_method(D_METHOD("set_entries", "entries_array"), &GDOPLeaderboardEntries::set_entries);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "entries"), "set_entries", "get_entries");

	ClassDB::bind_method(D_METHOD("get_has_next_page"), &GDOPLeaderboardEntries::get_has_next_page);

	ClassDB::bind_method(D_METHOD("get_has_prev_page"), &GDOPLeaderboardEntries::get_has_prev_page);

	ClassDB::bind_method(D_METHOD("get_total_count"), &GDOPLeaderboardEntries::get_total_count);

	ClassDB::bind_method(D_METHOD("add_entries", "entries_array"), &GDOPLeaderboardEntries::add_entries);
}

GDOPLeaderboardEntries::GDOPLeaderboardEntries() {}
GDOPLeaderboardEntries::GDOPLeaderboardEntries(ovrLeaderboardEntryArrayHandle p_array_handle) {
	array_handle = p_array_handle;
}
GDOPLeaderboardEntries::~GDOPLeaderboardEntries() {}

uint64_t GDOPLeaderboardEntries::get_total_count() const {
	return total_count;
}

bool GDOPLeaderboardEntries::get_has_next_page() const {
	return has_next_page;
}

bool GDOPLeaderboardEntries::get_has_prev_page() const {
	return has_prev_page;
}

Array GDOPLeaderboardEntries::get_entries() const {
	return entries;
}

void GDOPLeaderboardEntries::set_entries(const Array p_entries_array) {
	entries = p_entries_array;
}

void GDOPLeaderboardEntries::add_entries(Array p_entries_array) {
	entries.append_array(p_entries_array);
}