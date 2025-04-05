#ifndef PINKYTOE_MOVE_LEDGER_H_
#define PINKYTOE_MOVE_LEDGER_H_

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

  /// @brief Configuration of first player required to construct
  /// @param first_player 
  inline constexpr MoveLedger(Player first_player) noexcept;

  /// @brief Records next move
  /// @param r Row index
  /// @param c Column index
  inline constexpr void record_next(std::uint8_t r, std::uint8_t c) noexcept;

  /// @brief Removes last record from ledger
  inline constexpr void remove_last() noexcept;

  /// @brief Removes last record from ledger
  /// @param r Stores removed row index
  /// @param c Stores removed row index
  inline constexpr void remove_last(std::uint8_t& r, std::uint8_t& c);

  /// @brief Returns number of moves currently recorded
  /// @return Number of recorded moves
  inline constexpr std::uint8_t move_count() noexcept;

  /// @brief Returns the player configured to go first
  /// @return The player the moves/moved first
  inline constexpr Player first_player() noexcept;
};

} // namespace pinkytoe

#endif // !PINKYTOE_MOVE_LEDGER_H_
