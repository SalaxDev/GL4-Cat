CMAKE_MINIMUM_REQUIRED(VERSION 3.30)
project(LIGHT_TEXTURE LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

if(WIN32)
    set(SOIL2_STATIC_LIB "${CMAKE_SOURCE_DIR}/lib/SOIL2/lib/libsoil2.a")
    
    find_package(glfw3 CONFIG REQUIRED PATHS "./lib/glfw")
    find_package(soil2 CONFIG REQUIRED PATHS "./lib/SOIL2")
    find_package(glm CONFIG REQUIRED PATHS "./lib/glm")
    
    include_directories(
    "lib/GLFW/include"
    "lib/soil2/include"
    )
    
else()
    
    find_package(PkgConfig)
    if(PKG_CONFIG_FOUND)
        pkg_check_modules(GLFW REQUIRED glfw3)
        pkg_check_modules(SOIL2 REQUIRED SOIL2)
    endif()
    
    if(NOT GLFW_FOUND)
        find_package(glfw3 REQUIRED)
    endif()
    
    find_package(glfw3 REQUIRED)
    find_package(OpenGL REQUIRED)
endif()

include_directories(
    "lib/glad-4.4/include"
    "lib/glm"
    
    "include"
    "include/tools"
    "include/utils"
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
)

if(WIN32) # Windows
    target_link_libraries(GL-Cat PRIVATE
        opengl32
    )
    
elseif(UNIX AND NOT APPLE) #Linux


    target_link_libraries(GL-Cat
        glfw
        ${OPENGL_LIBRARIES}
        ${SOIL2_LIBRARIES}
        dl
        pthread
        X11
    )
    
elseif(APPLE) #Apple
    find_library(COCOA Cocoa)
    find_library(IOKIT IOKit)
    find_library(COREVIDEO CoreVideo)
    target_link_libraries(GL-Cat PRIVATE
        glfw
        ${GLFW_LIBRARIES}
        ${SOIL2_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${COCOA}
        ${IOKIT}
        ${COREVIDEO}
    )
    
endif()

add_custom_command(TARGET GL-Cat POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/res
    $<TARGET_FILE_DIR:GL-Cat>/res
    COMMENT "Copying Assets To Build Directory"
)