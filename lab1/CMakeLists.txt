include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
cmake_minimum_required(VERSION 3.18)
project(progonka)
set(CMAKE_CXX_STANDARD 17)
add_executable(progonka progonka.cpp)
