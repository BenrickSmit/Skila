##------------------------------------------------------------------------------
## SECTION: Setup the Source Executable
##------------------------------------------------------------------------------
set(BOOL_CREATE_INSTALLER OFF)
set(BOOL_CREATE_EXECUTABLE ON)
set(BOOL_CREATE_LIBRARY OFF)
set(BOOL_PROFILE_CODE OFF)
set(BOOL_USE_BOOST OFF)

## Read whether the application is a Debug or Release version
## Redundant but can't hurt... I think? Shouldn't at least
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
file(STRINGS "../build_info/build_bit_release.txt" STRING_BUILD_ARCHITECTURE)
if(${STRING_BUILD_ARCHITECTURE} STREQUAL "64" OR ${STRING_BUILD_ARCHITECTURE} STREQUAL "x64")
    SET(STRING_BUILD_ARCHITECTURE "x64")
    SET(CMAKE_GENERATOR_PLATFORM ${STRING_BUILD_ARCHITECTURE})
    message(STATUS "PLATFORM CHOICE: ${STRING_BUILD_ARCHITECTURE}} \"64Bit\"")
else()
SET(STRING_BUILD_ARCHITECTURE "x86")
SET(CMAKE_GENERATOR_PLATFORM ${STRING_BUILD_ARCHITECTURE})
message(STATUS "PLATFORM CHOICE: ${STRING_BUILD_ARCHITECTURE}} \"32Bit\"")
endif()

## Read the required C++ version
file(STRINGS "../build_info/build_cxx_standard.txt" STRING_REQUIRED_CXX_STANDARD)

## Find a list of all files in the current CMake Directory
file(GLOB_RECURSE EXEC_FILE_SOURCES LIST_DIRECTORIES false *.h *.cpp)

## Set the required C++ Standard
set(CMAKE_CXX_STANDARD ${STRING_REQUIRED_CXX_STANDARD})
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## Enable gprof profiling of code
if(${BOOL_PROFILE_CODE})
    #set(DCMAKE_CXX_FLAGS "${DCMAKE_CXX_FLAGS} -pg")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")
endif()

## Ensure the use of pthreads for the library
set(THREADS_PREFER_PTHREADS_FLAG ON)
find_package(Threads REQUIRED)
find_package(OpenGL REQUIRED)

set(GLEW_DIR "${CMAKE_SOURCE_DIR}/lib/glew-2.1.0")
set(GLM_DIR "${CMAKE_SOURCE_DIR}/lib/glm")
include_directories(
    "${GLEW_DIR}/include")
add_definitions(
    -DGLEW_STATIC)

##------------------------------------------------------------------------------
## SECTION: Create an executable
##------------------------------------------------------------------------------
if(${BOOL_CREATE_EXECUTABLE})
    ## Create the required executable
    add_executable(${PROJECT_NAME} ${EXEC_FILE_SOURCES})
    
    ## Allow for Release and Debug Versions
    if(${BOOL_RELEASE_VERSION})
        set_target_properties(${PROJECT_NAME} PROPERTIES RELEASE_POSTFIX "${CMAKE_RELEASE_POSTFIX}")
        message(STATUS ">> BUILD_TYPE: RELEASE")
    else()
        set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "${CMAKE_DEBUG_POSTFIX}")
        message(STATUS ">> BUILD_TYPE: DEBUG")
    endif()

    ## Allow for threads
    target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL ${OPENGL_LIBRARIES})
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
    #target_link_libraries(${PROJECT_NAME} PRIVATE ${GLFW_LIBRARIES})
    if(UNIX)
        ## For Unix-based Compilation
        add_compile_definitions(GLEW_STATIC)
        #set(GLEW_LINK_LIBRARY ${GLEW_DIR}/lib/glew32s.lib)
        target_link_libraries(${PROJECT_NAME} PRIVATE ${GLEW_DIR}/lib/libGLEW.a)
        message(STATUS ">> UNIX GLEW Compilation")
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
    
    
    ## If the file is successfully created, move it to bin and create a dir
    ## for the current <compiler>_<OS>_<version>
    set(EXEC_LOCATION ${CMAKE_SOURCE_DIR}/build/src/${PROJECT_NAME})
    if(EXISTS ${EXEC_LOCATION})
        ## Create the directory
        set(BASE_DIR ${CMAKE_SOURCE_DIR}/bin/exec)
        add_custom_target(build-time-make-base-exec-directory ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${BASE_DIR})
    	set(DIR_NAME ${CMAKE_SOURCE_DIR}/bin/exec/${CMAKE_CXX_COMPILER_ID}_${CMAKE_SYSTEM_NAME}_${PROJECT_NAME}_${PROJECT_VERSION})
    	add_custom_target(build-time-make-exec-directory ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${DIR_NAME})
    	
    	## Try and copy the file
    	add_custom_command(
    		TARGET ${PROJECT_NAME} POST_BUILD
    		COMMAND ${CMAKE_COMMAND} -E copy
    		${EXEC_LOCATION}
    		${DIR_NAME})
    endif()
