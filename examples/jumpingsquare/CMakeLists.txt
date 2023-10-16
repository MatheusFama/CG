cmake_minimum_required(VERSION 3.11)
project(jumpingsquare)
add_executable(${PROJECT_NAME} main.cpp window.cpp square.cpp obstacles.cpp ground.cpp)
enable_abcg(${PROJECT_NAME})
