project(LoginGate)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

include_directories(${CMAKE_SOURCE_DIR}/src/3rd/muduo)

aux_source_directory(. LoginGate_src)

add_executable(${PROJECT_NAME} ${LoginGate_src})

target_link_libraries(${PROJECT_NAME} muduo_base)
target_link_libraries(${PROJECT_NAME} muduo_net)
target_link_libraries(${PROJECT_NAME} pthread rt)