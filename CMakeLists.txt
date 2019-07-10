cmake_minimum_required(VERSION 2.6)

project( ProjectName )

add_definitions( -std=c++0x )

# Set BOOST_ROOT environment variable to point to your local Boost dir.
#find_package( Boost REQUIRED )
#include_directories( ${Boost_INCLUDE_DIR} )

# find_package( CGAL REQUIRED )
# include( ${CGAL_USE_FILE} )

find_package( GTest REQUIRED )
include_directories( ${GTEST_INCLUDE_DIRS} )

# OpenCV
# Find OpenCV, you may need to set OpenCV_DIR variable
# to the absolute path to the directory containing OpenCVConfig.cmake file
# via the command line or GUI
#find_package(OpenCV REQUIRED)

# If the package has been found, several variables will
# be set, you can find the full list with descriptions
# in the OpenCVConfig.cmake file.
# Print some message showing some of them
# message(STATUS "OpenCV library status:")
# message(STATUS "    version: ${OpenCV_VERSION}")
# message(STATUS "    libraries: ${OpenCV_LIBS}")
# message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

# Link your application with OpenCV libraries
#target_link_libraries(xxx ${OpenCV_LIBS})

# compilation flags
#if(MSVC)
#  # Force to always compile with W4
#  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
#    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
#  else()
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
#  endif()
#elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
#  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3")
#endif()

add_subdirectory( src )
add_subdirectory( test )
add_subdirectory( ressources )

