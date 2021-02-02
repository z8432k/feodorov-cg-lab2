set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE  ON)

find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(GLUT REQUIRED)

include_directories(include)

add_library(orig OBJECT orig.cc)
target_link_libraries(orig PUBLIC ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

add_library(cube OBJECT cube.cc)
target_link_libraries(cube PUBLIC ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})



add_executable(orig-cw orig-cw.cc)
target_link_libraries(orig-cw orig)

add_executable(cube-cw cube-cw.cc)
target_link_libraries(cube-cw cube)

add_executable(mouse mouse.cc)
target_link_libraries(mouse PUBLIC ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

add_executable(light light.cc)
target_link_libraries(light PUBLIC ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

