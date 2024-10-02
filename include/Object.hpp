#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <Material.hpp>
#include <Matrix4x4.hpp>
#include <Vector3.hpp>
#include <Mesh.hpp>

#include <vector>
#include <string>
#include <algorithm>

class Object
{
private:
    Material*   _material;
    Mesh*       _mesh;
    vec3        _position;
    vec3        _rotation;
    vec3        _scale;
    mat4        _local_transform;
    mat4        _global_transform;
    bool        _update_matrix;

    Object*                 _parent;
    std::vector<Object*>    _childs;

    std::string _name;
  
    void updateMatrix();
    void addChild(Object* child);
    void removeChild(Object* child);
public:
    Object();
    Object(Material* material, Mesh* mesh);
    ~Object();

    void render();

    const mat4& getGlobalTransform() const {return _global_transform;}
    const mat4& getLocalTransform() const {return _local_transform;}
    const vec3  getPosition() const {return _position;}
    const vec3  getRotation() const {return _rotation;}
    const vec3  getScale() const {return _scale;}
    const std::string getName() const {return _name;}

    void setColor(const vec3& new_color) {if (_material != NULL) _material->setColor(new_color);}
    void setPosition(const vec3& new_position);
    void setRotation(const vec3& new_rotation);
    void setScale(const vec3& new_scale);
    void setParent(Object* parent);
    void setName(const std::string& name) {_name = name;}

    void move(const vec3& movement);
    void rotate(const vec3& rotation);
    void scale(const vec3& scale_amount);
    void markUpdateMatrix() {_update_matrix = true;}
};

#endif