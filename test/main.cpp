#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../include/easydump.hpp"

#include <iostream> // cout
#include <map>
#include <sstream>
#include <type_traits> // false_type, true_type
#include <utility> // declval, pair
#include <vector>


// SCENARIO( "supported types", "[support]" ) {

  // GIVEN( "fixed base types" ) {
    // static_assert(exists<dump_type<int>>::value == true, "should exist");
    // static_assert(exists<dump_type<double>>::value == true, "should exist");
    // static_assert(exists<dump_type<char>>::value == false, "should not exist");
  // }

  // GIVEN( "fixed base types" ) {
  //   static_assert(exists<decltype(dump<int>)>::value == true, "should exist");
  //   static_assert(exists<decltype(dump<double>)>::value == true, "should exist");
  //   static_assert(exists<decltype(dump<char>)>::value == false, "should not exist");
  // }
  //
  // GIVEN( "compound types" ) {
  //   static_assert(exists<decltype(dump<std::pair<int, int>>)>::value == true, "");
  //   static_assert(exists<decltype(dump<std::pair<int, double>>)>::value == true, "");
  //   static_assert(exists<decltype(dump<std::pair<int, char>>)>::value == false), "";
  //
  //   static_assert(exists<decltype(dump<std::vector<int>>)>::value == true, "");
  //   static_assert(exists<decltype(dump<std::vector<double>>)>::value == true, "");
  //   static_assert(exists<decltype(dump<std::vector<char>>)>::value == false, "");
  //
  //   static_assert(exists<decltype(dump<std::map<int, int>>)>::value == true, "");
  //   static_assert(exists<decltype(dump<std::map<int, double>>)>::value == true, "");
  //   static_assert(exists<decltype(dump<std::map<int, char>>)>::value == false, "");
  //
  //   static_assert(exists<decltype(dump<std::map<int, std::vector<int>>>)>::value == true, "");
  //   static_assert(exists<decltype(dump<std::map<int, std::pair<int, double>>>)>::value == true, "");
  //   static_assert(exists<decltype(dump<std::map<int, std::map<int, char>>>)>::value == false, "");
  // }
// }


SCENARIO( "depth works", "[depth]" ) {
  using easydump::txt::depth;

  GIVEN( " base types" ) {
    static_assert(depth<int>::value == 0 , "");
    static_assert(depth<double>::value == 0 , "");
    // static_assert(depth<char>::value == 0 , ""); // this will fail
  }
  //
  GIVEN( "compound types" ) {
    static_assert(depth<std::pair<int, int>>::value == 1, "");
    static_assert(depth<std::pair<int, double>>::value == 1, "");
    static_assert(depth<std::pair<std::pair<int, int>, double>>::value == 2, "");

    static_assert(depth<std::vector<int>>::value == 1, "");
    static_assert(depth<std::vector<std::vector<double>>>::value == 2, "");
    static_assert(depth<std::vector<std::pair<int, std::vector<double>>>>::value == 3, "");

    static_assert(depth<std::map<int, int>>::value == 2, "");
    static_assert(depth<std::map<int, double>>::value == 2, "");
    static_assert(depth<std::map<std::pair<int, int>, double>>::value == 3, "");

    static_assert(depth<std::map<int, std::vector<int>>>::value == 3, "");
    static_assert(depth<std::map<int, std::pair<int, double>>>::value == 3, "");
    static_assert(depth<std::map<std::pair<int, int>, std::pair<int, double>>>::value == 3, "");
    static_assert(depth<std::map<int, std::map<int, double>>>::value == 4, "");
  }
}


SCENARIO( "base types work", "[base_type]" ) {

}
