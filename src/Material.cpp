#include <Material.hpp>

Material::Material(const Shader& shader, const vec3& color):
    _shader(shader), _color(color) {
}

Material::Material(const Material& other): 
    _shader(other._shader), _color(other._color){
}

Material::~Material(){
}

void Material::setGenericShadersUniforms(){
    _shader.setVec3("objectColor", _color);
}