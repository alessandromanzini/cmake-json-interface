include(FetchContent)

#Recommended Way - Fetch packaged release
message(STATUS "${LOG_IDENTITY}using fetch_url")
FetchContent_Declare(jsoncpp
	URL https://github.com/open-source-parsers/jsoncpp/archive/refs/tags/1.9.6.tar.gz)
FetchContent_MakeAvailable(jsoncpp)

message(STATUS "${LOG_IDENTITY}using link_libraries on ${PROJECT_NAME}")
target_link_libraries(${PROJECT_NAME} PUBLIC jsoncpp_static)
