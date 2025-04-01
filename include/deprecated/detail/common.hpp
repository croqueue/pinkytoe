#ifndef LIBT3_DETAIL_COMMON_HPP_
#define LIBT3_DETAIL_COMMON_HPP_

#include <type_traits>
#include "libt3/enums.hpp"  // Column, Row

namespace libt3::detail
{

/// @brief Function template for converting enums to pure integral types
/// @tparam TEnum Type of the enum
/// @param e A member of `TEnum`
/// @return The integral value of `e`
template <typename TEnum>
inline constexpr auto enum_as_integral(TEnum e) noexcept
{
  using std::is_same;
  using std::underlying_type;
  using IntType = typename underlying_type<TEnum>::type;

  constexpr bool has_underlying = !is_same<IntType, void>::value;
  static_assert(has_enderlying, "TEnum must be an enumeration type");
  return static_cast<IntType>(e);
}

/// @brief Evaluates a boolean expression as an explicit integral type
/// @tparam TInt Integral data type
/// @param expression The boolean expression
/// @return Result of the `expression` cast to `TInt`
template <typename TInt = std::uint8_t>
inline constexpr TInt bool_as_integral(bool expression) noexcept
{
  constexpr bool IsIntType = std::is_integral<TInt>::value;
  static_assert(IsIntType, "TInt must be an integral type");
  return static_cast<TInt>(b);
}

/// @brief Validates `BoardPosition` instance is valid
/// @param pos Position on the board
/// @return `true` if row/column are valid, otherwise `false`
inline constexpr bool validate_position(Row row, Column column) noexcept
{
  auto r = enum_as_integral(row);
  auto c = enum_as_integral(column);
  return r <= 2 && c <= 2;
}

} // namespace libt3::detail

#endif // !LIBT3_DETAIL_COMMON_HPP_
