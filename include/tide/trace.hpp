//
// trace.hpp
//
// This file defines the TRACE(...) macro, which comes in two forms:
//     1) ((void)0)               if NDEBUG is defined
//     2) a print to std::clog    if NDEBUG is not defined
//
// Form (2) prints the following to std::clog: TIDE_TRACE_PREFIX (default
// "[TRACE] ") followed by "__FILE__:__LINE__:__func__: ", followed by whatever
// arguments are passed to TRACE(...), and then a newline.  TIDE_TRACE_PREFIX
// and the arguments to TRACE(...) must be fit to pass to std::clog's
// operator<<.
//
// For example if line 14 of foo.cpp is inside the function bar() and contains
// `TRACE("hello!");`, one would expect to see `[TRACE] foo.cpp:14:bar: hello!`
// printed to the console when running a debug build.

#ifndef TIDE_TRACE_HPP
#define TIDE_TRACE_HPP

#ifndef NDEBUG

#ifndef TIDE_TRACE_PREFIX
#define TIDE_TRACE_PREFIX "[TRACE] "
#endif

#ifndef TIDE_TRACE_OSTREAM
#define TIDE_TRACE_OSTREAM std::clog
#endif

#include <iostream>

namespace Tide {

namespace detail {

// Tracer is a functor class that helps translate the TRACE(...) macro into
// calls to the given std::ostream's operator<< using TEMPLATE MAGIC.
class Tracer {
public:
	// The constructor accepts and stores a reference to the given ostream and
	// immediately calls its operator<< to print the rest of the arguments.
	template <typename File, typename Line, typename Func>
	Tracer(std::ostream& out, File&& file, Line&& line, Func&& func)
	    : m_out(out) {
		m_out << TIDE_TRACE_PREFIX << file << ':' << line << ':' << func;
	}

	// operator() calls the stored ostream's operator<< with the given
	// arguments, appropriately separated.
	template <typename... Args>
	auto operator()(Args&&... args) -> Tracer& {
		m_out << ": ";
		append(args...);
		return *this;
	}

	// operator() outputs a newline to the stored ostream.
	auto operator()() -> Tracer& {
		m_out << '\n';
		return *this;
	}

private:
	// append is a helper function that outputs a comma-separated list of its
	// arguments to the stored ostream.
	template <typename First, typename... Rest>
	auto append(First&& first, Rest&&... rest) -> void {
		m_out << first << ", ";
		append(rest...);
	}

	// append outputs its single argument to the stored ostream, followed by a
	// newline.
	template <typename Arg>
	auto append(Arg&& arg) -> void {
		m_out << arg << '\n';
	}

	std::ostream& m_out;

}; // class Tracer

} // namespace detail

} // namespace Tide

#endif // NDEBUG

// TODO: Simplify this with C++20's __VA_OPT__.

// TRACE(...) prints its arguments to std::clog, prepended by the string
// "[TRACE] $fileName:$lineNumber:$functionName: ".
#ifndef NDEBUG
#define TRACE(...)                                                             \
	Tide::detail::Tracer(TIDE_TRACE_OSTREAM, __FILE__, __LINE__,               \
	                     __func__)(__VA_ARGS__)
#else
#define TRACE(...) ((void)0)
#endif // NDEBUG

#endif // TIDE_TRACE_HPP
