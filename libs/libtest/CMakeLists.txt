include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(libtest_SRCS
    cov_listener.h
    cov_listener.cpp
)

# Declare the library
add_library(libtest STATIC
    ${libtest_SRCS}
)

# link gtest as static library
target_link_libraries(libtest
    gtest_main
)

# Specify here the include directories exported
# by this library
target_include_directories(libtest PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
