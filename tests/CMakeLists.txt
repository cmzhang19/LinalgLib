include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(VectorTest VectorTest.cc)

target_link_libraries(VectorTest gtest_main)

add_executable(MatrixTest MatrixTest.cc)

target_link_libraries(MatrixTest gtest_main)

include(GoogleTest)
gtest_discover_tests(VectorTest)

target_link_libraries(VectorTest LinalgLib)

gtest_discover_tests(MatrixTest)

target_link_libraries(MatrixTest LinalgLib)