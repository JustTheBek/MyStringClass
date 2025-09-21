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
   char teststring1 [] = "Hello";
   char teststring2 [] = " World!";
   MyStringClass myTestString(teststring1);

   // 2 Act
   myTestString.append(teststring2);

   // 3 Expect
   EXPECT_STREQ(myTestString.c_str(), "Hello World!");
   // don't count null-terminator
   EXPECT_EQ(myTestString.MyLength, (sizeof(teststring1) + sizeof(teststring2)) / sizeof(char) - 2);
}

// Tests deep-copy constructor.
TEST_F(MyStringClassTest, Test_MyStringClass_DeepCopyConstructor)
{
   // 1 Setup
   MyStringClass originalString("ThisIsATestString");

   // 2 Act
   MyStringClass newString(originalString);

   // 3 Expect
   EXPECT_STREQ(originalString.MyString, newString.MyString);
   EXPECT_EQ(originalString.MyLength, newString.MyLength);
   // check if ddep copy worked --> addresses have to be different
   EXPECT_NE(&originalString.MyString[0], &newString.MyString[0]);
}

// Tests move-copy constructor.
TEST_F(MyStringClassTest, Test_MyStringClass_MoveConstructor)
{
   // 1 Setup
   char origStr [] = "ThisIsATestString";
   int origLen = sizeof(origStr)/sizeof(char);
   MyStringClass originalString(origStr);
   char* origAddr = &originalString.MyString[0];

   // 2 Act
   MyStringClass newString(std::move(originalString));

   // 3 Expect
   EXPECT_STREQ(newString.MyString, origStr);
   EXPECT_EQ(newString.MyLength, origLen-1); // null-terminator is not counted
   // check if origStr is left 'empty'
   EXPECT_EQ(originalString.MyLength, 0);
   EXPECT_EQ(originalString.MyString, nullptr);
   // check if pointer got transfered
   EXPECT_EQ(&newString.MyString[0], origAddr);
}

// Tests deep-copy assignment operator.
TEST_F(MyStringClassTest, Test_MyStringClass_DeepCopyAssignmentOperator)
{
   // 1 Setup
   MyStringClass originalString("ThisIsMyStringWhereIWantToCopy");
   MyStringClass newString("ThisIsMyStringWhichIWantToCopy");

   // 2 Act
   originalString = newString;

   // 3 Expect
   EXPECT_STREQ(originalString.MyString, newString.MyString);
   EXPECT_EQ(originalString.MyLength, newString.MyLength);
   // check if deep copy worked --> addresses have to be different
   EXPECT_NE(&originalString.MyString[0], &newString.MyString[0]);
}

// Tests move assignment operator.
TEST_F(MyStringClassTest, Test_MyStringClass_MoveAssignmentOperator)
{
   // 1 Setup
   char origStr [] = "ThisIsMyStringWhereIWantToCopy";
   char newStr [] = "ThisIsMyStringWhichIWantToCopy";
   int newLen = sizeof(newStr)/sizeof(char);
   char* newAddr = nullptr;

   MyStringClass originalString(origStr);
   MyStringClass newString(newStr);
   newAddr = &newString.MyString[0];

   // 2 Act
   originalString = std::move(newString);

   // 3 Expect
   EXPECT_STREQ(originalString.MyString, newStr);
   EXPECT_EQ(originalString.MyLength, newLen-1); // null-terminator is not counted
   // check if newStr is left 'empty'
   EXPECT_EQ(newString.MyString, nullptr);
   EXPECT_EQ(newString.MyLength, 0);
   // check if pointer got transfered
   EXPECT_EQ(&originalString.MyString[0], newAddr);
}

// Tests add-assign assignment operator.
TEST_F(MyStringClassTest, Test_MyStringClass_AddAndAssignOperator)
{
   // 1 Setup
   char origStr [] = "Hello";
   char newStr [] = " World!";

   MyStringClass originalString(origStr);
   MyStringClass newString(newStr);

   // 2 Act
   originalString += newString;

   // 3 Expect
   EXPECT_STREQ(originalString.MyString, "Hello World!");
   EXPECT_EQ(originalString.MyLength, (sizeof(origStr) + sizeof(newStr)) / sizeof(char) - 2);
   // check if newstring remained the same
   EXPECT_STREQ(newString.MyString, newStr);
   EXPECT_EQ(newString.MyLength, sizeof(newStr)/sizeof(char)-1); // don't count null-terminator
}

