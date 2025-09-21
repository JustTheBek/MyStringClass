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
    MyStringClass(const char* initstring = nullptr);     // constructor with char string = default
    MyStringClass(const MyStringClass& rhs);             // deep-copy cunstructor
    MyStringClass(MyStringClass&& rhs);                  // move cunstructor
    ~MyStringClass();                                    // destructor
    MyStringClass& append(const char* toappend);
    void print(void) const;
    const char* c_str(void) const;
    int length(void);
    MyStringClass& operator=(const MyStringClass& rhs);  // deep-copy assignment operator
    MyStringClass& operator=(MyStringClass&& rhs); // move assignment operator
    MyStringClass& operator+=(const MyStringClass& rhs);  // add-assign operator with deep-copy
    MyStringClass& operator+=(const char* rhs);  // add-assign operator for cstring with deep-copy
    MyStringClass operator+(const MyStringClass& rhs);  // addition operator
    MyStringClass operator+(const char* rhs);  // addition operator for cstring
    operator const char*() const; // conversion operator for const char*
};

#endif // MY_STRINGCLASS_H
