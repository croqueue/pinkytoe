#include "pinkytoe/enums.h"

namespace pinkytoe
{

namespace impl
{

class Matrix;
class MoveLedger;

} // namespace [pinkytoe]::impl

class TicTacToe final {
  impl::Matrix& matrix_;
  impl::MoveLedger& ledger_;

public:
  TicTacToe()
};

} // namespace pinkytoe
