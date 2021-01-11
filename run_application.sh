#! /bin/bash
##-------------------------------------------------------------------------------------------------
## HEADER INFORMATION
##-------------------------------------------------------------------------------------------------
## This Shell Script is used to obtain the program filename from build_name.txt in build_info
## after which it will execute it.

## Read the filename from the chosen location
SOURCE_FILENAME="${PWD}/build_info/build_name.txt"
RELEASE_TYPE="${PWD}/build_info/build_type.txt"
DEBUG_PREFIX="${PWD}/build_info/build_debug_prefix.txt"

## Read the filename
EXEC_FILENAME=(`cat $SOURCE_FILENAME`)
EXEC_FILENAME=${EXEC_FILENAME}

## Read the debug prefix
RELEASE_TYPE=(`cat ${RELEASE_TYPE}`)

## Read whether its a release version or debug version
DEBUG_PREFIX=(`cat ${DEBUG_PREFIX}`)

## Change directory to execute the file
cd build/src
if [ ${RELEASE_TYPE} = "Release" ] || [ ${RELEASE_TYPE} = "release" ]; then
echo "Running Release Application: " ${EXEC_FILENAME}
./${EXEC_FILENAME}
else
echo "Running Debug Application: " ${EXEC_FILENAME}-${DEBUG_PREFIX}
./${EXEC_FILENAME}-${DEBUG_PREFIX}
fi