include(FetchContent)

#Recommended Way - Fetch packaged release
message(STATUS "${LOG_IDENTITY}using fetch_url")
FetchContent_Declare(simdjson
	URL https://github.com/simdjson/simdjson/archive/refs/tags/v3.10.1.tar.gz)
FetchContent_MakeAvailable(simdjson)

message(STATUS "${LOG_IDENTITY}using link_libraries on ${PROJECT_NAME}")
target_link_libraries(${PROJECT_NAME} PUBLIC simdjson)