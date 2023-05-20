#ifndef GOP_PROMISE_H
#define GOP_PROMISE_H

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/ref_counted.hpp>

#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/callable.hpp>

namespace godot {

class GDOculusPlatformPromise : public RefCounted {
	GDCLASS(GDOculusPlatformPromise, RefCounted)

protected:
	static void _bind_methods();

private:
	Vector<uint64_t> promise_ids;

	Callable then_callable;
	Callable error_callable;

public:
	GDOculusPlatformPromise();
	GDOculusPlatformPromise(uint64_t p_id);
	~GDOculusPlatformPromise();

	Array saved_fulfill_response;
	Array saved_rejection_response;

	void add_id(uint64_t p_id);
	int get_ids_count() const;
	bool has_id(uint64_t p_id) const;

	Ref<GDOculusPlatformPromise> then(const Callable &p_callable);
	Ref<GDOculusPlatformPromise> error(const Callable &p_callable);

	void fulfill(Array p_fulfill = Array::make(nullptr));
	void reject(Array p_reject = Array::make(nullptr));
};

} // namespace godot

#endif // GOP_PROMISE_H
