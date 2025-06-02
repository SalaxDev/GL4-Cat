CMAKE_MINIMUM_REQUIRED(VERSION 3.30)
project(LIGHT_TEXTURE LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")


if (MINGW)
    set(SOIL2_STATIC_LIB "${CMAKE_SOURCE_DIR}/lib/SOIL2/lib/libsoil2.a")
    find_package(glfw3 CONFIG REQUIRED PATHS "./lib/glfw")
    find_package(soil2 CONFIG REQUIRED PATHS "./lib/SOIL2")
elseif(MSVC)
    set(SOIL2_STATIC_LIB soil2)
    find_package(glfw3 CONFIG REQUIRED)
    find_package(soil2 CONFIG REQUIRED)
endif()

include_directories(
    "lib/glad-4.4/include"
    "lib/glm"
    
    "include"
    "include/tools"
    "include/utils"
    
    "lib/GLFW/include"
    "lib/soil2/include"
)

add_executable(GL-Cat
    src/main.cpp
    src/tools/sh_size.cpp
    src/utils/GManager.cpp
    
    lib/glad-4.4/src/glad.c
)

target_link_libraries(GL-Cat PRIVATE
    ${SOIL2_STATIC_LIB}
    glfw
    opengl32
)

add_custom_command(TARGET GL-Cat POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/res
    $<TARGET_FILE_DIR:GL-Cat>/res
    COMMENT "Copying Assets To Build Directory"
)