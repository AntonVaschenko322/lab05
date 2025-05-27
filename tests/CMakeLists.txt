project(testing)
add_executable(test1 acc_test.cpp)
enable_testing()
target_link_libraries(test1 banking gtest gmock)
