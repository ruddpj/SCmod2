cmake_minimum_required(VERSION 3.20)
project(RAL)

set(CMAKE_CXX_STANDARD 17)

# 1. Look for the NTL library
# NTL doesn't always have a built-in find_package, so we search for the library manually
find_library(NTL_LIB ntl)
find_path(NTL_INCLUDE_DIR NTL/ZZ.h)

add_executable(RAL main.cpp)

# 2. Include the headers
target_include_directories(RAL PRIVATE ${NTL_INCLUDE_DIR})

# 3. Link the library (This solves the "undefined reference" error)
target_link_libraries(RAL PRIVATE ${NTL_LIB} gmp) # NTL usually requires GMP as well