cmake_minimum_required(VERSION 3.28)
project(OpenGL-Physics VERSION 1.0.0 LANGUAGES CXX C)

# C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Config
set(BUILD_SHARED_LIBS OFF)
set(DEPS_DIR "${CMAKE_SOURCE_DIR}/dependencies")

# GLFW Config
set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "GLFW lib only" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "GLFW lib only" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "GLFW lib only" FORCE)

# GLM Config
set(GLM_BUILD_INSTALL OFF)
set(GLM_BUILD_TESTS OFF)
set(GLM_BUILD_LIBRARY OFF)

# ASSIMP Config
set(ASSIMP_INSTALL OFF)
set(ASSIMP_WARNINGS_AS_ERRORS OFF)
set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT OFF)
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
set(ASSIMP_BUILD_OBJ_IMPORTER ON)

# Add subdirectories
add_subdirectory(${DEPS_DIR}/glfw)
add_subdirectory(${DEPS_DIR}/glm)
add_subdirectory(${DEPS_DIR}/assimp)

# Glob for source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/*.c
)

# Additional compile flags for GCC and Clang
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Werror -Wattributes)
endif()

# Additional compile flags for MSVC
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/W4 /WX)
endif()

# Create exe
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${DEPS_DIR}/glfw/include
    ${DEPS_DIR}/glm/glm
    ${DEPS_DIR}/assimp/include
    ${DEPS_DIR}

    ${CMAKE_SOURCE_DIR}/src/controller
    ${CMAKE_SOURCE_DIR}/src/systems
    ${CMAKE_SOURCE_DIR}/src/components
    ${CMAKE_SOURCE_DIR}/src/entity
    ${CMAKE_SOURCE_DIR}/src/factories
)

# Link libs
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    glfw
    glm
    assimp
    OpenGL::GL
)
