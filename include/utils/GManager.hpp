#ifndef GMANAGER_HPP
#define GMANAGER_HPP

#include <glad.h>
#include <GLFW/glfw3.h>

#include <string>

class GManager {
    private :
        // Private Functions
    GLuint compileShader(GLenum type, const char *source) ;
public :
    GManager() = default;
    
        // Functions
    GLuint loadShader(const char *vertex, const char *fragment) ;
    std::string readShader(const char *filePath) ;
    
};

#endif //GMANAGER_HPP