project(database)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

include_directories(${CMAKE_SOURCE_DIR}/src/3rd/muduo)

include_directories(${CMAKE_SOURCE_DIR}/src/3rd/yaml-cpp/include)

# install mysql by yourself (apt install libmysql++-dev)
include_directories(/usr/include/mysql)

aux_source_directory(. database_src)

set(CXX_FLAGS
 -g
)

add_executable(${PROJECT_NAME} ${database_src})

target_link_libraries(${PROJECT_NAME} yaml-cpp)
target_link_libraries(${PROJECT_NAME} muduo_net)
target_link_libraries(${PROJECT_NAME} muduo_base)
target_link_libraries(${PROJECT_NAME} pthread rt mysqlclient)