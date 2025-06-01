#ifndef SH_SIZE_HPP
#define SH_SIZE_HPP

#include <soil2/SOIL2.h>
#include <glm.hpp>

namespace sh {
    struct Size {
        int w, h ;
        const char *name ;
        Size(int w = 0, int h = 0, const char *name = "") ;
    };
    
    struct Vertex {
        glm::vec3 position ;
        glm::vec3 color ;
        glm::vec2 texcoord ;
        glm::vec3 normal ;
    };
    
    struct IMG {
        int w, h ;
        unsigned char *file = nullptr ;
        IMG(int w = 0, int h = 0) ;
        ~IMG() ;
        
        void loadImage(const char *path) ;
        void release() ;
        void setDefaultSize() ;
    };
}


#endif //SH_SIZE_HPP