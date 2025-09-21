cmake_minimum_required(VERSION 3.20.0)
project(MyString VERSION 0.0.1 LANGUAGES CXX)

#set cmake variables
set(CMAKE_CXX_STANDARD 11)

#add compiler options
add_compile_options(# options to activate gcov
                    -fprofile-arcs
                    -ftest-coverage
                    # other GCC flags
                    -Wall #show warnings
)

#add linker options
add_link_options(# options to link gcov libraries
                -lgcov
                 --coverage)

#paths to libraries under test
add_subdirectory(MyStringClass)

#main application (testrunner)
add_executable(TestMyString)
target_sources(TestMyString PRIVATE testrunner.cpp)

# Include GTest header path
include_directories(/usr/src/gtest/include)

# Include GTest compiled library path
link_directories(/usr/local/lib/)

#link the libraries under test to the testrunner application
target_link_libraries(TestMyString PRIVATE MyStringClass libgtest.a)