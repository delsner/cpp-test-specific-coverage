cmake_minimum_required(VERSION 3.15)

# define source files
set(test_SRCS main.cpp mockbar.h testfoo.cpp testfoo.h)

# create binary for test execution
add_executable(unittests ${test_SRCS})

# link gtest as static library
target_link_libraries(unittests
        gtest_main
        gmock_main
        libfoo
        libtest
        )

target_compile_definitions(unittests PRIVATE   
       TEST_LISTENER
)