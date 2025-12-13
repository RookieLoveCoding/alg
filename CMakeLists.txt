cmake_minimum_required(VERSION 3.10)
project(MyApp)

add_subdirectory(infra)
add_executable(myapp main.c)
target_link_libraries(myapp infra)