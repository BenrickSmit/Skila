##------------------------------------------------------------------------------
## SECTION: add unit tests
##------------------------------------------------------------------------------
set(TEST_PROJECT_NAME "${PROJECT_NAME}_tests")

## Find a list of all files in the current CMake Directory
file(GLOB_RECURSE TEST_FILE_SOURCES LIST_DIRECTORIES false *.h *.cpp)

## Add the header and src files to be compiled
#file(GLOB_RECURSE HEADER_FILE_SOURCES CMAKE_CONFIGURE_DEPENDS LIST_DIRECTORIES false "../includes/*.h")
file(GLOB_RECURSE HEADER_SRC_FILE_SOURCES CMAKE_CONFIGURE_DEPENDS LIST_DIRECTORIES false "../src/*.cpp" "../src/*.c")

set(TEST_FILE_SOURCES ${TEST_FILE_SOURCES} ${HEADER_FILE_SOURCES} ${HEADER_SRC_FILE_SOURCES})
list(REMOVE_DUPLICATES TEST_FILE_SOURCES)

## Remove the main.cpp from the list of files
set(MAIN_CPP_INDEX -1)
list(FIND TEST_FILE_SOURCES "${CMAKE_SOURCE_DIR}/tests/../src/main.cpp" MAIN_CPP_INDEX)
list(REMOVE_AT TEST_FILE_SOURCES ${MAIN_CPP_INDEX})
list(FIND TEST_FILE_SOURCES "${CMAKE_SOURCE_DIR}/tests/../src/main.cpp" MAIN_CPP_INDEX)
message(">> INDEX: ${MAIN_CPP_INDEX}")

find_package(OpenGL REQUIRED)

set(GLEW_DIR "${CMAKE_SOURCE_DIR}/lib/glew-2.1.0")
set(GLM_DIR "${CMAKE_SOURCE_DIR}/lib/glm")
include_directories(
    "${GLEW_DIR}/include")
add_definitions(
    -DGLEW_STATIC)


#add_executable(${TEST_PROJECT_NAME} tests_main.cpp)
add_executable(${TEST_PROJECT_NAME} ${TEST_FILE_SOURCES})
## Find the Header And Source files to test
target_include_directories(${TEST_PROJECT_NAME} PRIVATE ../includes/ )
target_include_directories(${TEST_PROJECT_NAME} PRIVATE ../src/ )

target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
#target_link_libraries(${PROJECT_NAME} PRIVATE ${GLFW_LIBRARIES})
if(UNIX)
    ## For Unix-based Compilation
    add_compile_definitions(GLEW_STATIC)
    #set(GLEW_LINK_LIBRARY ${GLEW_DIR}/lib/glew32s.lib)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${GLEW_DIR}/lib/libGLEW.a)
    message(STATUS ">> [TEST] UNIX GLEW Compilation")
else()
    ## For Windows Compilation
    add_compile_definitions(GLEW_STATIC)
    #set(GLEW_LINK_LIBRARY ${GLEW_DIR}/lib/glew32s.lib)
    
    ## x86/x86_64 application
    if(${BOOL_32_BIT_COMPILATION})
        ## Release or Debug Library
        if(${BOOL_RELEASE_VERSION})
            target_link_libraries(${PROJECT_NAME} PRIVATE ${GLEW_DIR}/lib/Release/Win32/glew32s.lib)
        else()
            target_link_libraries(${PROJECT_NAME} PRIVATE ${GLEW_DIR}/lib/Debug/Win32/glew32s.lib)
        endif()
        message(STATUS ">> Using Win32 Static GLEW Library")
    else()
        ## Release or Debug Library
        if(${BOOL_RELEASE_VERSION})
            target_link_libraries(${PROJECT_NAME} PRIVATE ${GLEW_DIR}/lib/Release/x64/glew32s.lib)
        else()
            target_link_libraries(${PROJECT_NAME} PRIVATE ${GLEW_DIR}/lib/Debug/x64/glew32s.lib)
        endif()
        message(STATUS ">> Using x64 Static GLEW Library")
    endif()
    
    message(STATUS ">> Windows GLEW Compilation")
endif()


## Add Google Test to the framework, and run all unit tests
# Google C++ Testing Framework
# https://code.google.com/p/googletest/
set(THREAD_USED pthread)
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(THREAD_USED "")
endif()
target_link_libraries(${TEST_PROJECT_NAME} PUBLIC gtest gtest_main ${THREAD_USED})

## Required to add individual tests
#add_test(GOOGLE_TEST_ALIVE_TEST ${TEST_PROJECT_NAME})


