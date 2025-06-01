#include "GManager.hpp"
#include <fstream>

    // Private Functions
GLuint GManager::compileShader(GLenum type, const char *source) {
    GLuint id = glCreateShader(type) ;
    glShaderSource(id, 1, &source, NULL) ;
    glCompileShader(id) ;
    
    int success ;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success) ;
    if (!success) {
        int length ;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length) ;
        
        char *msg = new char[length] ;
        glGetShaderInfoLog(id, length, &length, msg) ;
        printf("Failed To Compile Shader!: %s\n", msg) ;
        delete[] msg ;
        
        glDeleteShader(id) ;
        id = 0 ;
    }
    
    return id ;
}

    // Functions
GLuint GManager::loadShader(const char *vertex, const char *fragment)  {
    GLuint program = glCreateProgram() ;
    
    GLuint vs = compileShader(GL_VERTEX_SHADER, vertex) ;
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fragment) ;
    
    glAttachShader(program, vs) ;
    glAttachShader(program, fs) ;
    glLinkProgram(program) ;
    
    int success ;
    glGetProgramiv(program, GL_LINK_STATUS, &success) ;
    if (!success) {
        int length ;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length) ;
        
        char *msg = new char[length] ;
        glGetProgramInfoLog(program, length, &length, msg) ;
        printf("Failed To Link Shaders To Program!: %s\n", msg) ;
        delete[] msg ;
        
        glDeleteProgram(program) ;
        program = 0 ;
    }
    
    glDeleteShader(vs) ;
    glDeleteShader(fs) ;
    
    return program ;
}

std::string GManager::readShader(const char *filePath) {
    std::ifstream file(filePath) ;
    if (file.is_open()) {
        std::string src{}, temp{} ;
        while (std::getline(file, temp)) {
            src += temp + '\n' ;
        }
        file.close() ;
        return src ;
        
    } else {
        printf("Failed To Open [%s] Check The filePath or Name\n", filePath) ;
        return "" ;
    }
}