project(devicehub)
cmake_minimum_required(VERSION 2.8)
 
set(VERSION "0.5.9")

add_executable(${PROJECT_NAME} test.c devicehub.c sensorList.c actuatorList.c)
 
include_directories("${CMAKE_SOURCE_DIR}")
 
SET(CMAKE_BUILD_TYPE Debug)



if(MOSQUITTO_INCLUDE_DIR)
    # Already in cache, be silent
    set(MOSQUITTO_FIND_QUIETLY TRUE)
endif(MOSQUITTO_INCLUDE_DIR)

find_path(MOSQUITTO_INCLUDE_DIR MQTTClient.h)

find_library(MOSQUITTO_LIBRARY NAMES paho-mqtt3c)

# Handle the QUIETLY and REQUIRED arguments and set MOSQUITTO_FOUND to TRUE if
# all listed variables are TRUE.
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MOSQUITTO DEFAULT_MSG MOSQUITTO_LIBRARY MOSQUITTO_INCLUDE_DIR)

if(MOSQUITTO_FOUND)
  set(MOSQUITTO_LIBRARIES ${MOSQUITTO_LIBRARY})
else(MOSQUITTO_FOUND)
  set(MOSQUITTO_LIBRARIES)
endif(MOSQUITTO_FOUND)


if(MOSQUITTO_FOUND)
  target_link_libraries (${PROJECT_NAME} ${MOSQUITTO_LIBRARIES})
endif (MOSQUITTO_FOUND)


INSTALL(TARGETS ${PROJECT_NAME} DESTINATION bin)
#INSTALL(FILES   ${CMAKE_SOURCE_DIR}/mqtt.conf.sample DESTINATION /etc/dh/)
#INSTALL(FILES   ${CMAKE_SOURCE_DIR}/scripts/upstart/dh_mqttbridge.conf DESTINATION /etc/init/)
 
SET(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_VERSION ${VERSION})
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Cristi Vlad")
set(CPACK_PACKAGE_VENDOR "devicehub.net")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
 
INCLUDE(CPack)
