project(Core6502SimpleExample)

set(CMAKECMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/examples)

include_directories(${Core6502_SOURCE_DIR}/include)

add_executable(Core6502SimpleExample main.cpp)
add_dependencies(Core6502SimpleExample Core6502)
target_link_libraries(Core6502SimpleExample Core6502)