#undef NDEBUG

#include <tide/trace.hpp>

#include <gtest/gtest.h>

#include <sstream>

// PrintableObject represents a custom object which can be printed by a
// std::ostream.
struct PrintableObject {
	int value;
};

std::ostream& operator<<(std::ostream& out, PrintableObject const& po) {
	return out << po.value;
}

// TracerTest is a test fixture which ties a Tracer to a std::ostringstream.
class TracerTest : public ::testing::Test {
protected:
	TracerTest()
	    : m_out{}
	    , m_tracer(m_out, "FILE", "LINE", "FUNC") {}

	std::ostringstream m_out;
	Tide::detail::Tracer m_tracer;
};

TEST_F(TracerTest, Constructor) {
	EXPECT_EQ(m_out.str(), "[TRACE] FILE:LINE:FUNC");
}

TEST_F(TracerTest, OperatorCallEmpty) {
	m_tracer();
	EXPECT_EQ(m_out.str(), "[TRACE] FILE:LINE:FUNC\n");
}

TEST_F(TracerTest, OperatorCallMessage) {
	m_tracer("test message");
	EXPECT_EQ(m_out.str(), "[TRACE] FILE:LINE:FUNC: test message\n");
}

TEST_F(TracerTest, OperatorCallObject) {
	PrintableObject po{42};
	m_tracer(po);
	EXPECT_EQ(m_out.str(), "[TRACE] FILE:LINE:FUNC: 42\n");
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
