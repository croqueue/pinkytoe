#ifndef PINKYTOE_IMPL_META_H_
#define PINKYTOE_IMPL_META_H_

#include <type_traits>

namespace pinkytoe::impl
{

/// Function-template prototypes

/// @brief Statically casts an enum to its underlying integral type
/// @tparam TEnum The enumeration data type
/// @param e Enumeration member
/// @return Integral-type equivalent of the enumeration member
template <typename TEnum>
inline constexpr auto enum_as_integral(TEnum e) noexcept;

/// @brief Statically casts from boolean to a specified integer type
/// @tparam TInt Return type (must specify)
/// @param expression Boolean value
/// @return `0` or `1` with `TInt` type
template <typename TInt>
inline constexpr TInt bool_as_integral(bool b) noexcept;


/// Function-template implementations

/// @brief Statically casts an enum to its underlying integral type
/// @tparam TEnum The enumeration data type
/// @param e Enumeration member
/// @return Integral-type equivalent of the enumeration member
template <typename TEnum>
constexpr auto enum_as_integral(TEnum e) noexcept
{
  using IntegralType = typename std::underlying_type<TEnum>::type;
  return static_cast<IntegralType>(e);
}

/// @brief Statically casts from boolean to a specified integer type
/// @tparam TInt Return type (must specify)
/// @param expression Boolean value
/// @return `0` or `1` with `TInt` type
template <typename TInt>
constexpr TInt bool_as_integral(bool expression) noexcept
{
  constexpr bool is_int_type = std::is_integral<TInt>::value;
  static_assert(is_int_type, "TInt must be an integral type");
  return static_cast<TInt>(expression);
}

} // namespace pinkytoe::impl

#endif // !PINKYTOE_IMPL_META_H_
