cmake_minimum_required(VERSION 3.23)

add_library(IPEngine)

target_sources(IPEngine PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/Window/Window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Window/GLFW.cpp
    ${CMAKE_SOURCE_DIR}/external/lib/glad/glad.c)

# compiler option for c++ warnings
if(
  (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC") OR
  (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
)

  target_compile_options(IPEngine PRIVATE /W4)
  target_link_libraries(IPEngine PRIVATE ${CMAKE_SOURCE_DIR}/external/lib/msvc22/glfw3dll.lib)

elseif(
  (CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR
  (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
)

  target_compile_options(IPEngine PRIVATE -Wall -Wextra)
  target_link_libraries(IPEngine PRIVATE ${CMAKE_SOURCE_DIR}/external/lib/mingw/libglfw3dll.a)

endif()

target_include_directories(IPEngine PRIVATE 
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/external/include)