endif()

##------------------------------------------------------------------------------
## SECTION: Create a library
##------------------------------------------------------------------------------
if(${BOOL_CREATE_LIBRARY})
    ## Create the required library
    add_library(${PROJECT_NAME}_lib STATIC ${EXEC_FILE_SOURCES} "MatrixOperations.cpp")
    ## ALlow for 32-bit compilation
    if(BOOL_32_BIT_COMPILATION)
        if(!UNIX)
            set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_OPTIONS "-m32" LINK_OPTIONS "-m32")
        endif()
    endif()

    ## Allow for threads
    target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL ${OPENGL_LIBRARIES})
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw ${GLFW_LIBRARIES})

    ## If the file is successfully created, move it to bin and create a dir
    ## for the current lib_<compiler>_<OS>_<version>
    set(LIB_LOCATION ${CMAKE_SOURCE_DIR}/build/src/${PROJECT_NAME}_lib)
    if(EXISTS ${LIB_LOCATION})
        ## Create the directory
        set(BASE_DIR ${CMAKE_SOURCE_DIR}/bin/libs)
        add_custom_target(build-time-make-base-lib-directory ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${BASE_DIR})
    	set(DIR_NAME ${CMAKE_SOURCE_DIR}/bin/libs/lib_${CMAKE_CXX_COMPILER_ID}_${CMAKE_SYSTEM_NAME}_${PROJECT_NAME}_${PROJECT_VERSION})
    	add_custom_target(build-time-make-lib-directory ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${DIR_NAME})
    	
    	## Try and copy the file
    	add_custom_command(
    		TARGET ${PROJECT_NAME}_lib POST_BUILD
    		COMMAND ${CMAKE_COMMAND} -E copy
    		${LIB_LOCATION}
    		${DIR_NAME}/)
    endif()
endif()

##------------------------------------------------------------------------------
## SECTION: Create an installer with CPack
##------------------------------------------------------------------------------
## CPack Information if you want to create an installer
if(${BOOL_CREATE_INSTALLER})
    set(CPACK_PROJECT_NAME ${PROJECT_NAME})
    set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
    set(CPACK_VERBATIM_VARIABLES true)
    set(CPACK_PACKAGE_VERSION_MAJOR 0)
    set(CPACK_PACKAGE_VERSION_MINOR 1)
    set(CPACK_PACKAGE_VERSION_PATCH 0)
    #set(CPACK_PACKAGE_DESCRIPTION_SUMMARY )
    #set(CPACK_PACKAGE_DESCRIPTION_FILE )
    #set(CPACK_RESOURCE_FILE_WELCOME )
    set(CPACK_RESOURCE_FILE_LICENSE ../LICENSE)
    set(CPACK_RESOURCE_FILE_README ../README.md)
    include(CPack)
endif()

##------------------------------------------------------------------------------
## SECTION: Potential Future Version Will include
##------------------------------------------------------------------------------
#if(${BOOL_USE_BOOST})
#    set(Boost_USE_STATIC_LIBS OFF) 
#    set(Boost_USE_MULTITHREADED ON)  
#    set(Boost_USE_STATIC_RUNTIME OFF)
    
#    set(BOOST_LIBRARIES_TO_USE filesystem thread regex)
    
#    find_package(Boost 1.45.0 COMPONENTS ${BOOST_LIBRARIES_TO_USE}) 

#    if(Boost_FOUND)
#        include_directories(${Boost_INCLUDE_DIRS}) 
#        add_executable(progname file1.cxx file2.cxx) 
#        target_link_libraries(progname ${Boost_LIBRARIES})
#    endif()
#endif()
