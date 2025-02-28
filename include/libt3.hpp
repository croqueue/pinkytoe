#ifndef ISLANDU_LIBT3_HPP_
#define ISLANDU_LIBT3_HPP_

namespace libt3 {

/// @brief 
enum class CellOwner : int {
    PlayerO = -1,
    None    = 0,
    PlayerX = 1
};

/// @brief 
enum class MoveResult : int {
    Ok = 0,
    Error = -1
};


/// @brief TODO:
class TicTacToeBoard {
    CellOwner grid_[3][3];
    CellOwner next_move_;

    /// @brief TODO:
    /// @param row 
    /// @param column 
    /// @return 
    static inline constexpr bool validate_location(int row, int column) noexcept
    {
        auto row_valid = row >= 0 && row <= 2;
        auto column_valid = column >= 0 && column <= 2;
        return row_valid && column_valid;
    }

    /// @brief TODO:
    /// @param owner 
    /// @return 
    static inline CellOwner flip_owner(CellOwner owner) noexcept
    {
        auto as_integral = static_cast<int>(owner);
        auto flipped = as_integral * -1;
        return static_cast<CellOwner>(flipped);
    }

public:
    /// @brief TODO:
    /// @param init_player 
    inline constexpr TicTacToeBoard(CellOwner init_player) noexcept : grid_{}, next_move_(init_player)
    {
    }

    /// @brief TODO:
    /// @param row 
    /// @param column 
    /// @return 
    inline constexpr MoveResult place_next(int row, int column) noexcept
    {
        if (!validate_location(row, column))
            return MoveResult::Error;
        
        auto occupant = this->grid_[row][column];

        if (occupant != CellOwner::None)
            return MoveResult::Error;

        this->grid_[row][column] = this->next_move_;
        this->next_move_ = flip_owner(this->next_move_);
        return MoveResult::Ok;
    }
};

} // namespace libt3

#endif // !ISLANDU_LIBT3_HPP_
