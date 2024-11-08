# Library project
project(CMakeLibrary)
set(LOG_IDENTITY "${PROJECT_NAME}:> ")

# Create library target
add_library(${PROJECT_NAME}
	include/functions.h
	src/functions.cpp   )

# The 'include' folder has the headers that will be shared to the external project.
# The 'src' folder should also be included in case we have header for internal use.
target_include_directories(${PROJECT_NAME}
	PUBLIC ./include
	PRIVATE ./src)

# Set JSON library
# We only load the library that we are going to use. This grants us a faster build time and smaller binaries.
# If we want to use all libraries, we can define them all.
if(USE_JSONCPP_JSON)
	target_compile_definitions(${PROJECT_NAME} PUBLIC USE_JSONCPP_JSON)
	message(STATUS "${LOG_IDENTITY}Using JsonCpp library.")

	#FetchContent (cmake/rapidjson_fetchcontent.cmake)
	include(jsoncpp_fetchcontent)
endif()
if(USE_SIMD_JSON)
	target_compile_definitions(${PROJECT_NAME} PUBLIC USE_SIMD_JSON)
	message(STATUS "${LOG_IDENTITY}Using SimdJSON library.")

	#FetchContent (cmake/rapidjson_fetchcontent.cmake)
	include(simd_fetchcontent)
endif()
if(USE_NLOHMANN_JSON)
	target_compile_definitions(${PROJECT_NAME} PUBLIC USE_NLOHMANN_JSON)
	message(STATUS "${LOG_IDENTITY}Using NlohmannJSON library.")

	# FetchContent (cmake/nlohmann_fetchcontent.cmake)
	include(nlohmann_fetchcontent)
endif()
