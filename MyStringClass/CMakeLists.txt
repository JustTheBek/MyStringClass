add_library(MyStringClass STATIC)

#provide sources nedded to build the library
target_sources(MyStringClass
        PRIVATE
        MyStringClass.cpp
)

#interfaces (path of .h files) needed to link this lib
target_include_directories(MyStringClass
        PUBLIC
        ./
)
