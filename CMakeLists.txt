# CMakeList.txt : CMake project for PokedexJson, 2GD10 Manzini Alessandro
# Project specific logic here.
#
cmake_minimum_required (VERSION 3.24.1)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Ensure C++17 is strictly required
message(STATUS "C++17 support has been enabled by default.")

# Set the project name
project(PokedexJson)

# Set JSON library to use
# Uncomment if you want to FORCE the cache through this CMakeLists.txt
# set(JSON_LIBRARY "simd" CACHE STRING "FORCE JSON library to use." FORCE)

# We set the flags to use target the desired library.
# The rest of the code will try to fetch and use it.
# Confirmation is done in the library/CMakeLists.txt file.
if(JSON_LIBRARY STREQUAL "jsoncpp")
	set(USE_JSONCPP_JSON ON)
elseif(JSON_LIBRARY STREQUAL "simd")
	set(USE_SIMD_JSON ON)
elseif(JSON_LIBRARY STREQUAL "nlohmann")
	set(USE_NLOHMANN_JSON ON)
else()
	message(FATAL_ERROR "JSON_LIBRARY must be set to either 'jsoncpp', 'simd' or 'nlohmann'. '${JSON_LIBRARY}' is currently being selected.")
endif()

# Append cmake module path
# Making sure cmake finds our custom modules (.cmake)
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Include sub-directories
add_subdirectory(library)
add_subdirectory(program)
