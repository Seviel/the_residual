cmake_minimum_required(VERSION 3.16.3)

project("TheResidual")

set(CMAKE_CXX_STANDARD 17)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs)
add_executable(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE SOURCES "src/*.cpp")

target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)

execute_process(COMMAND uname OUTPUT_VARIABLE uname)
if(uname MATCHES "^MSYS" OR uname MATCHES "^MINGW")
  # target_link_libraries( ${PROJECT_NAME} PRIVATE rinvid opengl32 winmm gdi32
  # freetype sfml-window sfml-system sfml-audio)
else()
  target_link_libraries(${PROJECT_NAME} PRIVATE rinvid GL sfml-window
                                                sfml-system)
endif()
