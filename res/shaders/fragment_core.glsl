#version 440 core

in vec3 vs_position ;
in vec3 vs_color ;
in vec2 vs_texcoord ;
in vec3 vs_normal ;

out vec4 fs_color ;

uniform sampler2D texture0 ;
uniform sampler2D texture1 ;
uniform vec3 lightPos0 ;
uniform vec3 cameraPos ;

void main() {
    //fs_color = texture(texture0, vs_texcoord) * texture(texture0, vs_texcoord) * vec4(vs_color, 1.f) ;
    
    // Ambient Light
    vec3 ambientLight = vec3(0.1f, 0.1f, 0.1f) ;
    
    // Diffuse Light
    vec3 posToLightDirVec = normalize(vs_position - lightPos0) ;
    vec3 diffuseColor = vec3(1.f, 1.f, 1.f) ;
    float diffuse = clamp(dot(posToLightDirVec, vs_normal), 0, 1) ;
    vec3 finalDiffuse = diffuseColor * diffuse ;
    
    // Specular Light
    vec3 lightToPosDirVec = normalize(lightPos0 - vs_position) ;
    vec3 reflectDirVec = normalize(reflect(lightToPosDirVec, normalize(vs_normal))) ;
    vec3 posToViewDirVec = normalize(vs_position - cameraPos) ;
    float specularConstant = pow(max(dot(posToViewDirVec, reflectDirVec), 0), 30) ;
    vec3 finalSpecular = vec3 (1.f, 1.f, 1.f) * specularConstant ;	
    
    
    
    fs_color = texture(texture0, vs_texcoord) * vec4(vs_color, 1.f)
        * (vec4(ambientLight, 1.f) + vec4(finalDiffuse, 1.f) + vec4(finalSpecular, 1.f)) ;
}