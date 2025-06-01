#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

#include <glad.h>
#include <GLFW/glfw3.h>

#include <cstddef>
#include <cstdio>
#include <thread>
#include <chrono>

#include "GManager.hpp"
#include "sh_size.hpp"


void call_err() ;
void FBRcallback(GLFWwindow *wnd, int fbw, int fbh) ;
void update_input(GLFWwindow *wnd, glm::vec3 &position, glm::vec3 &rotation, glm::vec3 &scale) ;


sh::Size wndSize(800, 600, "Camera") ;
constexpr float fps = 1000.f / 90.f ;

// Vertices
sh::Vertex vertices[] {
    glm::vec3(-0.5f, 0.5f, 0.f), // Top Left
    glm::vec3(1.f, 0.f, 0.f),
    glm::vec2(0.f, 1.f),
    glm::vec3(0.f, 0.f, -1.f),
    
    glm::vec3(-0.5f, -0.5f, 0.f), // Bottom Left
    glm::vec3(0.f, 1.f, 0.f),
    glm::vec2(0.f, 0.f),
    glm::vec3(0.f, 0.f, -1.f),
    
    glm::vec3(0.5f, -0.5f, 0.f), // Bottom right
    glm::vec3(0.f, 0.f, 1.f),
    glm::vec2(1.f, 0.f),
    glm::vec3(0.f, 0.f, -1.f),
    
    glm::vec3(0.5f, 0.5f, 0.f), // Top Right
    glm::vec3(0.f, 1.f, 0.f),
    glm::vec2(1.f, 1.f),
    glm::vec3(0.f, 0.f, -1.f)
};

const GLuint numVertices = sizeof(vertices) / sizeof(sh::Vertex) ;

// Indices
GLuint indices[] {
    0, 1, 2,
    0, 2, 3
};

const GLuint numIndices = sizeof(indices) / sizeof(GLuint) ;

