#include <gtest/gtest.h>
#include <cstdint>

#include "move_history.hpp"

using pinkytoe::impl::MoveHistory;

TEST(MoveHistoryTests, constructor_test) {
	MoveHistory history;
  /// Make sure count is 0 (only publically testable initialization)
	ASSERT_EQ(history.count(), 0);
}

TEST(MoveHistoryTests, push_test) {
	MoveHistory history;
	std::uint8_t r_tmp{}, c_tmp{};

  /// Fill left -> right, top -> bottom
	for (std::uint8_t r = 0; r < 3; ++r) {
		for (std::uint8_t c = 0; c < 3; ++c) {
			history.push(r, c);
			history.top(r_tmp, c_tmp);
      /// Make sure last push is on the top
			ASSERT_EQ(r, r_tmp);
			ASSERT_EQ(c, c_tmp);
		}
	}
}

TEST(MoveHistoryTests, pop_only_test) {
	MoveHistory history;
	std::uint8_t r_tmp{}, c_tmp{};

	/// Fill left -> right, top -> bottom
	for (std::uint8_t r = 0; r < 3; ++r) {
		for (std::uint8_t c = 0; c < 3; ++c) {
			history.push(r, c);
		}
	}

	/// Pop order should match right -> left, bottom -> top
	for (std::int8_t r = 2; r >= 0; --r) {
		for (std::int8_t c = 2; c >= 0; --c) {
      /// Make sure pop order is the opposite of push order
			history.top(r_tmp, c_tmp);
			ASSERT_EQ(r_tmp, static_cast<std::uint8_t>(r));
			ASSERT_EQ(c_tmp, static_cast<std::uint8_t>(c));
			history.pop();
		}
	}
}

TEST(MoveHistoryTests, pop_and_get_test) {
	MoveHistory history;
	std::uint8_t r_tmp{}, c_tmp{};

	/// Fill left->right, top->bottom
	for (std::uint8_t r = 0; r < 3; ++r) {
		for (std::uint8_t c = 0; c < 3; ++c) {
			history.push(r, c);
		}
	}

	/// Pop order should match right -> left, bottom -> top
	for (std::int8_t r = 2; r >= 0; --r) {
		for (std::int8_t c = 2; c >= 0; --c) {
      /// Make sure pop order is the opposite of push order
			history.pop(r_tmp, c_tmp);
			ASSERT_EQ(r_tmp, static_cast<std::uint8_t>(r));
			ASSERT_EQ(c_tmp, static_cast<std::uint8_t>(c));
		}
	}
}
