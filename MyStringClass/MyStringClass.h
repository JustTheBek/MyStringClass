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
    static int get_string_length(const char* tocheck);
    static void init_string(char* toinit, int length);
    static void copy_string_from_to(const char* from, char* to);
  public:
    MyStringClass(const char* initstring = nullptr);
    ~MyStringClass();
    MyStringClass& append(const char* toappend);
    void print(void) const;
    const char* c_str(void) const;
    int length(void);
};

#endif // MY_STRINGCLASS_H
