#include "constexpr_string.hpp"

////#define FMT_HEADER_ONLY
//#include <fmt/format.h>
//#include <print> c++x23 only
#include <iostream>


constexpr std::string make_string(std::string_view base, const int repeat) {
   std::string result;
   for (int i = 0; i < repeat; ++i) {
      result += base;
   }
   return result;
}

int main() {

   using namespace jason_turner_utils;
   // create a lambda to return a string. Necessary to create a constexpr string.
   constexpr auto make_data = [](){ return make_string("Hello Jason ", 3); };

   constexpr static auto sv = to_string_view(make_data);

   //fmt::print("{}: '{}'", sv.size(), sv);
   //std::print("{}: '{}'", sv.size(), sv);
   std::cout << sv.size() << ": " << sv << std::endl;

   return 0;
}
