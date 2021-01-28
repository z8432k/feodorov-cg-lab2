set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE  ON)

find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(GLUT REQUIRED)

include_directories(include)

add_executable(cgcw cgcw.cc)
target_link_libraries(cgcw ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
