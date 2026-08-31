cmake_minimum_required(VERSION 3.28)

project("TheResidual")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(THE_RESIDUAL_BUILD_TESTS "Build The Residual tests" OFF)

add_executable(${PROJECT_NAME} WIN32)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)

set(RINVID_BUILD_TESTS OFF CACHE BOOL "Build Rinvid tests")
set(RINVID_BUILD_BENCHMARKS OFF CACHE BOOL "Build Rinvid benchmarks")
add_subdirectory(Rinvid)

target_link_libraries(${PROJECT_NAME} PRIVATE rinvid)
rinvid_copy_runtime_dependencies(${PROJECT_NAME})

# Rinvid's MinGW runtime DLL list is scoped to its subdirectory, so it is not
# visible when the helper above is called for this parent-project target.
if(MINGW)
  get_filename_component(MINGW_RUNTIME_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY)
  foreach(MINGW_RUNTIME_DLL IN ITEMS libgcc_s_seh-1.dll libstdc++-6.dll
                                    libwinpthread-1.dll)
    if(EXISTS "${MINGW_RUNTIME_DIR}/${MINGW_RUNTIME_DLL}")
      add_custom_command(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${MINGW_RUNTIME_DIR}/${MINGW_RUNTIME_DLL}"
                $<TARGET_FILE_DIR:${PROJECT_NAME}>)
    endif()
  endforeach()
endif()

if(THE_RESIDUAL_BUILD_TESTS)
  enable_testing()

  add_executable(player_progress_test tests/player_progress_test.cpp src/player_progress.cpp)
  target_include_directories(player_progress_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
  target_compile_options(player_progress_test PRIVATE -Wall -Wextra -Werror)

  add_test(NAME player_progress_test COMMAND player_progress_test)
endif()

# Copy resources to build directory so the executable can find them
set(EXAMPLE_RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)
add_custom_command(
  TARGET TheResidual
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${EXAMPLE_RESOURCES_DIR}
          $<TARGET_FILE_DIR:TheResidual>/resources)
