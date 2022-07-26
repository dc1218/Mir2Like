project(chat)

include_directories(${CMAKE_SOURCE_DIR}/src/common)

aux_source_directory(. chat_src)

# add_library(${PROJECT_NAME} SHARED ${chat_src})

add_executable(${PROJECT_NAME} ${chat_src})

# target_link_libraries(${PROJECT_NAME} common)

