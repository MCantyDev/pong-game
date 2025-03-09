cmake_minimum_required(VERSION 3.28)

# Create Project
project(PongGame VERSION 1.0)

# Set the C++ Standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Include Directories
include_directories("${CMAKE_SOURCE_DIR}/include")
include_directories("${CMAKE_SOURCE_DIR}/libraries/include")

# Get Files
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE LIBS "${CMAKE_SOURCE_DIR}/libraries/lib/*.lib")

# Create the Executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link Libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS} opengl32 Winmm)
