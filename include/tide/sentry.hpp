//
// tide/sentry.hpp
//
// This file defines the Sentry class template, which is meant to simplify the
// creation of RAII wrappers around "dumb" resources.  Instead of creating an
// entire new class for each kind of resource, you specify two traits - the
// value type of the resource, and how to clean it up - and give those traits to
// a Sentry.
//
// This is done with a traits struct, which may look something like this:
//
//     struct Traits {
//         // value_type is the type of the value to store in the Sentry.
//         using value_type = int;
//
//         // Destroy() is called by the Sentry's destructor.
//         static void Destroy(value_type resource) noexcept {
//             freeResource(resource);
//         }
//     };
//
// .  This can then be used in code like this:
//
//     Sentry<Traits> resource{createResource()};
//
// .  When `resource` goes out of scope, `Traits::Destroy()` will be called with
// the return value of `createResource()`.

#ifndef TIDE_SENTRY_HPP
#define TIDE_SENTRY_HPP

#include <algorithm>

namespace Tide {

// A Sentry is a movable, non-copyable RAII wrapper template for an object
// described by `Traits`, which must define two properties:
//
//     struct Traits {
//         // `value_type` is the type of the value to store in the Sentry.
//         using value_type = int;
//
//         // `Destroy()` is called by the Sentry's destructor.
//         static void Destroy(value_type) noexcept;
//     };
//
// Sentry has one public constructor, which stores the given value and a bool
// signifying that this resource should be freed using `Traits::Destroy()` when
// the Sentry is destroyed.
//
// As a convenience, the Sentry class also provides a conversion operator to
// allow its usage in place of a "raw" `Traits::value_type` in code.
template <typename Traits>
class Sentry {
public:
	// Constructor: creates a Sentry which does not hold a value.  Allows us to
	// use the copy and swap idiom.
	Sentry() noexcept
	    : m_value{}
	    , m_is_valid{false} {}

	// Constructor: adopts a value.
	explicit Sentry(typename Traits::value_type value) noexcept
	    : m_value{value}
	    , m_is_valid{true} {}

	// Copy Constructor: disabled because it does not make sense to guard the
	// same value more than once.
	Sentry(Sentry const&) = delete;

	// Copy Assignment: disabled because it does not make sense to guard the
	// same value more than once.
	Sentry& operator=(Sentry const&) = delete;

	// Move Constructor.
	Sentry(Sentry&& other) noexcept
	    : Sentry{} {
		swap(*this, other);
	}

	// Move Assignment.
	Sentry& operator=(Sentry&& other) noexcept {
		swap(*this, other);
		return *this;
	}

	// Destructor: calls Traits::Destroy if this Sentry holds a value.
	virtual ~Sentry() noexcept {
		if (m_is_valid) {
			Traits::Destroy(m_value);
		}
	}

	// swap exchanges the values of two Sentry objects.
	friend auto swap(Sentry& first, Sentry& second) noexcept -> void {
		using std::swap;
		swap(first.m_value, second.m_value);
		swap(first.m_is_valid, second.m_is_valid);
	}

	// Convert a Sentry to its native type.
	operator typename Traits::value_type() noexcept {
		return m_value;
	}

private:
	typename Traits::value_type m_value;
	bool m_is_valid;
};

} // namespace Tide

#endif // TIDE_SENTRY_HPP
