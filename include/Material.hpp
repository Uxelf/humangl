#pragma once
#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <Shader.hpp>
#include <Vector3.hpp>
#include <string>

class Material
{
private:
    Shader  _shader;
    vec3    _color;

public:
    Material(const Shader& shader, const vec3& color);
    Material(const Material& other);
    ~Material();

    void setColor(const vec3& color) {_color = color;}

    const Shader& getShader() const {return _shader;}
    const vec3    getColor() const {return _color;}

    void useShader() {_shader.use();}
    void setGenericShadersUniforms();
};

#endif