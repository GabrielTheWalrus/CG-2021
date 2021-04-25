project(viewer5)
add_executable(${PROJECT_NAME} main.cpp model.cpp openglwindow.cpp
                               trackball.cpp bola.cpp ground.cpp camera.cpp stadium.cpp)
enable_abcg(${PROJECT_NAME})
