#include "sh_size.hpp"
#include <cstdio>

sh::Size::Size(int w, int h, const char *name) 
    : w(w), h(h), name(name) {}

sh::IMG::IMG(int w, int h) 
    : w(w), h(h) {}
    
sh::IMG::~IMG() {
    if (file) SOIL_free_image_data(file) ;
}

void sh::IMG::loadImage(const char *path) {
    file = SOIL_load_image(path, &w, &h, NULL, SOIL_LOAD_RGBA) ;
    if (!file) printf("Failed To Load Image!: %s", path) ;
}

void sh::IMG::release() {
    if (file) {
        SOIL_free_image_data(file) ;
        file = nullptr ;
    }
}

void sh::IMG::setDefaultSize() {
    w = 0 ;
    h = 0 ;
}