// Tests add-assign assignment operator for cstring.
TEST_F(MyStringClassTest, Test_MyStringClass_AddAndAssignOperatorCstring)
{
   // 1 Setup
   char origStr [] = "Hello";
   char newStr [] = " World!";

   MyStringClass originalString(origStr);

   // 2 Act
   originalString += newStr;

   // 3 Expect
   EXPECT_STREQ(originalString.MyString, "Hello World!");
   EXPECT_EQ(originalString.MyLength, (sizeof(origStr) + sizeof(newStr)) / sizeof(char) - 2);
   // check if newstring remained the same
   EXPECT_STREQ(newStr, " World!");
}

// Tests addition assignment operator.
TEST_F(MyStringClassTest, Test_MyStringClass_AdditionOperator)
{
   // 1 Setup
   char origStr [] = "Hello";
   char newStr [] = " NewWorld!";

   MyStringClass originalString(origStr);
   MyStringClass newString(newStr);

   // 2 Act
   MyStringClass outString = originalString + newString;

   // 3 Expect
   EXPECT_STREQ(outString.MyString, "Hello NewWorld!");
   EXPECT_EQ(outString.MyLength, (sizeof(origStr) + sizeof(newStr)) / sizeof(char) - 2);
   // check if the original strings remained unchanged
   EXPECT_STREQ(originalString.MyString, origStr);
   EXPECT_EQ(originalString.MyLength, sizeof(origStr)/sizeof(char)-1); // don't count null-terminator
   EXPECT_STREQ(newString.MyString, newStr);
   EXPECT_EQ(newString.MyLength, sizeof(newStr)/sizeof(char)-1); // don't count null-terminator
   // check if addresses differ
   EXPECT_NE(&originalString.MyString[0], &outString.MyString[0]);
   EXPECT_NE(&newString.MyString[0], &outString.MyString[0]);
}

// Tests addition assignment operator for Cstr.
TEST_F(MyStringClassTest, Test_MyStringClass_AdditionOperatorCstr)
{
   // 1 Setup
   char origStr [] = "Hello";
   char newStr [] = " NewWorld!";
   char* newStrAddr = &newStr[0];

   MyStringClass originalString(origStr);

   // 2 Act
   MyStringClass outString = originalString + newStr;

   // 3 Expect
   EXPECT_STREQ(outString.MyString, "Hello NewWorld!");
   EXPECT_EQ(outString.MyLength, (sizeof(origStr) + sizeof(newStr)) / sizeof(char) - 2);
   // check if the original strings remained unchanged
   EXPECT_STREQ(originalString.MyString, origStr);
   EXPECT_EQ(originalString.MyLength, sizeof(origStr)/sizeof(char)-1); // don't count null-terminator
   EXPECT_STREQ(newStr, " NewWorld!");
   EXPECT_EQ(newStr, newStrAddr);
   // check if addresses differ
   EXPECT_NE(&originalString.MyString[0], &outString.MyString[0]);
   EXPECT_NE(&newStrAddr[0], &outString.MyString[0]);
}

// Tests conversion operator from MyStringClass to char*.
TEST_F(MyStringClassTest, Test_MyStringClass_ConversionOperatorToCstr)
{
   // 1 Setup
   char origStr [] = "ThisIsAnotherTestString";
   const char* newStr = nullptr;

   MyStringClass originalString(origStr);

   // 2 Act
   newStr = (const char*)originalString;

   // 3 Expect
   EXPECT_STREQ(originalString.MyString, newStr);
   EXPECT_EQ(originalString.MyLength, MyStringClass::get_string_length(newStr)-1); // don't count null-terminator
   // check if addresses differ
   EXPECT_NE(&originalString.MyString[0], &newStr[0]);
   EXPECT_NE(&origStr[0], &newStr[0]);
}


}  // namespace
}  // namespace project
}  // namespace my

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
