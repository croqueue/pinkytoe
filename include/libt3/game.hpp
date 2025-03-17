#ifndef LIBT3_GAME_HPP_
#define LIBT3_GAME_HPP_

#include <cstdint>
#include "libt3/enums.hpp"
#include "libt3/detail/common.hpp"

namespace libt3 {

/// @brief Implementation of the Tic-Tac-Toe game
class TicTacToe final
{
	struct ScoreLedger final
	{
		/// @brief Tracks the balance of rows
		std::int8_t r_bals[3]{};
		/// @brief Tracks the balance of columns
		std::int8_t c_bals[3]{};
		/// @brief Tracks the balance of the two diagonals
		std::int8_t d_bals[2]{};



		/// @brief Adjusts row/column/diagonal balances toward player
		/// @param player `CellOwner` as integral value
		/// @param row Row index
		/// @param column Column index
		inline constexpr void update_balances(std::int8_t p,
																					std::int8_t r,
																					std::int8_t c) noexcept;

		/// @brief Checks if a player has won
		/// @return The result of the move
		inline constexpr Status tabulate_score() noexcept;
	};

	/// @brief Tracks the balance of the board between players
	ScoreLedger board_balance_{};
	/// @brief 3x3 matrix containing cell-ownership states
	Player grid_[3][3]{};
	/// @brief Indicates the player that moves next
	Player next_player_;
	/// @brief 
	bool end_flag_;
	
	/// @brief Toggles between player turns
	inline void toggle_next() noexcept;

public:
	/// @brief 
	TicTacToe() = default;

	/// @brief 
	/// @param player 
	/// @return 
	inline constexpr Status set_starting_player(Player player);

	/// @brief 
	/// @param row 
	/// @param column 
	/// @return 
	inline constexpr Player get_occupant(Row row, Column column) noexcept;

	/// @brief Places the next X or O on the board
	/// @param row Row index
	/// @param column Column index
	/// @return Result of the attempted move
	inline constexpr Status place_next(Row row, Column column) noexcept;

	/// @brief 
	/// @return 
	inline constexpr Player whose_turn() noexcept;

	/// @brief 
	/// @return 
	inline constexpr bool is_over() noexcept;
};

/// @brief Adjusts row/column/diagonal balances toward player
/// @param player `CellOwner` as integral value
/// @param row Row index
/// @param column Column index
constexpr void TicTacToe::ScoreLedger::update_balances(std::int8_t p,
			std::int8_t r,
			std::int8_t c) noexcept
{
	std::int8_t diagonal_conditions[2] = {
		static_cast<std::int8_t>(r == c),
		static_cast<std::int8_t>(r == 2 - c)
	};

	this->r_bals[r] += p;
	this->c_bals[c] += p;
	this->d_bals[0] += diagonal_conditions[0] * p;
	this->d_bals[1] += diagonal_conditions[1] * p;
}

/// @brief Checks if a player has won
/// @return The result of the move
constexpr Status TicTacToe::ScoreLedger::tabulate_score() noexcept
{
	/// TODO: Optimize this function
	// Check rows
	if (this->r_bals[0] == 3)
		return Status::PlayerXWins;
	if (this->r_bals[0] == -3)
		return Status::PlayerOWins;
	if (this->r_bals[1] == 3)
		return Status::PlayerXWins;
	if (this->r_bals[1] == -3)
		return Status::PlayerOWins;
	if (this->r_bals[2] == 3)
		return Status::PlayerXWins;
	if (this->r_bals[2] == -3)
		return Status::PlayerOWins;

	// Check columns
	if (this->c_bals[0] == 3)
		return Status::PlayerXWins;
	if (this->c_bals[0] == -3)
		return Status::PlayerOWins;
	if (this->c_bals[1] == 3)
		return Status::PlayerXWins;
	if (this->c_bals[1] == -3)
		return Status::PlayerOWins;
	if (this->c_bals[2] == 3)
		return Status::PlayerXWins;
	if (this->c_bals[2] == -3)
		return Status::PlayerOWins;

	// Check diagonals
	if (this->d_bals[0] == 3)
		return Status::PlayerXWins;
	if (this->d_bals[1] == -3)
		return Status::PlayerOWins;

	// Legal move
	return Status::Ok;
}

/// @brief Toggles between player turns
inline void TicTacToe::toggle_next() noexcept
{
	using detail::enum_as_integral;

	auto int_val = enum_as_integral(this->next_player_);
	auto flipped = int_val * -1;
	this->next_player_ = static_cast<Player>(flipped);
}

/// @brief 
/// @param player 
/// @return 
inline constexpr Status TicTacToe::set_starting_player(Player player)
{
	switch (player) {
		case Player::X:
		case Player::O:
			this->next_player_ = player;
			return Status::Ok;
		default:
			return Status::PlayerNotSelected;
	}
}

/// @brief get_occupant 
/// @param row 
/// @param column 
/// @return 
inline constexpr Player TicTacToe::get_occupant(Row row, Column column) noexcept
{
	using detail::enum_as_integral;
	using detail::validate_position;

	auto r = enum_as_integral(row);
	auto c = enum_as_integral(column);

	if (!validate_position(r, c))
		return Player::None;

	return this->grid_[r][c];
}

/// @brief Places the next X or O on the board
/// @param row Row index
/// @param column Column index
/// @return Result of the attempted move
inline constexpr Status TicTacToe::place_next(Row row, Column column) noexcept
{
	using detail::enum_as_integral;
	using detail::validate_position;

	// Validate starting player is set
	if (this->next_player_ == Player::None)
		return Status::PlayerNotSelected;
	
	auto r = enum_as_integral(row);
	auto c = enum_as_integral(column);

	if (!validate_position(r, c))
		return Status::RangeError;

	auto occupant = this->grid_[r][c];

	if (occupant != Player::None)
		return Status::CellOccupied;

	// Claim cell on the grid
	this->grid_[r][c] = this->next_player_;

	// Update balances
	auto p = enum_as_integral(this->next_player_);
	this->board_balance_.update_balances(p, r, c);

	// Check for winner
	auto result = this->board_balance_.tabulate_score();

	if (result == Status::PlayerXWins || result == Status::PlayerOWins)
		this->end_flag_ = true;
	else
		this->toggle_next();

	// Indicates successful placement
	return result;
}

/// @brief 
/// @return 
inline constexpr Player TicTacToe::whose_turn() noexcept
{
	return this->next_player_;
}

/// @brief 
/// @return 
inline constexpr bool TicTacToe::is_over() noexcept
{
	return this->end_flag_;
}

} // namespace libt3

#endif // !LIBT3_GAME_HPP_
