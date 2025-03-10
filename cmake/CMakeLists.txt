cmake_minimum_required(VERSION 3.28)

# Create Project
project(PongGame VERSION 1.0)

# Set the C++ Standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Set Output Directory for Executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(DEBUG_LIBS "${CMAKE_CURRENT_SOURCE_DIR}/../libraries/lib/Debug")
set(RELEASE_LIBS "${CMAKE_CURRENT_SOURCE_DIR}/../libraries/lib/Release")
set(ASSETS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../project/assets")

# Include Directories
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../project/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../libraries/include")

# Get Correct Libraries based on Build-Type
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Building Debug version")
    file(GLOB_RECURSE LIBS "${DEBUG_LIBS}/*.lib")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Building Release version")
    file(GLOB_RECURSE LIBS "${RELEASE_LIBS}/*.lib")
else()
    message(WARNING "Unknown build type, using release libraries")
    file(GLOB_RECURSE LIBS "${RELEASE_LIBS}/*.lib")
endif()

# Get rid of the Warnings because nothing else i do gets rid of them if i use Debug mode
# But I dont really need the PDB for SFML regardless as I would only need to Debug my own program
if(MSVC)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /IGNORE:4099")
endif()

# Get Source Files
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../project/src/*.cpp")

# Copy the Required Assets
file(COPY ${ASSETS_DIR}/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
message(STATUS "Copying Required Assets from ${ASSETS_DIR} to ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

# Create the Executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link Libraries
target_link_libraries(${PROJECT_NAME} PRIVATE 
    ${LIBS} 
    opengl32 
    Winmm
)
