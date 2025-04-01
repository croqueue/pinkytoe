#include <cstdint>
#include "pinkytoe/enums.h"

namespace pinkytoe::impl
{

/// @brief 
class BalanceFields final {
  // std::int8_t r0 : 4;
  // std::int8_t r1 : 4;
  // std::int8_t r2 : 4;
  // std::int8_t c0 : 4;
  // std::int8_t c1 : 4;
  // std::int8_t c2 : 4;
  // std::int8_t d0 : 4;
  // std::int8_t d1 : 4;

  std::int8_t rows_[3];
  std::int8_t cols_[3];
  std::int8_t d0_;
  std::int8_t d1_;

public:
  BalanceFields() = default;

  

};

/// @brief 
struct BoardPosition final {
  std::uint8_t r : 4;
  std::uint8_t c : 4;

  BoardPosition() = default;

  /// @brief 
  /// @param r 
  /// @param c 
  inline constexpr BoardPosition(Row r, Column c) noexcept;
};

class MoveLedger final {
  BalanceFields balance_;
  BoardPosition history_[9];
  Player start_player_;
  std::uint8_t move_count_;

public:
  enum class Status : std::uint8_t {
    Ok            = 0,
    CellOccupied  = 1,
    GameOver      = 2,
    CantUndo      = 3
  };

  // CONSTRUCTORS

  /// @brief 
  /// @param start_player 
  inline constexpr MoveLedger(Player start_player) noexcept;

  // OPERATIONS

  /// @brief 
  /// @param r 
  /// @param c 
  /// @return 
  inline constexpr Status move_next(Row r, Column c) noexcept;

  /// @brief 
  /// @return 
  inline constexpr Status undo_last() noexcept;

  // PROPERTIES

  /// @brief 
  /// @return 
  inline constexpr std::uint8_t move_count() noexcept;

  /// @brief 
  /// @return 
  inline constexpr Player start_player() noexcept;
};

} // namespace pinkytoe::impl
