#ifndef CONSTEXPR_STRING_HPP
#define CONSTEXPR_STRING_HPP

#include <algorithm>
#include <array>
#include <string>
#include <string_view>

/*
  Jason Turner C++ Weekly - Ep 313 The 'constexpr' Problem That Took Me 5 Years to Fix!
  (c) 28 Feb 2022
*/

namespace jason_turner_utils {

// can this be a constexpr ? (GWP)
#define TEN_MEGA_BYTES  (10 * 1024 * 1024)

// space to hold more than enough of the string.
struct oversized_array {
   std::array<char, TEN_MEGA_BYTES> data{};
   std::size_t size;
};

consteval auto to_oversized_array(const std::string &str) {
   oversized_array result;
   std::copy(str.begin(), str.end(), result.data.begin());
   result.size = str.size();
   return result;
}

// copy the string from the oversized array into a right sized array
consteval auto to_right_sized_array(auto callable) {
    constexpr auto oversized = to_oversized_array(callable());
    std::array<char, oversized.size> result;
    std::copy(oversized.data.begin(),
              std::next(oversized.data.begin(), oversized.size), result.begin());
    return result;
}

template<auto Data>
consteval const auto &make_static() {
   return Data;
}

consteval auto to_string_view(auto callable) -> std::string_view {
   constexpr auto &static_data = make_static<to_right_sized_array(callable)>();
   return std::string_view{static_data.begin(), static_data.size()};
}

} // namespace jason_turner_utils

#endif
