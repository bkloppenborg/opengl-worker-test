cmake_minimum_required(VERSION 2.8) 
project(worker-test CXX C)

find_package(OpenGL REQUIRED)
MESSAGE(STATUS "found OPENGL, lib = " ${OPENGL_LIBRARIES} )
add_definitions(-DGL_GLEXT_PROTOTYPES )

find_package(Qt4 COMPONENTS QtCore QtGui QtMain QtOpenGL REQUIRED)
INCLUDE(${QT_USE_FILE})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/QT ${CMAKE_CURRENT_BINARY_DIR}/QT)
add_subdirectory(QT) 

file(GLOB SOURCE *.cpp)

# Now add the binary
add_executable(worker-test ${SOURCE})

target_link_libraries(worker-test QT_files ${QT_LIBRARIES} ${OPENGL_LIBRARIES})
