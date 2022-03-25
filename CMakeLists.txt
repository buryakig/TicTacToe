cmake_minimum_required(VERSION 3.6)
include(FetchContent)

set(CMAKE_SUPPRESS_REGENERATION true)

set(FOLDER_NAME TicTacToe)
set(PROJECT_NAME TicTacToe)
project(${PROJECT_NAME} CXX)

include(CMake/CMakeMacros.txt)

# Dunno
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Setting up python for bootstrap
if(WIN32)
	set(PYTHON_EXECUTABLE "python")
else()
	set(PYTHON_EXECUTABLE "python3")
endif()

# Exetuting bootstrap
FetchContent_Declare(
  SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG        2.5.1 # release-2.5.1
)

# SFML Cmake configurations
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "")
set(SFML_BUILD_AUDIO OFF CACHE BOOL "")
set(SFML_BUILD_DOC OFF CACHE BOOL "")
set(SFML_BUILD_NETWORK OFF CACHE BOOL "")
set(SFML_GENERATE_PDB OFF CACHE BOOL "")
set(BUILD_SHARED_LIBS OFF CACHE BOOL "")
FetchContent_MakeAvailable(SFML)


# Adding SFML CmakeLists to this one
#add_subdirectory(submodules/src/SFML)

include_directories(.)
include_directories(src/)

#set_property(TARGET SFML          PROPERTY FOLDER "ThirdPartyLibraries")

file(GLOB_RECURSE SRC_FILES LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.c??)
file(GLOB_RECURSE HEADER_FILES LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.h)

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES})

target_link_libraries(${PROJECT_NAME} sfml-graphics)

SETUP_GROUPS("${SRC_FILES}")
SETUP_GROUPS("${HEADER_FILES}")

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME_DEBUG ${PROJECT_NAME}_Debug)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME_RELEASE ${PROJECT_NAME}_Release)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME_RELWITHDEBINFO ${PROJECT_NAME}_ReleaseDebInfo)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDART 20)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

if(MSVC)
	add_definitions(-D_CONSOLE)
	set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY  "${CMAKE_SOURCE_DIR}")
endif()

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})