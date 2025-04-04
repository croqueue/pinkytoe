#include <cstdint>
#include "pinkytoe/enums.h"
#include "pinkytoe/move_history.h"

namespace pinkytoe
{

class MoveLedger final {
  Player start_player_;
  std::int8_t r_bals_[3]{};
  std::int8_t c_bals_[3]{};
  std::int8_t d_bals_[2]{};
  MoveHistory history_{};

public:
  // CONSTRUCTORS

  /// @brief 
  /// @param start_player 
  inline constexpr MoveLedger(Player start_player) noexcept;

  // OPERATIONS

  /// @brief 
  /// @param r 
  /// @param c 
  /// @return 
  inline constexpr void put_next(std::uint8_t r, std::uint8_t c) noexcept;

  /// @brief 
  /// @return 
  inline constexpr void pop_last() noexcept;

  // PROPERTIES

  /// @brief 
  /// @return 
  inline constexpr std::uint8_t move_count() noexcept;

  /// @brief 
  /// @return 
  inline constexpr Player start_player() noexcept;
};

} // namespace pinkytoe
