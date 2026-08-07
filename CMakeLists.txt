cmake_minimum_required(VERSION 3.28.3)

if (NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 23)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

project(
	bitcoinDataReader
  VERSION 0.0.1
  DESCRIPTION ""
  HOMEPAGE_URL ""
  LANGUAGES CXX C)

###Compiler
add_compile_options(-Wall -Wextra -Wpedantic)


##Scripts 
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
include(Docs)

##Subdir
add_subdirectory(app)
add_subdirectory(lib)
add_subdirectory(extern)

