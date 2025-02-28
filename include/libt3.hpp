#ifndef ISLANDU_LIBT3_HPP_
#define ISLANDU_LIBT3_HPP_

#include <stdexcept>
// #include <algorithm>

namespace libt3 {

/// @brief Enumeration cell-ownership states
enum class CellOwner : int {
    /// @brief Indicates cell is owned by player O
    PlayerO = -1,
    /// @brief Indicates cell is vacant
    None    = 0,
    /// @brief Indicates cell is owned by player X
    PlayerX = 1
};

/// @brief Enumeration of possible move outcomes
enum class MoveResult : int {
    /// @brief Indicates successful move
    Ok = 0,
    /// @brief Indicates invalid move
    Error = -1
};

/// @brief TODO:
class TicTacToeBoard {
    /// @brief 3x3 matrix containing cell-ownership states
    CellOwner grid_[3][3];
    /// @brief Indicates the player that moves next
    CellOwner next_move_;
    /// @brief Tracks the balance of rows between the 2 players
    int row_bals_[3];
    /// @brief Tracks the balance of columns between the 2 players
    int col_bals_[3];
    /// @brief Tracks the balance of the 2 diagonals between the 2 players
    int diag_bals_[2];

    /// @brief Validates row and column values
    /// @param row Row index on the board
    /// @param column Column index on the board
    /// @return `true`: row and column valid, otherwise `false`
    static inline constexpr bool validate_location(int row, int column) noexcept
    {
        auto row_valid = row >= 0 && row <= 2;
        auto column_valid = column >= 0 && column <= 2;
        return row_valid && column_valid;
    }

    /// @brief Toggles between players
    /// @param player Input player
    /// @return The `CellOwner` opposite `player`
    static inline CellOwner flip_player(CellOwner player) noexcept
    {
        auto as_integral = static_cast<int>(player);
        auto flipped = as_integral * -1;
        return static_cast<CellOwner>(flipped);
    }

    /// @brief 
    /// @param player 
    /// @return 
    static inline constexpr int player_to_integral(CellOwner player) noexcept
    {
        return static_cast<int>(player);
    }

public:
    /// @brief Implements a tic-tac-toe board
    /// @param init_player Player to make the first move
    inline constexpr TicTacToeBoard(CellOwner init_player)
        : grid_{}, next_move_(init_player),
          row_bals_{}, col_bals_{}, diag_bals_{}
    {
        if (init_player == CellOwner::None) {
            throw std::invalid_argument("Starting player required");
        }
    }

    /// @brief Places the next X or O on the board TODO: update the balance factors
    /// @param row Row selector
    /// @param column Column selector
    /// @return Result of the attempted move
    inline constexpr MoveResult place_next(int row, int column) noexcept
    {
        if (!validate_location(row, column))
            return MoveResult::Error;
        
        auto occupant = this->grid_[row][column];

        if (occupant != CellOwner::None)
            return MoveResult::Error;

        this->grid_[row][column] = this->next_move_;

        /// TODO: Update balance factors
        auto player_integral = player_to_integral(this->next_move_);
        this->row_bals_[row] += player_integral;
        this->col_bals_[column] += player_integral;
        /// TODO: Finish the diagonal balance

        this->next_move_ = flip_player(this->next_move_);
        return MoveResult::Ok;
    }
};

} // namespace libt3

#endif // !ISLANDU_LIBT3_HPP_
