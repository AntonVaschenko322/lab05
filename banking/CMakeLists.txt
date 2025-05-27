cmake_minimum_required(VERSION 3.28)
project(Bank)
add_library(banking STATIC Account.cpp Transaction.cpp)
target_include_directories(banking  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
