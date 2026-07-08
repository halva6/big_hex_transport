cmake_minimum_required(VERSION 3.16)

project(big-hex-transport)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(EMSCRIPTEN)
  add_library(raylib STATIC IMPORTED)

  set_target_properties(raylib PROPERTIES
      IMPORTED_LOCATION "/home/jason/Workspace/C/raylib-web/src/libraylib.a"
      INTERFACE_INCLUDE_DIRECTORIES "/home/jason/Workspace/C/raylib-web/src"
  )

  set(CMAKE_EXECUTABLE_SUFFIX ".html")

else()
  find_package(raylib REQUIRED)
endif()

file(GLOB_RECURSE SOURCES
    src/*.c
)

add_executable(${PROJECT_NAME} ${SOURCES})

if(EMSCRIPTEN)
  target_link_options(${PROJECT_NAME} PRIVATE
        -sUSE_GLFW=3
        -sUSE_WEBGL2=1
        -sASSERTIONS=2
        -sWASM=1
        -sASYNCIFY
    )
  set_target_properties(${PROJECT_NAME} PROPERTIES
        LINK_FLAGS "--preload-file ${CMAKE_SOURCE_DIR}/assets@assets"
    )
endif()

target_include_directories(${PROJECT_NAME}
    PRIVATE
        src
        include
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        raylib
)
