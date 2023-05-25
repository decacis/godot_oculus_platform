#ifndef GDOP_CHALLENGE_ENTRIES_H
#define GDOP_CHALLENGE_ENTRIES_H

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/ref_counted.hpp>

#include <godot_cpp/variant/array.hpp>

#include <include/OVR_Platform.h>

namespace godot {

class GDOPChallengeEntries : public RefCounted {
	GDCLASS(GDOPChallengeEntries, RefCounted)

protected:
	static void _bind_methods();

private:
	Array entries;

public:
	GDOPChallengeEntries();
	GDOPChallengeEntries(ovrChallengeEntryArrayHandle p_array_handle);
	~GDOPChallengeEntries();

	ovrChallengeEntryArrayHandle array_handle;

	uint64_t total_count = 0;
	bool has_next_page = false;
	bool has_prev_page = false;

	uint64_t get_total_count() const;

	bool get_has_next_page() const;

	bool get_has_prev_page() const;

	Array get_entries() const;
	void set_entries(const Array p_entries_array);
};

} // namespace godot

#endif // GDOP_CHALLENGE_ENTRIES_H
