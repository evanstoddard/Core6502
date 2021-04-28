set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include_directories(${Core6502_SOURCE_DIR}/include)
add_library(Core6502 Core6502.cpp Core6502Operations.cpp)