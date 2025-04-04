#include <type_traits>

namespace pinkytoe::impl
{

// TEMPLATE PROTOTYPES

/// @brief 
/// @tparam TEnum 
/// @param e 
/// @return 
template <typename TEnum>
inline constexpr auto enum_as_integral(TEnum e) noexcept;

/// @brief 
/// @tparam TInt 
/// @param expression 
/// @return 
template <typename TInt>
inline constexpr TInt bool_as_integral(bool expression) noexcept;


// TEMPLATE IMPLEMENTATIONS

/// @brief 
/// @tparam TEnum 
/// @param e 
/// @return 
template <typename TEnum>
constexpr auto enum_as_integral(TEnum e) noexcept
{
  using IntegralType = typename std::underlying_type<TEnum>::type;
  return static_cast<IntegralType>(e);
}

/// @brief 
/// @tparam TInt 
/// @param expression 
/// @return 
template <typename TInt>
constexpr TInt bool_as_integral(bool expression) noexcept
{
  constexpr bool is_int_type = std::is_integral<TInt>::value;
  static_assert(is_int_type, "TInt must be an integral type");
  return static_cast<TInt>(expression);
}

} // namespace pinkytoe::impl
