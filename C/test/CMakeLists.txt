cmake_minimum_required(VERSION 3.10)
project(Homework008Test)

# 啟用 C 和 C++ 支援
enable_language(C CXX)

# 設定編譯參數以支援 Code Coverage (-fprofile-arcs -ftest-coverage)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -O0")

# 尋找 gtest 套件
find_package(GTest REQUIRED)

# 建立測試執行檔
add_executable(run_tests 
    homework008.c 
    test_homework008.cpp
)

# 加入這行，告訴編譯器我們現在是在測試模式
target_compile_definitions(run_tests PRIVATE TESTING)

# 連結 GTest 與 Coverage 必要的函式庫
target_link_libraries(run_tests gcov GTest::gtest GTest::gtest_main pthread)