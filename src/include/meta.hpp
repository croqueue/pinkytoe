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

}