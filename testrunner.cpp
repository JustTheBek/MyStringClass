//#define UNIT_TEST

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
/*TEST_F(MyStringClassTest, Test_MyStringClass_Initsring) 
{
   // 1 Setup
   char testarray [5] = "abcd";
   char exptected [5] = "\xFF\xFF\xFF\xFF";
   MyStringClass myTestString("Hello"); // used only for function call

   std::cout << "Act" << std::endl;
   // 2 Act
   // no act is needed, the setup contained the action
   std::cout << "addr:" << long(&testarray[0]) << std::endl;
   myTestString.init_string(&testarray[0], 5);


   std::cout << "Exp" << std::endl;

   // 3 Expect
   EXPECT_STREQ(&testarray[0], &exptected[0]);
}
*/
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
