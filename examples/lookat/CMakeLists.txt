project(lookat)
add_executable(${PROJECT_NAME} camera.cpp main.cpp window.cpp model.cpp)
enable_abcg(${PROJECT_NAME})
