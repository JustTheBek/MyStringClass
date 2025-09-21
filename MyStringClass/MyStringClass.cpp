#include "MyStringClass.h"
#include <iostream>

MyStringClass::MyStringClass(const char* initstring)
{
  int initlength = this->get_string_length(initstring);

  this->MyString = new char[initlength];

  init_string(this->MyString, initlength);

  copy_string_from_to(initstring, this->MyString);

  this->MyLength = initlength-1; // don't store null-terminator

  //std::cout << "Created new instance of MyStringClass:" << this->MyString << "\n";
}

// deep-copy constructor
MyStringClass::MyStringClass(const MyStringClass& initstring)
{
  this->MyString = new char[initstring.MyLength+1]; // considering null-terminator

  init_string(this->MyString, initstring.MyLength+1);

  copy_string_from_to(initstring.MyString, this->MyString);

  this->MyLength = initstring.MyLength;
}

// move constructor
MyStringClass::MyStringClass(MyStringClass&& initstring)
{
  this->MyString = initstring.MyString;
  this->MyLength = initstring.MyLength;

  initstring.MyString = nullptr;
  initstring.MyLength = 0;
}

MyStringClass::~MyStringClass()
{
  //std::cout << "Descructor call for: " << this->MyString << std::endl;
  delete[] this->MyString;
}

int MyStringClass::get_string_length(const char* tocheck)
{
  int i;
  for(i = 0; tocheck[i] != '\0'; ++i){ }

  return i+1; // don't forget null-terminator
}

void MyStringClass::init_string(char* toinit, int length)
{
  //std::cout << "addr:" << &toinit << std::endl;
  for(int i = 0; i < length-1; ++i)
  {
    //std::cout << "before:" << (unsigned short)(toinit[i]);
    toinit[i] = (char)0xFFu; // fill up array with [1]s
    //std::cout << "after:" << (unsigned short)(toinit[i]) << std::endl;
  }
  toinit[length-1] = '\0'; // don't forget null-terminator
}

void MyStringClass::copy_string_from_to(const char* from, char* to)
{
  if(from == nullptr || to == nullptr)
  {
    std::cerr << "ERROR MyStringClass: String copy can't be executed, one of the pointers was nullptr! \n";
  }
  else
  {
    // TODO: add null-terminator check
    int fromsize = get_string_length(from);
    int tosize = get_string_length(to);

    if(fromsize > tosize)
    {
      std::cerr << "ERROR MyStringClass: String copy can't be executed, mismatch in size of strings, from:" << fromsize <<", to:" << tosize <<"\n";
    }
    else
    {
      // doesn't copy null-terminator
      for(int i = 0; i < fromsize-1; ++i)
      {
        to[i] = from[i];
      }
    }
  }
}

MyStringClass& MyStringClass::append(const char* toappend)
{
  int newlen = this->MyLength + get_string_length(toappend);
  char* temp = this->MyString;

  this->MyString = new char[newlen];
  init_string(this->MyString, newlen);

  copy_string_from_to(temp, this->MyString);
  copy_string_from_to(toappend, &this->MyString[this->MyLength]);

  this->MyLength = newlen - 1; // don't count null-terminator

  delete[] temp;

  return *this;
}

void MyStringClass::print(void) const
{
  std::cout << this->MyString; // don't print newline (\n)
}

const char* MyStringClass::c_str(void) const
{
    return (const char*)this->MyString;
}

int MyStringClass::length(void)
{
  return this->MyLength;
}

// deep-copy assignment operator
MyStringClass& MyStringClass::operator=(const MyStringClass& rhs)
{
  this->MyLength = rhs.MyLength;

  delete [] this->MyString;
  this->MyString = new char[rhs.MyLength+1]; // considering null-terminator

  init_string(this->MyString, rhs.MyLength+1);

  copy_string_from_to(rhs.MyString, this->MyString);

  return *this;
}

// move assignment operator
MyStringClass& MyStringClass::operator=(MyStringClass&& rhs)
{
  this->MyLength = rhs.MyLength;

  delete [] this->MyString;
  this->MyString = rhs.MyString;
  rhs.MyString = nullptr;
  rhs.MyLength = 0;

  return *this;
}

MyStringClass& MyStringClass::operator+=(const MyStringClass& rhs)  // add-assign operator with deep-copy
{
  this->append(rhs.MyString);

  return *this;
}

MyStringClass& MyStringClass::operator+=(const char* rhs)  // add-assign operator for cstring with deep-copy
{
  this->append(rhs);

  return *this;
}

MyStringClass MyStringClass::operator+(const MyStringClass& rhs)  // addition operator
{
  return MyStringClass(*this) += rhs;
}

MyStringClass MyStringClass::operator+(const char* rhs)  // addition operator for cstring
{
  return MyStringClass(*this) += rhs;
}

MyStringClass::operator const char*() const // conversion operator for const char*
{
  int newlen = this->MyLength+1;
  char* newchar = new char[this->MyLength+1]; // consider null-terminator
  init_string(newchar, newlen);
  copy_string_from_to(this->MyString, &newchar[0]);

  return newchar;
}