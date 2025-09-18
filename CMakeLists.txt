cmake_minimum_required(VERSION 3.16.3)

project("TheResidual")

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE SOURCES "src/*.cpp")

target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)

add_subdirectory(Rinvid)

execute_process(COMMAND uname OUTPUT_VARIABLE uname)
if(uname MATCHES "^MSYS" OR uname MATCHES "^MINGW")
  target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE rinvid
            opengl32
            winmm
            gdi32
            freetype
            sfml-window
            sfml-system
            sfml-audio)
else()
  target_link_libraries(${PROJECT_NAME} PRIVATE rinvid GL sfml-window
                                                sfml-system)
endif()

# Copy resources to build directory so the executable can find them
set(EXAMPLE_RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)
add_custom_command(
  TARGET TheResidual
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${EXAMPLE_RESOURCES_DIR}
          $<TARGET_FILE_DIR:TheResidual>/resources)
