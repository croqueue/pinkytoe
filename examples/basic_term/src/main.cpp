#include "enums.hpp"
#include "pinkytoe/api.h"
#include <cstdio>

using pinkytoe::Column;
using pinkytoe::MoveResult;
using pinkytoe::Player;
using pinkytoe::Row;
using pinkytoe::TicTacToe;

namespace pinkytoe::examples::basic_term {

struct GameConfig final
{
  char x_repr, o_repr;
  ForegroundColor foreground_color;
  BackgroundColor background_color;

  inline constexpr GameConfig() noexcept
    : x_repr('X')
    , o_repr('O')
    , foreground_color(ForegroundColor::White)
    , background_color(BackgroundColor::BrightBlack)
  {
  }
};

class GameContext final
{
  TicTacToe game_;
  const GameConfig config_;
  Player frame_buf_[3][3];

public:
  /// @brief
  /// @param player1
  inline GameContext(Player player1) noexcept
    : game_(player1)
    , config_{}
    , frame_buf_{}
  {
  }

  /// @brief
  /// @param player1
  /// @param config
  inline GameContext(Player player1, const GameConfig& config) noexcept
    : game_(player1)
    , config_(config)
    , frame_buf_{}
  {
  }

  inline constexpr MoveResult play_next(Row row, Column column) noexcept
  {
    return this->game_.play_next(row, column);
  }

  inline void draw_state() noexcept
  {
    this->game_.read_board(this->frame_buf_);
    auto fg = static_cast<unsigned int>(this->config_.foreground_color);
    auto bg = static_cast<unsigned int>(this->config_.background_color);

    for (auto r = 0; r < 3; ++r) {
      for (auto c = 0; c < 3; ++c) {
        char owner;

        switch (this->frame_buf_[r][c]) {
          case Player::X:
            owner = this->config_.x_repr;
            break;
          case Player::O:
            owner = this->config_.o_repr;
            break;
          default:
            owner = ' ';
            break;
        }

        if ((r + c) & 1) {
          std::fprintf(stdout, "\033[%u;%um%c[0m", fg, bg, owner);
        } else {
          std::fprintf(stdout, "\033[%um%c[0m", fg, owner);
        }
      }

      std::fputc('\n', stdout);
    }
  }
};

} // namespace pinkytoe::examples::basic_term

int
main(void)
{
  using pinkytoe::examples::basic_term::BackgroundColor;
  using pinkytoe::examples::basic_term::ForegroundColor;
  using pinkytoe::examples::basic_term::GameConfig;
  using pinkytoe::examples::basic_term::GameContext;

  GameConfig config;
  GameContext context(Player::X, config);

  context.play_next(Row::Middle, Column::Middle);
  context.draw_state();

  // RAII w/ GameContext upon processing prerequisite CL options and user input

  return 0;
}
