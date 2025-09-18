cmake_minimum_required(VERSION 4.0.0)
project(MyString VERSION 0.0.1 LANGUAGES CXX)

#set cmake variables
set(CMAKE_CXX_STANDARD 11)

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