#ifndef ISLANDU_LIBT3_HPP_
#define ISLANDU_LIBT3_HPP_

#include <algorithm>
#include <stdexcept>

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
    Ok          = 0,
    /// @brief Result of the move is Player X winning the game
    PlayerXWins = 1,
    /// @brief Result of the move is Player O winning the game
    PlayerOWins = 2,
    /// @brief Indicates invalid move
    Error       = -1
};

/// @brief Implementation of the Tic-Tac-Toe board
class TicTacToeBoard {
    /// @brief Tracks the balance of the board between players
    struct BalanceContext final {
        /// @brief Tracks the balance of rows
        int rows[3] {};
        /// @brief Tracks the balance of columns
        int columns[3] {};
        /// @brief Tracks the balance of the two diagonals
        int diagonals[2] {};

        /// @brief Adjusts row/column/diagonal balances toward player
        /// @param player `CellOwner` as integral value
        /// @param row Row index
        /// @param column Column index
        inline constexpr void update_balances(int player, int row,
                                              int column) noexcept
        {
            int diagonal_conditions[2] = {
                static_cast<int>(row == column),
                static_cast<int>(row == 2 - column)
            };

            this->rows[row] += player;
            this->columns[column] += player;
            this->diagonals[0] += diagonal_conditions[0] * player;
            this->diagonals[1] += diagonal_conditions[1] * player;
        }

        /// @brief Checks for winning player with current balance factors
        /// @return The result of the move
        inline constexpr MoveResult check_for_winner() noexcept
        {
            // Check rows
            if (this->rows[0] == 3)
                return MoveResult::PlayerXWins;
            if (this->rows[0] == -3)
                return MoveResult::PlayerOWins;
            if (this->rows[1] == 3)
                return MoveResult::PlayerXWins;
            if (this->rows[1] == -3)
                return MoveResult::PlayerOWins;
            if (this->rows[2] == 3)
                return MoveResult::PlayerXWins;
            if (this->rows[2] == -3)
                return MoveResult::PlayerOWins;

            // Check columns
            if (this->columns[0] == 3)
                return MoveResult::PlayerXWins;
            if (this->columns[0] == -3)
                return MoveResult::PlayerOWins;
            if (this->columns[1] == 3)
                return MoveResult::PlayerXWins;
            if (this->columns[1] == -3)
                return MoveResult::PlayerOWins;
            if (this->columns[2] == 3)
                return MoveResult::PlayerXWins;
            if (this->columns[2] == -3)
                return MoveResult::PlayerOWins;

            // Check diagonals
            if (this->diagonals[0] == 3)
                return MoveResult::PlayerXWins;
            if (this->diagonals[1] == -3)
                return MoveResult::PlayerOWins;

            // Legal move with indeterminate winner
            return MoveResult::Ok;
        }
    };

    /// @brief Tracks the balance of the board between players
    BalanceContext board_balance_ {};
    /// @brief 3x3 matrix containing cell-ownership states
    CellOwner grid_[3][3];
    /// @brief Indicates the player that moves next
    CellOwner next_move_;
    
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

    /// @brief Converts player enumeration to its corresponding integral value
    /// @param player `CellOwner` indicating a player
    /// @return The `CellOwner` as an `int`
    static inline constexpr int player_to_integral(CellOwner player) noexcept
    {
        return static_cast<int>(player);
    }

public:
    /// @brief Implements a tic-tac-toe board
    /// @param init_player Player to make the first move
    inline constexpr TicTacToeBoard(CellOwner init_player)
        : grid_{}, next_move_(init_player)
    {
        if (init_player == CellOwner::None) {
            throw std::invalid_argument("Starting player required");
        }
    }

    /// @brief Places the next X or O on the board
    /// @param row Row index
    /// @param column Column index
    /// @return Result of the attempted move
    inline constexpr MoveResult place_next(int row, int column) noexcept
    {
        if (!validate_location(row, column))
            return MoveResult::Error;
        
        auto occupant = this->grid_[row][column];

        if (occupant != CellOwner::None)
            return MoveResult::Error;

        this->grid_[row][column] = this->next_move_;
        auto player_integral = player_to_integral(this->next_move_);
        this->board_balance_.update_balances(player_integral, row, column);
        this->next_move_ = flip_player(this->next_move_);
        return this->board_balance_.check_for_winner();
    }
};

} // namespace libt3

#endif // !ISLANDU_LIBT3_HPP_
