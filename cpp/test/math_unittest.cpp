// Copyright 2005, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// A sample program demonstrating using Google C++ testing framework.
//
// Author: wan@google.com (Zhanyong Wan)


// This sample shows how to write a simple unit test for a function,
// using Google C++ testing framework.
//
// Writing a unit test using Google C++ testing framework is easy as 1-2-3:


// Step 1. Include necessary header files such that the stuff your
// test logic needs is declared.
//
// Don't forget gtest.h, which declares the testing framework.

#include <limits.h>
#include "gtest/gtest.h"
#include "../math.h"
#include <random>


// Step 2. Use the TEST macro to define your tests.
//
// TEST has two parameters: the test case name and the test name.
// After using the macro, you should define your test logic between a
// pair of braces.  You can use a bunch of macros to indicate the
// success or failure of a test.  EXPECT_TRUE and EXPECT_EQ are
// examples of such macros.  For a complete list, see gtest.h.
//
// <TechnicalDetails>
//
// In Google Test, tests are grouped into test cases.  This is how we
// keep test code organized.  You should put logically related tests
// into the same test case.
//
// The test case name and the test name should both be valid C++
// identifiers.  And you should not use underscore (_) in the names.
//
// Google Test guarantees that each test you define is run exactly
// once, but it makes no guarantee on the order the tests are
// executed.  Therefore, you should write your tests in such a way
// that their results don't depend on their order.
//
// </TechnicalDetails>


// Tests Factorial().

// Tests factorial of negative numbers.
//TEST(BINARY_SEARCH_TREE_TEST, PUT) {
  //// This test is named "Negative", and belongs to the "FactorialTest"
  //// test case.
  //using verihy::data_structure::binary_search_tree::binary_search_tree;
  //using verihy::data_structure::binary_search_tree::node;
  //binary_search_tree<char, int> a;

  //a.put('a', 100);
  //a.put('d', 101);
  //a.put('c', 223);
  
  //EXPECT_EQ(a.get('c'), 223);
  //EXPECT_EQ(a.get('d'), 101);
  //EXPECT_EQ(a.get('a'), 100);

  
  ////EXPECT_EQ(1, Factorial(-5));
  ////EXPECT_EQ(1, Factorial(-1));
  ////EXPECT_GT(Factorial(-10), 0);

  //// <TechnicalDetails>
  ////
  //// EXPECT_EQ(expected, actual) is the same as
  ////
  ////   EXPECT_TRUE((expected) == (actual))
  ////
  //// except that it will print both the expected value and the actual
  //// value when the assertion fails.  This is very helpful for
  //// debugging.  Therefore in this case EXPECT_EQ is preferred.
  ////
  //// On the other hand, EXPECT_TRUE accepts any Boolean expression,
  //// and is thus more general.
  ////
  //// </TechnicalDetails>
//}

//TEST(BINARY_SEARCH_TREE, CHANGE){
  //using verihy::data_structure::binary_search_tree::binary_search_tree;
  //using verihy::data_structure::binary_search_tree::node;
  //binary_search_tree<char, int> a;

  //a.put('a', 100);
  //a.put('d', 101);
  //ASSERT_EQ(100, a.get('a'));
  //a.put('a', 223);

  //ASSERT_EQ(223, a.get('a'));
  //a.remove('d');
  

//}

// Tests factorial of 0.
/*TEST(FactorialTest, Zero) {*/
  //EXPECT_EQ(1, Factorial(0));
//}

//// Tests factorial of positive numbers.
//TEST(FactorialTest, Positive) {
  //EXPECT_EQ(1, Factorial(1));
  //EXPECT_EQ(2, Factorial(2));
  //EXPECT_EQ(6, Factorial(3));
  //EXPECT_EQ(40320, Factorial(8));
//}


//// Tests IsPrime()

//// Tests negative input.
//TEST(IsPrimeTest, Negative) {
  //// This test belongs to the IsPrimeTest test case.

  //EXPECT_FALSE(IsPrime(-1));
  //EXPECT_FALSE(IsPrime(-2));
  //EXPECT_FALSE(IsPrime(INT_MIN));
//}

//// Tests some trivial cases.
//TEST(IsPrimeTest, Trivial) {
  //EXPECT_FALSE(IsPrime(0));
  //EXPECT_FALSE(IsPrime(1));
  //EXPECT_TRUE(IsPrime(2));
  //EXPECT_TRUE(IsPrime(3));
//}

//// Tests positive input.
//TEST(IsPrimeTest, Positive) {
  //EXPECT_FALSE(IsPrime(4));
  //EXPECT_TRUE(IsPrime(5));
  //EXPECT_FALSE(IsPrime(6));
  //EXPECT_TRUE(IsPrime(23));
//}

