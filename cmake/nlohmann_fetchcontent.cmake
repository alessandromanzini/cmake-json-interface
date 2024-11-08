include(FetchContent)

set(JSON_MultipleHeaders OFF CACHE BOOL "" FORCE) #Toggle between multi/single header

#Recommended Way - Fetch packaged release
message(STATUS "${LOG_IDENTITY}using fetch_url")
FetchContent_Declare(nlohmann_json 
	URL "https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz")
FetchContent_MakeAvailable(nlohmann_json)

message(STATUS "${LOG_IDENTITY}using link_libraries on ${PROJECT_NAME}")
target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json::nlohmann_json)