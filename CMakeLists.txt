project(graphics_asgn2)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(src SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

include(FindPkgConfig)

pkg_check_modules(GLFW3 REQUIRED glfw3)
include_directories(${GLFW3_INCLUDE_DIRS})
target_link_libraries (${PROJECT_NAME} ${GLFW3_LIBRARIES})

pkg_check_modules(GLEW REQUIRED glew)
include_directories(${GLEW_INCLUDE_DIRS})
target_link_libraries (${PROJECT_NAME} ${GLEW_LIBRARIES})

if (NOT APPLE)
  pkg_check_modules(GL REQUIRED gl)
  include_directories(${GL_INCLUDE_DIRS})
  target_link_libraries (${PROJECT_NAME} ${GL_LIBRARIES})
endif()

if (APPLE)
  target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

# find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} pthread)
target_link_libraries(${PROJECT_NAME} SOIL)

pkg_check_modules(AO REQUIRED ao)
include_directories(${AO_INCLUDE_DIRS})
target_link_libraries (${PROJECT_NAME} ${AO_LIBRARIES})

pkg_check_modules(LIBMPG123 REQUIRED libmpg123)
include_directories(${LIBMPG123_INCLUDE_DIRS})
target_link_libraries (${PROJECT_NAME} ${LIBMPG123_LIBRARIES})

configure_file(src/Sample_GL.vert Sample_GL.vert COPYONLY)
configure_file(src/Sample_GL.frag Sample_GL.frag COPYONLY)

configure_file(src/TextureRender.vert TextureRender.vert COPYONLY)
configure_file(src/TextureRender.frag TextureRender.frag COPYONLY)

configure_file(src/TextVertexShader.vertexshader TextVertexShader.vertexshader COPYONLY)
configure_file(src/TextVertexShader.fragmentshader TextVertexShader.fragmentshader COPYONLY)