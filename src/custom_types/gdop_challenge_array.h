#ifndef GDOP_CHALLENGE_ARRAY_H
#define GDOP_CHALLENGE_ARRAY_H

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/ref_counted.hpp>

#include <godot_cpp/variant/array.hpp>

#include <include/OVR_Platform.h>

namespace godot {

class GDOPChallengeArray : public RefCounted {
	GDCLASS(GDOPChallengeArray, RefCounted)

protected:
	static void _bind_methods();

	String _to_string() const;

private:
	Array challenges;

public:
	GDOPChallengeArray();
	GDOPChallengeArray(ovrChallengeArrayHandle p_array_handle);
	~GDOPChallengeArray();

	ovrChallengeArrayHandle array_handle;

	uint64_t total_count = 0;
	bool has_next_page = false;
	bool has_prev_page = false;

	uint64_t get_total_count() const;

	bool get_has_next_page() const;

	bool get_has_prev_page() const;

	Array get_challenges() const;
	void set_challenges(const Array p_challenges_array);
};

} // namespace godot

#endif // GDOP_CHALLENGE_ARRAY_H
