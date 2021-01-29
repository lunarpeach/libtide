#include <tide/sentry.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <utility>

// gmock does not work on free functions or static members.  To work around
// this, I have:
//
// 1) defined the mock class `MockThing`,
// 2) declared a global pointer to a `MockThing`, and
// 3) created a traits class which calls the global's `Destroy()` method.
//
// Each test then begins with creating a new, local `MockThing` and updating the
// global pointer to that method.

// MockThing is a simple mock object with one method.
class MockThing {
public:
	MOCK_METHOD(void, Destroy, (int));
};

namespace {

// Global pointer which will be used by the static method in TestTraits.  THIS
// MUST BE UPDATED AT THE BEGINNING OF EVERY TEST.
MockThing* g_thing;

} // namespace

// TestTraits is a set of traits for a Sentry which will call Destroy on the
// MockThing the global points to.
struct TestTraits {
	using value_type = int;
	static auto Destroy(value_type v) -> void {
		g_thing->Destroy(v);
	}
};

// Make sure Destroy is not called on empty Sentries.
TEST(SentryTest, Empty) {
	// Create a new MockThing and update the global pointer.
	MockThing thing;
	g_thing = &thing;
	EXPECT_CALL(thing, Destroy(::testing::_)).Times(0);
	// Create and destroy a Sentry.
	{ Tide::Sentry<TestTraits> s; }
}

// Make sure Destroy is called on valid Sentries.
TEST(SentryTest, Valid) {
	// Create a new MockThing and update the global pointer.
	MockThing thing;
	g_thing = &thing;
	int value = 42;
	EXPECT_CALL(thing, Destroy(value)).Times(1);
	// Create and destroy a Sentry.
	{ Tide::Sentry<TestTraits> s{value}; }
}

// Make sure Destroy is only called once after a move.
TEST(SentryTest, Move) {
	// Create a new MockThing and update the global pointer.
	MockThing thing;
	g_thing = &thing;
	int value = 42;
	EXPECT_CALL(thing, Destroy(value)).Times(1);
	{
		Tide::Sentry<TestTraits> s{value};
		auto x = std::move(s);
		auto y = std::move(x);
		auto z = std::move(y);
	}
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
