##------------------------------------------------------------------------------
## SECTION: Set Variables
##------------------------------------------------------------------------------
## Set some settings for the builder
set(BOOL_CREATE_TESTS ON)
set(BOOL_CREATE_EXECUTABLE ON)
set(BOOL_CREATE_LIBRARY OFF)

## For use with debug and release executables
#set(CMAKE_DEBUG_POSTFIX "-debug")
file(STRINGS "build_info/build_debug_prefix.txt" CMAKE_DEBUG_PREFIX)
set(CMAKE_RELEASE_POSTFIX "")

## Read whether the application is a Debug or Release version
file(STRINGS "build_info/build_type.txt" STRING_BUILD_TYPE)
SET(BOOL_RELEASE_VERSION ON)

if(${STRING_BUILD_TYPE} STREQUAL "Debug" OR ${STRING_BUILD_TYPE} STREQUAL "debug")
    SET(BOOL_RELEASE_VERSION OFF)
    SET(STRING_BUILD_TYPE "debug")
else()
    SET(STRING_BUILD_TYPE "release")
endif()

if(${BOOL_RELEASE_VERSION})
    set(CMAKE_BUILD_TYPE ${STRING_BUILD_TYPE})
else()
    set(CMAKE_BUILD_TYPE ${STRING_BUILD_TYPE})
endif()

## Read whether to create a 32bit application or 64bit application
file(STRINGS "build_info/build_bit_release.txt" STRING_BUILD_ARCHITECTURE)
if(NOT UNIX)
    if(${STRING_BUILD_ARCHITECTURE} STREQUAL "64" OR ${STRING_BUILD_ARCHITECTURE} STREQUAL "x64")
        SET(STRING_BUILD_ARCHITECTURE "x64")
        SET(CMAKE_GENERATOR_PLATFORM ${STRING_BUILD_ARCHITECTURE})
        message(STATUS ">> PLATFORM CHOICE: ${STRING_BUILD_ARCHITECTURE}} \"64Bit\"")
    else()
        SET(STRING_BUILD_ARCHITECTURE "x86")
        SET(CMAKE_GENERATOR_PLATFORM ${STRING_BUILD_ARCHITECTURE})
        message(STATUS ">> PLATFORM CHOICE: ${STRING_BUILD_ARCHITECTURE}} \"32Bit\"")
    endif()
else()
    message(STATUS ">> PLATFORM CHOICE: PLATFORM DEFAULT ${CMAKE_GENERATOR_PLATFORM} as Unix/Unix-related Machine")
endif()


## Obtain the project's base name and version number
file(STRINGS "build_info/build_name.txt" STRING_PROJECT_NAME)
file(STRINGS "build_info/build_version.txt" STRING_PROJECT_VERSION)

## Basic CMAKE Project Settings
cmake_minimum_required (VERSION 3.15 FATAL_ERROR)
project(${STRING_PROJECT_NAME} VERSION "${STRING_PROJECT_VERSION}")

##------------------------------------------------------------------------------
## SECTION: Add the required files to source
##------------------------------------------------------------------------------
## Add the source files to the executable
include_directories(includes)
include_directories(lib)
add_subdirectory(src)
add_subdirectory(lib)

##------------------------------------------------------------------------------
## SECTION: Enable OpenGL, GLFW, GLEW
##------------------------------------------------------------------------------
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

## GLFW
set(GLFW_DIR lib/glfw-3.3.2)
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory(${GLFW_DIR})


## GLEW
add_subdirectory("${CMAKE_SOURCE_DIR}/lib/glew-2.1.0/build/cmake" "${CMAKE_SOURCE_DIR/lib/glew-2.1.0/}")

##------------------------------------------------------------------------------
## SECTION: Enable testing on the project
##------------------------------------------------------------------------------
if(${BOOL_CREATE_TESTS})
    ## Enable Testing of the Program
    enable_testing()

    ## Add the Google Test (gtest) unit testing framework
    add_subdirectory(lib/googletest-release-1.10.0 EXCLUDE_FROM_ALL)
    ## Prevent overriding the parent project's compiler/linker settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    
    ## Add the Unit Tests
    add_subdirectory(tests)
endif()

##-----------------------------------------------------------------------------=
## SECTION: Create Bin directory
##------------------------------------------------------------------------------
file(MAKE_DIRECTORY bin)