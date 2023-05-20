#include "gop_promise.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/variant.hpp>

using namespace godot;

void GDOculusPlatformPromise::_bind_methods() {
	ClassDB::bind_method(D_METHOD("then", "callable"), &GDOculusPlatformPromise::then);
	ClassDB::bind_method(D_METHOD("error", "callable"), &GDOculusPlatformPromise::error);
}

GDOculusPlatformPromise::GDOculusPlatformPromise() {}
GDOculusPlatformPromise::GDOculusPlatformPromise(uint64_t p_id) {
	promise_ids.push_back(p_id);
}
GDOculusPlatformPromise::~GDOculusPlatformPromise() {}

void GDOculusPlatformPromise::add_id(uint64_t p_id) {
	if (!promise_ids.has(p_id)) {
		promise_ids.push_back(p_id);
	} else {
		WARN_PRINT("Trying to add ID already assigned to GDOculusPlatformPromise");
	}
}

bool GDOculusPlatformPromise::has_id(const uint64_t p_id) const {
	return promise_ids.has(p_id);
}

int GDOculusPlatformPromise::get_ids_count() const {
	return promise_ids.size();
};

Ref<GDOculusPlatformPromise> GDOculusPlatformPromise::then(const Callable &p_callable) {
	ERR_FAIL_COND_V_MSG(!then_callable.is_null(), this, "GDOculusPlatformPromise already has a Callable connected to then()");
	then_callable = p_callable;
	return this;
}

Ref<GDOculusPlatformPromise> GDOculusPlatformPromise::error(const Callable &p_callable) {
	ERR_FAIL_COND_V_MSG(!error_callable.is_null(), this, "GDOculusPlatformPromise already has a Callable connected to error()");
	error_callable = p_callable;
	return this;
}

void GDOculusPlatformPromise::fulfill(Array p_fulfill) {
	if (!then_callable.is_null()) {
		then_callable.callv(p_fulfill);
	}
}

void GDOculusPlatformPromise::reject(Array p_reject) {
	if (!error_callable.is_null()) {
		error_callable.callv(p_reject);
	}
}
