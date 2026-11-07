cmake_minimum_required(VERSION 3.23)

project(IndiePuppetier)

add_executable(main)

target_sources(main PRIVATE main.cpp)

message("Compiler is ${CMAKE_CXX_COMPILER_ID}")

# compiler option for c++ warnings
if(
  (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC") OR
  (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
)

  target_compile_options(main PRIVATE /W4)
  # target_link_libraries(main PRIVATE ${CMAKE_SOURCE_DIR}/external/lib/msvc22/glfw3dll.lib)

elseif(
  (CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR
  (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
)

  target_compile_options(main PRIVATE -Wall -Wextra)
  # target_link_libraries(main PRIVATE ${CMAKE_SOURCE_DIR}/external/lib/mingw/libglfw3dll.a)

endif()

target_link_libraries(main PRIVATE IPEngine)

add_subdirectory(IPEngine)

target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/include 
    ${CMAKE_SOURCE_DIR}/external/include)