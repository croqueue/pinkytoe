#include <cstdint>

namespace pinkytoe
{

class MoveHistory final {
  // indices 0-8, need 4 bits each
  // 9 cells, 36 bits total
  std::uint8_t data_[5];
  std::uint8_t count_;

public:
  MoveHistory() = default;

  /// @brief 
  /// @param r 
  /// @param c 
  inline constexpr void push(std::uint8_t r, std::uint8_t c) noexcept;

  /// @brief 
  inline constexpr void pop() noexcept;

  /// @brief 
  /// @param r 
  /// @param c 
  inline constexpr void pop(std::uint8_t& r, std::uint8_t& c);

  /// @brief 
  /// @return 
  inline constexpr std::uint8_t move_count() const noexcept;
};

} // namespace pinkytoe
