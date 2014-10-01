set(SUBPROJECT_NAME PlayerApp)
project(${SUBPROJECT_NAME})
cmake_minimum_required(VERSION 2.8)
set(${SUBPROJECT_NAME}_VERSION_MAJOR 0)
set(${SUBPROJECT_NAME}_VERSION_MINOR 1)

message(STATUS "=== Configuring ${SUBPROJECT_NAME} ===")

# find dependencies
find_package(Boost 1.48.0 COMPONENTS system filesystem REQUIRED)
find_package(OpenCV 2.4.3 REQUIRED core highgui)

# source and header files
set(HEADERS
	VideoPlayer.hpp
)
set(SOURCE
	VideoPlayer.cpp
)

# add dependencies
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${Logging_SOURCE_DIR}/include)
include_directories(${ImageIO_SOURCE_DIR}/include)

# make executable
add_executable(${SUBPROJECT_NAME} ${SOURCE} ${HEADERS})
target_link_libraries(${SUBPROJECT_NAME} ImageIO Logging ${OpenCV_LIBS} ${Boost_LIBRARIES})