int main(int argc, const char **argv) {
    if (!glfwInit()) {
        call_err() ;
        return 1 ;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4) ;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4) ;
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE) ;
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE) ;
    
    GLFWwindow *wnd = glfwCreateWindow(wndSize.w, wndSize.h, wndSize.name, NULL, NULL) ;
    if (!wnd) {
        call_err() ;
        glfwTerminate() ;
        return 2 ;
    }
    
    glfwMakeContextCurrent(wnd) ;
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        call_err() ;
        glfwDestroyWindow(wnd) ;
        glfwTerminate() ;
        return 3 ;
    }
    
    int fbw, fbh ;
    
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION)) ;
    glfwGetFramebufferSize(wnd, &fbw, &fbh) ;
    glfwSetFramebufferSizeCallback(wnd, FBRcallback) ;
    
    // GL Settings
    glEnable(GL_DEPTH_TEST) ;
    glEnable(GL_CULL_FACE) ;
    
    glCullFace(GL_BACK) ;
    glFrontFace(GL_CCW) ;
    
    glEnable(GL_BLEND) ;
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL) ;
    
    // Vertex Objects
        // Vertex Array Object
    GLuint vao ;
    glGenVertexArrays(1, &vao) ;
    glBindVertexArray(vao) ;
    
        // Vertex Buffer Object
    GLuint vbo ;
    glGenBuffers(1, &vbo) ;
    glBindBuffer(GL_ARRAY_BUFFER, vbo) ;
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW) ;
    
    glEnableVertexAttribArray(0) ;
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
        sizeof(sh::Vertex), (GLvoid *) offsetof(sh::Vertex, position) 
    );
    
    glEnableVertexAttribArray(1) ;
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
        sizeof(sh::Vertex), (GLvoid *) offsetof(sh::Vertex, color)
    );
    
    glEnableVertexAttribArray(2) ;
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
        sizeof(sh::Vertex), (GLvoid *) offsetof(sh::Vertex, texcoord)
    );
    
    glEnableVertexAttribArray(3) ;
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE,
        sizeof(sh::Vertex), (GLvoid *) offsetof(sh::Vertex, normal)
    );
    
        // Vertex Index Object
    GLuint vio ;
    glGenBuffers(1, &vio) ;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vio) ;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW) ;
    
    // Shader Section
    GManager gm ;
    
    std::string vs = gm.readShader("./res/shaders/vertex_core.glsl") ;
    std::string fs = gm.readShader("./res/shaders/fragment_core.glsl") ;
    
    GLuint program = gm.loadShader(vs.c_str(), fs.c_str()) ;
    vs = "" ;
    fs = "" ;
        // Image Loading
    sh::IMG img(0, 0) ;
    img.loadImage("./res/images/pusheen.png") ; // pusheen img
    
    GLuint texture0 ;
    glGenTextures(1, &texture0) ;
    glBindTexture(GL_TEXTURE_2D, texture0) ;
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT) ;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT) ;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) ;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST) ;
    
    if (img.file) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
            img.w, img.h, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, img.file
        );
        glGenerateMipmap(GL_TEXTURE_2D) ;
    }
    
    glBindTexture(GL_TEXTURE_2D, 0) ;
    
    img.release() ;
    img.setDefaultSize() ;
    
    img.loadImage("./res/images/container.png") ;
    GLuint texture1 ;
    glGenTextures(1, &texture1) ;
    glBindTexture(GL_TEXTURE_2D, texture1) ;
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT) ;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT) ;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) ;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST) ;
    
    if (img.file) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
            img.w, img.h, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, img.file
        );
        
        glGenerateMipmap(GL_TEXTURE_2D) ;
    }
    
    
    glBindVertexArray(0) ;
    glBindBuffer(GL_ARRAY_BUFFER, 0) ;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) ;
    
    img.release() ;
    img.setDefaultSize() ;
    
    
    glm::mat4 modelMatrix(1.f) ;
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.f, 0.f ,0.f)) ;
    
    glm::vec3 camPosition(0.f, 0.f, 1.f) ;
    glm::vec3 worldUp(0.f, 1.f, 0.f) ;
    glm::vec3 camFront(0.f, 0.f, -1.f) ;
    glm::mat4 viewMatrix(1.f) ;
    
    viewMatrix = glm::lookAt(camPosition, camPosition + camFront, worldUp) ;
    
    
    float fov = 90.f ;
    float nearPlane = 0.1f ;
    float farPlane = 100.f ;
    glm::mat4 projectionMatrix(1.f) ;
    projectionMatrix = glm::perspective(
        glm::radians(fov),
        static_cast<float>(fbw) / fbh,
        nearPlane,
        farPlane
    );
    
    // LIGHTS
    glm::vec3 lightPos0(0.f, 0.f, 2.f) ;
    
    
    
    glm::vec3 position(0.f) ;
    glm::vec3 rotation(0.f, 2.f, 0.f) ;
    glm::vec3 scale(1.f) ;
    
    
    // Loop
    glUseProgram(program) ;
    
    int texloc0 = glGetUniformLocation(program, "texture0") ;
    int texloc1 = glGetUniformLocation(program, "texture1") ;
    int modelLoc = glGetUniformLocation(program, "modelMatrix") ;
    int viewLoc = glGetUniformLocation(program, "viewMatrix") ;
    int projLoc = glGetUniformLocation(program, "projectionMatrix") ;
    int lightloc0 = glGetUniformLocation(program, "lightPos0") ;
    int cameraLoc = glGetUniformLocation(program, "cameraPos") ;
    
    modelMatrix = glm::translate(modelMatrix, position) ;
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f ,0.f)) ;
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f)) ;
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f)) ;
    modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f)) ;
    
    
    glUniform3fv(cameraLoc, 1, glm::value_ptr(camPosition)) ;
    while (!glfwWindowShouldClose(wnd)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT) ;
        
        
        glUniform1i(texloc0, 0) ;
        glUniform1i(texloc1, 1)  ;
        
        glfwGetFramebufferSize(wnd, &fbw, &fbh) ;
        projectionMatrix = glm::mat4(1.f) ;
        projectionMatrix = glm::perspective(
            fov,
            static_cast<float>(fbw) / fbh,
            nearPlane,
            farPlane
        );
        
        // Move Rotate Scale Texture
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix)) ;
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix)) ;
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix)) ;
        glUniform3fv(lightloc0, 1, glm::value_ptr(lightPos0)) ;
        /* 
        position.z -= 0.01f ;
        rotation.y += 2.f ;
         */
        
        modelMatrix = glm::mat4(1.f) ;
        modelMatrix = glm::translate(modelMatrix, position) ;
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f ,0.f)) ;
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f)) ;
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f)) ;
        modelMatrix = glm::scale(modelMatrix, glm::vec3(scale)) ;
        
        glActiveTexture(GL_TEXTURE0) ;
        glBindTexture(GL_TEXTURE_2D, texture0) ;
        
        glActiveTexture(GL_TEXTURE1) ;
        glBindTexture(GL_TEXTURE_2D, texture1) ;
        
        glBindVertexArray(vao) ;
        glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, NULL) ;
        
        update_input(wnd, position, rotation, scale) ;
        glfwSwapBuffers(wnd) ;
        glfwPollEvents() ;
        
        std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(fps)) ;
    }
    
    glDeleteProgram(program) ;
    glfwDestroyWindow(wnd) ;
    glfwTerminate() ;
    return 0 ;
}

void call_err() {
    const char *msg ;
    glfwGetError(&msg) ;
    printf("GLFW Error: %s", msg) ;
}

void FBRcallback(GLFWwindow *wnd, int fbw, int fbh) {
    glViewport(0, 0, fbw, fbh) ;
}

void update_input(GLFWwindow *wnd, glm::vec3 &position, glm::vec3 &rotation, glm::vec3 &scale) {
    if (glfwGetKey(wnd, GLFW_KEY_W) == GLFW_PRESS) {
        position.y += 0.01f ;
    } else if (glfwGetKey(wnd, GLFW_KEY_S) == GLFW_PRESS) {
        position.y -= 0.01f ;
    }
    
    if (glfwGetKey(wnd, GLFW_KEY_A) == GLFW_PRESS) {
        position.x -= 0.01f ;
    } else if (glfwGetKey(wnd, GLFW_KEY_D) == GLFW_PRESS) {
        position.x += 0.01f ;
    }
    
    if (glfwGetKey(wnd, GLFW_KEY_Q) == GLFW_PRESS) {
        rotation.y -= 1.1f ;
    } else if (glfwGetKey(wnd, GLFW_KEY_E) == GLFW_PRESS) {
        rotation.y += 1.1f ;
    }
    
    if (glfwGetKey(wnd, GLFW_KEY_Z) == GLFW_PRESS) {
        scale -= 0.05f ;
    } else if (glfwGetKey(wnd, GLFW_KEY_X) == GLFW_PRESS) {
        scale += 0.05f ;
    }
}