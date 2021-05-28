cmake_minimum_required(VERSION 3.7)

project(Core6502Tests)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

include_directories(${Core6502_SOURCE_DIR}/include)

set (TEST_SOURCES
    "Core6502Tests_core.cpp"
    "Core6502Tests_main.cpp" 
    "Core6502Tests_LDA.cpp"  
    "Core6502Tests_LDX.cpp" 
    "Core6502Tests_LDY.cpp" 
    "Core6502Tests_STA.cpp"
    "Core6502Tests_STX.cpp"
    "Core6502Tests_STY.cpp"
    "Core6502Tests_StatusFlags.cpp"
    "Core6502Tests_Transfer.cpp"
    "Core6502Tests_AND.cpp"
    "Core6502Tests_EOR.cpp"
    "Core6502Tests_ORA.cpp"
    "Core6502Tests_BIT.cpp"
    "Core6502Tests_Increment.cpp"
    "Core6502Tests_Decrement.cpp"
    "Core6502Tests_Jump.cpp"
    "Core6502Tests_Branch.cpp"
    "Core6502Tests_CMP.cpp"
    "Core6502Tests_CPX.cpp"
    "Core6502Tests_CPY.cpp"
    "Core6502Tests_LSR.cpp"
    "Core6502Tests_ASL.cpp"
)

SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
SET(GCC_COVERAGE_LINK_FLAGS    "-lgcov")

source_group("src" FILES ${TEST_SOURCES})
add_executable(Core6502Tests ${TEST_SOURCES})
add_dependencies(Core6502Tests Core6502)
target_link_libraries(Core6502Tests gtest)
target_link_libraries(Core6502Tests Core6502)
