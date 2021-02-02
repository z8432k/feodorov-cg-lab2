set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE  ON)


# include_directories(include)

add_executable(example1 example1.cc)
target_link_libraries(example1 PUBLIC ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

