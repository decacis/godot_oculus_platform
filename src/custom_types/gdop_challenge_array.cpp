#include "gdop_challenge_array.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void GDOPChallengeArray::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_challenges"), &GDOPChallengeArray::get_challenges);
	ClassDB::bind_method(D_METHOD("set_challenges", "challenges_array"), &GDOPChallengeArray::set_challenges);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "challenges"), "set_challenges", "get_challenges");

	ClassDB::bind_method(D_METHOD("get_has_next_page"), &GDOPChallengeArray::get_has_next_page);

	ClassDB::bind_method(D_METHOD("get_has_prev_page"), &GDOPChallengeArray::get_has_prev_page);

	ClassDB::bind_method(D_METHOD("get_total_count"), &GDOPChallengeArray::get_total_count);
}

GDOPChallengeArray::GDOPChallengeArray() {}
GDOPChallengeArray::GDOPChallengeArray(ovrChallengeArrayHandle p_array_handle) {
	if (p_array_handle) {
		array_handle = p_array_handle;
	}
}
GDOPChallengeArray::~GDOPChallengeArray() {}

uint64_t GDOPChallengeArray::get_total_count() const {
	return total_count;
}

bool GDOPChallengeArray::get_has_next_page() const {
	return has_next_page;
}

bool GDOPChallengeArray::get_has_prev_page() const {
	return has_prev_page;
}

Array GDOPChallengeArray::get_challenges() const {
	return challenges;
}

void GDOPChallengeArray::set_challenges(const Array p_challenges_array) {
	challenges = p_challenges_array;
}
