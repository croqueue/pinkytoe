#include <gtest/gtest.h>
#include <cstdint>

#include "frame.hpp"

using pinkytoe::impl::Frame;

TEST(FrameTests, constructor_test) {
  /// Arrange: Create a default object
  Frame frame;

  /// All squares should be 0
  for (auto r = 0; r < 3; ++r) {
    for (auto c = 0; c < 3; ++c) {
      /// Act: Get square value
      auto p = frame.get_square(r, c);
      /// Assert: The value should be 0
      ASSERT_EQ(p, static_cast<std::int8_t>(0));
    }
  }
}


TEST(FrameTests, get_set_test) {
  std::int8_t p[3] = { -1, 0, 1 };
  Frame frame;

  /// Set all pixels
  for (auto r = 0; r < 3; ++r) {
    for (auto c = 0; c < 3; ++c) {
      frame.set_square(r, c, p[r]);
    }
  }

  /// Check pixel values
  for (auto r = 0; r < 3; ++r) {
    for (auto c = 0; c < 3; ++c) {
      ASSERT_EQ(frame.get_square(r, c), p[r]);
    }
  }
}
