
cmake_minimum_required(VERSION 3.10)
project(NS750)

#Settings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# set target name
set(TARGET_SERVER server)
set(TARGET_CLIENT client)


#Setting
include_directories(${CMAKE_SOURCE_DIR}/include)

# set shared objects
set(SHARED_OBJECTS ${CMAKE_SOURCE_DIR}/src/socket.cpp)

#file

add_executable( ${TARGET_SERVER} ${SHARED_OBJECTS} ${CMAKE_SOURCE_DIR}/src/server.cpp ${CMAKE_SOURCE_DIR}/src/sockserver.cpp)
set_property(TARGET ${TARGET_SERVER} PROPERTY CXX_STANDARD 11)
target_link_libraries(${TARGET_SERVER} pthread)

add_executable( ${TARGET_CLIENT} ${SHARED_OBJECTS} ${CMAKE_SOURCE_DIR}/src/client.cpp ${CMAKE_SOURCE_DIR}/src/sockclient.cpp)
set_property(TARGET ${TARGET_CLIENT} PROPERTY CXX_STANDARD 11)
target_link_libraries(${TARGET_CLIENT} pthread)