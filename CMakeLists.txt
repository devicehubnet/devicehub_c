project(devicehub)
cmake_minimum_required(VERSION 2.8)

set(VERSION "0.5.9")
aux_source_directory(src SRC_LIB_LIST)
aux_source_directory(examples SRC_LIST)


include_directories("${CMAKE_SOURCE_DIR}")

include_directories("${CMAKE_SOURCE_DIR}/src")


add_executable(${PROJECT_NAME} ${SRC_LIST} ${SRC_LIB_LIST})

add_library(src SHARED ${SRC_LIB_LIST})

 
SET(CMAKE_BUILD_TYPE Debug)
 
if(PAHO_INCLUDE_DIR)
    # Already in cache, be silent
    set(PAHO_FIND_QUIETLY TRUE)
endif(PAHO_INCLUDE_DIR)

 
find_path(PAHO_INCLUDE_DIR MQTTClient.h)
 
find_library(PAHO_LIBRARY NAMES paho-mqtt3c)
 
# Handle the QUIETLY and REQUIRED arguments and set PAHO_FOUND to TRUE if
# all listed variables are TRUE.
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(PAHO DEFAULT_MSG PAHO_LIBRARY PAHO_INCLUDE_DIR)
if(PAHO_FOUND)
  set(PAHO_LIBRARIES ${PAHO_LIBRARY})
else(PAHO_FOUND)
  set(PAHO_LIBRARIES)
endif(PAHO_FOUND)

if(PAHO_FOUND)
  target_link_libraries (${PROJECT_NAME} ${PAHO_LIBRARIES})
endif (PAHO_FOUND)


SET(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_VERSION ${VERSION})
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Cristi Vlad")
set(CPACK_PACKAGE_VENDOR "DeviceHub.net")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

INCLUDE(CPack)
