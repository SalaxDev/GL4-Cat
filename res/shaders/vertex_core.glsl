#version 440 core

layout (location = 0) in vec3 position ;
layout (location = 1) in vec3 color ;
layout (location = 2) in vec2 texcoord ;
layout (location = 3) in vec3 normal ;

out vec3 vs_position ;
out vec3 vs_color ;
out vec2 vs_texcoord ;
out vec3 vs_normal ;

uniform mat4 modelMatrix ;
uniform mat4 viewMatrix ;
uniform mat4 projectionMatrix ;

void main() {
    vs_position = vec4(modelMatrix * vec4(position, 1.f)).xyz ;
    vs_color = color ;
    vs_texcoord = vec2(texcoord.x, texcoord.y * -1.f) ;
    
    vs_normal = mat3(modelMatrix) * normal ;
    
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.f) ;
}