//// Step 3. Call RUN_ALL_TESTS() in main().
////
//// We do this by linking in src/gtest_main.cc file, which consists of
//// a main() function which calls RUN_ALL_TESTS() for us.
////
//// This runs all the tests you've defined, prints the result, and
//// returns 0 if successful, or 1 otherwise.
////
//// Did you notice that we didn't register the tests?  The
//// RUN_ALL_TESTS() macro magically knows about all the tests we
// defined.  Isn't this convenient?
//
//
#include <sstream>
#include <map>
using std::ostringstream;
using std::istringstream;
using std::ostream;
using std::istream;
using std::string;
using std::vector;
using std::map;
#include <cstdio>
#include <algorithm>
using std::pair;

TEST(BIG_INT, INT_CONSTRUCTOR){
    using verihy::math::big_int;
    map<int , string> mp{
        {3, "3"},
        {134, "134"},
        {333, "333"},
        {0, "0"},
        {-11, "-11"},
        {-32455666, "-32455666"},
        {342455666, "342455666"},
    };
    for(const auto &ps: mp){
        big_int p = ps.first;
        ostringstream res;
        res << p;
        ASSERT_EQ((ps.second).c_str(), res.str());
    }

}

TEST(BIG_INT, STR_CONSTRUCTOR){
    using verihy::math::big_int;
    //std::vector<big_int> a = {big_int(1234563), big_int(2134524566), big_int(0), big_int(-3242445)};
    //for(auto &p : a){
    //bool is_negative;
    //char *str = debug::_pre_trans("-134", is_negative);
    //printf("%s\n", str);
    //std::cout << debug::_pre_trans("-134", is_negative) << std::endl;
    vector<string> test_set = {"00001","134","1344","0","-11", "32434255", "-3242355325", "-0", "-234235325"};
    map<string, string> mp{
        {"00001", "1"},
        {"134", "134"},
        {"+333", "333"},
        {"333", "333"},
        {"0", "0"},
        {"+0", "0"},
        {"-0", "0"},
        {"-00000", "0"},
        {"+00000", "0"},
        {"+000", "0"},
        {"-11", "-11"},
        {"-0032455666", "-32455666"},
        {"-344353433464546262454654564526432455666", "-344353433464546262454654564526432455666"}
    };
    for(const auto &ps: mp){
        big_int p = (ps.first).c_str();
        ostringstream res;
        res << p;
        ASSERT_EQ((ps.second).c_str(), res.str());
    }
}

TEST(BIG_INT, STRING_CONSTRUCTOR){
    using verihy::math::big_int;
    //std::vector<big_int> a = {big_int(1234563), big_int(2134524566), big_int(0), big_int(-3242445)};
    //for(auto &p : a){
    //bool is_negative;
    //printf("%s\n", str);
    map<string, string> mp{
        {"00001", "1"},
        {"134", "134"},
        {"0", "0"},
        {"+0", "0"},
        {"-0", "0"},
        {"-00000", "0"},
        {"+00000", "0"},
        {"+000", "0"},
        {"-11", "-11"},
        {"-0032455666", "-32455666"},
        {"-344353433464546262454654564526432455666", "-344353433464546262454654564526432455666"},
        {"234595590265275086776698", "234595590265275086776698"},


    };
    for(const auto &ps:mp){
        big_int p = (ps.first);
        ostringstream res;
        res << p;
        ASSERT_EQ((ps.second), res.str());
    }
}

TEST(BIG_INT, COPY_CONSTRUCTOR){
    using verihy::math::big_int;
    //std::vector<big_int> a = {big_int(1234563), big_int(2134524566), big_int(0), big_int(-3242445)};
    //for(auto &p : a){
    //bool is_negative;
    //char *str = debug::_pre_trans("-134", is_negative);
    //printf("%s\n", str);
    //std::cout << debug::_pre_trans("-134", is_negative) << std::endl;
    map<string, string> mp{
        {"00001", "1"},
        {"134", "134"},
        {"0", "0"},
        {"+0", "0"},
        {"-0", "0"},
        {"-00000", "0"},
        {"+00000", "0"},
        {"30007","30007"},
        {"+000", "0"},
        {"-11", "-11"},
        {"-0032455666", "-32455666"},
        {"-344353433464546262454654564526432455666", "-344353433464546262454654564526432455666"}
    };
    for(const auto &ps:mp){
        big_int tp = (ps.first);
        big_int p(tp);
        big_int cp;
        cp = tp;
        ostringstream res;
        ostringstream cres;
        res << p;
        cres << cp;
        ASSERT_EQ((ps.second), res.str());
        ASSERT_EQ((ps.second), cres.str());
    }
}

