#undef NDEBUG

// Define the custom ostream.  A std::ostream (or derivative) named `out` must
// be defined before calling `TRACE()`.
#define TIDE_TRACE_OSTREAM out
#include <tide/trace.hpp>

#include <gtest/gtest.h>

#include <sstream>

// Testing the macro itself is complicated because the result is going to depend
// on the file, function, and line where `TRACE()` appears.  This test simply
// checks that after a call to `TRACE()`, the output position in the stream has
// advanced.
TEST(TRACE_MacroTest, CustomPrefix) {
	std::ostringstream out;
	auto originalp = out.tellp();
	TRACE("Hi!");
	EXPECT_GT(out.tellp(), originalp);
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
