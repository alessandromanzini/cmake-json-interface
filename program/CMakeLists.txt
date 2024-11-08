# Program project
project(CMakeProgram)

# Add source to this project's executable.
add_executable(${PROJECT_NAME} 
	src/main.cpp)

# Link library
target_link_libraries(${PROJECT_NAME}
	PRIVATE CMakeLibrary)

# Copy Content (./content >> out/.../content)
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
                ${CMAKE_SOURCE_DIR}/content
                $<TARGET_FILE_DIR:${PROJECT_NAME}>/content)