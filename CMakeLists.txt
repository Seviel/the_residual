cmake_minimum_required(VERSION 3.28)

project("TheResidual")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)

set(RINVID_BUILD_TESTS OFF CACHE BOOL "Build Rinvid tests")
set(RINVID_BUILD_BENCHMARKS OFF CACHE BOOL "Build Rinvid benchmarks")
add_subdirectory(Rinvid)

target_link_libraries(${PROJECT_NAME} PRIVATE rinvid)
rinvid_copy_runtime_dependencies(${PROJECT_NAME})

# Copy resources to build directory so the executable can find them
set(EXAMPLE_RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)
add_custom_command(
  TARGET TheResidual
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${EXAMPLE_RESOURCES_DIR}
          $<TARGET_FILE_DIR:TheResidual>/resources)