TEST(BIG_INT, COMPARE){
    using verihy::math::big_int;
    //std::vector<big_int> a = {big_int(1234563), big_int(2134524566), big_int(0), big_int(-3242445)};
    //for(auto &p : a){
    //bool is_negative;
    //char *str = debug::_pre_trans("-134", is_negative);
    //printf("%s\n", str);
    //std::cout << debug::_pre_trans("-134", is_negative) << std::endl;
    ASSERT_EQ(big_int("2344") < big_int("2344"), false);
    ASSERT_EQ(big_int("12344") < big_int("2344"), false);
    ASSERT_EQ(big_int("12344") < big_int("1452344"), true);
    ASSERT_EQ(big_int("-12344") < big_int("1452344"), true);
    ASSERT_EQ(big_int("-0") < big_int("+0"), false);
    ASSERT_EQ(big_int("-0") < big_int("-034"), false);
    ASSERT_EQ(big_int("32423450") < big_int("32423451"), true);
    big_int p1 = "2344";
    big_int p2 = "2444";
    p2 = p2;
    ASSERT_EQ(p2, big_int("2444"));

    ASSERT_EQ(big_int("2344") > big_int("2344"), false );
    ASSERT_EQ(big_int("12344") > big_int("2344"), true);
    ASSERT_EQ(big_int("12344") > big_int("1452344"), false );
    ASSERT_EQ(big_int("-12344") > big_int("1452344"), false );
    ASSERT_EQ(big_int("-0") > big_int("+0"), false );
    ASSERT_EQ(big_int("-0") > big_int("-034"), true );
    ASSERT_EQ(big_int("32423450") > big_int("32423451"), false );

    ASSERT_EQ(big_int("2344") == big_int("2344"), true);
    ASSERT_EQ(big_int("12344") == big_int("2344"), false );
    ASSERT_EQ(big_int("-0")== big_int("+0"), true);
    ASSERT_EQ(big_int("-333")== big_int("333"), false );
    ASSERT_EQ(big_int("+333")== big_int("333"), true);
}

TEST(BIG_INT_OPERATOR, PLUS){
    using verihy::math::big_int;
    map<pair<string,string>,string> mp{
        {std::make_pair("4", "3" ), "7"},
        {std::make_pair("3", "4" ), "7"},
        {std::make_pair("4", "4" ), "8"},
        {std::make_pair("0", "0" ), "0"},
        {std::make_pair("4", "0" ), "4"},
        {std::make_pair("65525", "165555" ), "231080"},
        {std::make_pair("65535", "1" ), "65536"},
        {std::make_pair("65536", "1" ), "65537"},
        {std::make_pair("-65536", "1" ), "-65535"},
        {std::make_pair("435235243526", "452389527348" ), "887624770874"},
        //{std::make_pair("43244652623543252351", "234552345612651543524344" ), "234595590265275086776695"},
        {std::make_pair("43244652623543252354", "234552345612651543524344" ), "234595590265275086776698"},
        {std::make_pair("43244652623543252354", "-234552345612651543524344" ), "-234509100960028000271990"},
    };
    for(auto &p : mp){
        big_int lhs = p.first.first;
        big_int rhs = p.first.second;
        ASSERT_EQ(big_int(p.second), lhs + rhs);
        ASSERT_EQ(big_int(p.second), rhs + lhs);
    }
}

TEST(BIG_INT_OPERATOR, SUB){
    using verihy::math::big_int;
    ASSERT_EQ(big_int(5), big_int(12) - big_int(7));
    ASSERT_EQ(big_int(0), big_int(12) - big_int(12));
    ASSERT_EQ(big_int(-5), big_int(2) - big_int(7));
    ASSERT_EQ(big_int(-9), big_int(-2) - big_int(7));
    ASSERT_EQ(big_int(5), big_int(-2) - big_int(-7));
    ASSERT_EQ(big_int("-234118120819081"), big_int("234243523462") - big_int("234352364342543"));
    ASSERT_EQ(big_int("234118120819081"), big_int("-234243523462") - big_int("-234352364342543"));
    ASSERT_EQ(big_int("-0"), big_int("-234243523462") - big_int("-234243523462"));
}

TEST(BIG_INT_OPERATOR, MUL){
    using verihy::math::big_int;
    ASSERT_EQ(big_int(84), big_int(12) * big_int(7));
    ASSERT_EQ(big_int("552847240836"), big_int("65538") * big_int("8435522"));
    ASSERT_EQ(big_int("12345654321"), big_int("111111") * big_int("111111"));
    //ASSERT_EQ(big_int(0), big_int(12) - big_int(12));
    //ASSERT_EQ(big_int(-5), big_int(2) - big_int(7));
    //ASSERT_EQ(big_int(-9), big_int(-2) - big_int(7));
    //ASSERT_EQ(big_int(5), big_int(-2) - big_int(-7));
    //ASSERT_EQ(big_int("-234118120819081"), big_int("234243523462") - big_int("234352364342543"));
    //ASSERT_EQ(big_int("234118120819081"), big_int("-234243523462") - big_int("-234352364342543"));
    //ASSERT_EQ(big_int("-0"), big_int("-234243523462") - big_int("-234243523462"));
}
