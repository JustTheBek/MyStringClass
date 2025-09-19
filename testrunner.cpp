#define UNIT_TEST

#include "MyStringClass.h"
#include <gtest/gtest.h>

namespace my {
namespace project {
namespace {

// The fixture for testing class MyStringClass.
class MyStringClassTest : public testing::Test 
{
  public:
   static bool HasFatalFailure();
  
   protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  MyStringClassTest() {
     // You can do set-up work for each test here.
  }

  ~MyStringClassTest() override {
     // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override {
     // Code here will be called immediately after the constructor (right
     // before each test).
  }

  void TearDown() override {
     // Code here will be called immediately after each test (right
     // before the destructor).
  }

  // Class members declared here can be used by all tests in the test suite
  // for Foo.
};

// Tests that initsring fills up char array with [1]s and the last field with '\0'.
TEST_F(MyStringClassTest, Test_MyStringClass_Initsring) 
{
   // 1 Setup
   char testarray [] = "abcd";
   char exptected [] = "\xFF\xFF\xFF\xFF";
   char* p = testarray;
   long addr = (long)p;
   MyStringClass myTestString("Hello"); // used only for function call

   //std::cout << "Act" << std::endl;
   // 2 Act
   // no act is needed, the setup contained the action
   //std::cout << "addr:0x" << std::hex << addr << std::endl;
   MyStringClass::init_string(p, 5); //TODO: talk with prof, why does this cause segfault

   //std::cout << "Exp" << std::endl;

   // 3 Expect
   EXPECT_STREQ(&testarray[0], &exptected[0]);
   //EXPECT_EQ(1,1);
}

// Tests that constructor (with const char*) works properly.
TEST_F(MyStringClassTest, Test_MyStringClass_ConstCharPtrConstructor) 
{
   // 1 Setup
   MyStringClass myTestString("Hello");

   // 2 Act
   // no act is needed, the setup contained the action

   // 3 Expect
   EXPECT_STREQ(myTestString.c_str(), "Hello");
}

// Tests that c_str() works properly (this is a getter for the private string)
TEST_F(MyStringClassTest, Test_MyStringClass_GetPrivateString) 
{
   // 1 Setup
   char testring [] = "This_Is_My_TestString";
   MyStringClass myTestString(testring);

   // 2 Act
   const char* result = myTestString.c_str();

   // 3 Expect
   EXPECT_STREQ(result, testring);
}

// Tests that length() works properly (this is a getter for the length excl. null-termiantor)
TEST_F(MyStringClassTest, Test_MyStringClass_GetLength) 
{
   // 1 Setup
   char testring [] = "This_Is_My_New_TestString";
   int test_length = sizeof(testring)/sizeof(char);
   MyStringClass myTestString(testring);

   // 2 Act
   int res = myTestString.length();

   // 3 Expect
   EXPECT_EQ(test_length-1, res); // null-terminator is not counted to length()
}

// Tests that append works properly.
TEST_F(MyStringClassTest, Test_MyStringClass_Append) 
{
   // 1 Setup
   MyStringClass myTestString("Hello");

   // 2 Act
   myTestString.append(" World!");

   // 3 Expect
   EXPECT_STREQ(myTestString.c_str(), "Hello World!");
}


}  // namespace
}  // namespace project
}  // namespace my

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
