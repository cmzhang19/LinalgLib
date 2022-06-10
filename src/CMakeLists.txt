
set(headers ${CMAKE_SOURCE_DIR}/include)

aux_source_directory(. DIR_SRCS)

add_library(LinalgLib ${DIR_SRCS})
target_include_directories(LinalgLib  PUBLIC "${headers}")

add_executable(main main.cpp)

target_link_libraries(main LinalgLib)

