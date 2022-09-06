project(chat)

include_directories(${CMAKE_SOURCE_DIR}/src/3rd/muduo)

aux_source_directory(. chat_src)

add_executable(${PROJECT_NAME} ${chat_src})

target_link_libraries(${PROJECT_NAME} muduo_base)
target_link_libraries(${PROJECT_NAME} muduo_net)
target_link_libraries(${PROJECT_NAME} pthread rt)

