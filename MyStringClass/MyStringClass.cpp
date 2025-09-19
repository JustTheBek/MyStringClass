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

MyStringClass::~MyStringClass()
{

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

  this->MyLength = newlen;

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