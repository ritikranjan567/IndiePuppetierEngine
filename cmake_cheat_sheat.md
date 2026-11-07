## Basic Commands

- `cmake -S <dir>` make thee dir the root dir of the project
- `cmake -G Ninja -B build` generates a build system in the mentioned folder; here it is `build`
- `cmake --build build` executes the build system and generates the executable or lib inside the mentioned folder; here it is `build`

```cmake.txt
cmake_minimum_required(VERSION 3.23) // mentioned the minimun required version of cmake required

project(MyProjectName) // simply tells name of project but does a lot in back
```

`add_executable(MyProgram)` creates MyProgram.exe or executable file  
`add_library(MyLibrary)` similarly creates lib

```
target_sources(MyProgram
  PRIVATE
    main.cxx
)
```
This addes sorce files, like other cpp and other implementation to the executable or lib
Below includes header files in executable or lib:
```
target_sources(MyLibrary
  PRIVATE
    library_implementation.cxx

  PUBLIC
    FILE_SET myHeaders
    TYPE HEADERS
    BASE_DIRS
      include
    FILES
      include/library_header.h
)
```

### Linking libs

```CMakeLists.txt
target_link_libraries(MyProgram
  PRIVATE
    MyLibrary
)
```

`add_subdirectory(SubdirectoryName)` 
command allows us to incorporate CMLs located in subdirectories of the project.

When a CMakeLists.txt in a subdirectory is being processed by CMake all relative paths described in the subdirectory CML are relative to that subdirectory, not the top-level CML.

`cmake --build build --clean-first` use this after reorganization to avoid conflict in build system.

### cmake lang basic
```
set(var "World!")
message("Hello ${var}")
```

Loop example:
```
set(stooges "Moe;Larry")
list(APPEND stooges "Curly")

message("Stooges contains: ${stooges}")

foreach(stooge IN LISTS stooges)
  message("Hello, ${stooge}")
endforeach()
```

### Conditional
```
if(True)
  message("Constant Value: True")
else()
  message("Constant Value: False")
endif()
```

`target_compile_features(MyApp PRIVATE cxx_std_20)` command describes a minimum language standard as a target property

`target_compile_options(MyApp PRIVATE -Wall -Werror)` add compile options, although used mindfully as this can vary compiler to compiler.  
This can be checked with `CMAKE_<LANG>_COMPILER_ID` variants like GNU, MSVC, and AppleClang.

```
if(
  (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC") OR
  (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
)

  target_compile_options(Tutorial PRIVATE /W3)

elseif(
  (CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR
  (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
)

  target_compile_options(Tutorial PRIVATE -Wall)

endif()
```

### Link and include directories

```
target_link_directories(MyApp PRIVATE Vendor/lib) # links lib in dir
target_include_directories(MyApp PRIVATE Vendor/include) # links header in the include dir


