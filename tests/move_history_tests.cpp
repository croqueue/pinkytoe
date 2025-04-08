#include <gtest/gtest.h>
#include <cstdint>

#include "move_history.hpp"

using pinkytoe::impl::MoveHistory;

TEST(MoveHistoryTests, constructor_test) {
	MoveHistory history;

	ASSERT_EQ(history.count(), 0);
}
