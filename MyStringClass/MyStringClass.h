#ifndef MY_STRINGCLASS_H
#define MY_STRINGCLASS_H

#ifdef UNIT_TEST
  #define STATIC
  #define PRIVATE public
#else
  #define STATIC static
  #define PRIVATE private
#endif

class MyStringClass
{
  PRIVATE:
    char* MyString;
    int MyLength; // length of MyString without null-terminator
    STATIC int get_string_length(const char* tocheck);
    STATIC void init_string(char* toinit, int length);
    STATIC void copy_string_from_to(const char* from, char* to);
  public:
    MyStringClass(const char* initstring = nullptr);
    ~MyStringClass();
    MyStringClass& append(const char* toappend);
    void print(void);
    const char* c_str(void);
};

#endif // MY_STRINGCLASS_H
