#undef NDEBUG

// Define a custom prefix.
#define TIDE_TRACE_PREFIX "[PREFIX] "
#include <tide/trace.hpp>

#include <gtest/gtest.h>

#include <sstream>

// TracerTest is a test fixture which ties a Tracer to a std::ostringstream.
class TracerTest : public ::testing::Test {
protected:
	TracerTest()
	    : m_out{}
	    , m_tracer(m_out, "FILE", "LINE", "FUNC") {}

	std::ostringstream m_out;
	Tide::detail::Tracer m_tracer;
};

// Ensure the custom prefix is used.
TEST_F(TracerTest, Constructor) {
	EXPECT_EQ(m_out.str(), "[PREFIX] FILE:LINE:FUNC");
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
