#include <Object.hpp>

Object::Object(): _material(NULL), _mesh(NULL), _visible(true), _parent(NULL), _name("Default Name")
{
    _scale = vec3(1, 1, 1);
    _global_transform = mat4(1);
    _local_transform = mat4(1);
}

Object::Object(Material* material, Mesh* mesh): _material(material), _mesh(mesh), _visible(true), _parent(NULL), _name("Default Name")
{
    _scale = vec3(1, 1, 1);
    _global_transform = mat4(1);
    _local_transform = mat4(1);
}

Object::~Object()
{
}

void Object::render(){
    if(_update_matrix){
        updateMatrix();
    }
    if (_visible && _mesh != NULL && _material != NULL){
        _material->useShader();

        _material->getShader().setMat4("model", _global_transform);
        _material->setGenericShadersUniforms();
        _mesh->render();
    }
}

void Object::updateMatrix(){
    if (_parent){
        _global_transform = _parent->getGlobalTransform() * _local_transform;
    }
    else
        _global_transform = _local_transform;
    _update_matrix = false;

    for (unsigned int i = 0; i < _childs.size(); i++)
        _childs[i]->markUpdateMatrix();
}

const vec3 Object::getGlobalPosition() const{
    vec3 position;
    position.x = _global_transform[3][0];
    position.y = _global_transform[3][1];
    position.z = _global_transform[3][2];
    return position;
}

void Object::setPosition(const vec3& new_position){
    _position = new_position;
    _local_transform.translate(_position);

    updateMatrix();
}

void Object::setRotation(const vec3& new_rotation){
    _rotation = new_rotation;

    _local_transform = mat4(1);
    _local_transform.scale(_scale);
    if (_rotation.y)
        _local_transform.rotate(_rotation.y, vec3(0, 1, 0));
    if (_rotation.x)
        _local_transform.rotate(_rotation.x, vec3(1, 0, 0));
    if (_rotation.z)
        _local_transform.rotate(_rotation.z, vec3(0, 0, 1));
    _local_transform.translate(_position);

    updateMatrix();
}

void Object::setScale(const vec3& new_scale){
    _local_transform.scale(1.0f / _scale.x, 1.0f / _scale.y, 1.0f / _scale.z);
    _scale = new_scale;
    _local_transform.scale(_scale);
    
    updateMatrix();
}

void Object::setParent(Object* parent){
    
    if (_parent == parent)
        return;

    if (_parent)
        _parent->removeChild(this);

    _parent = parent;   
    if (parent) 
        parent->addChild(this);
    updateMatrix();
}
void Object::addChild(Object* child){
    _childs.push_back(child);
}
void Object::removeChild(Object* child){
    std::vector<Object*>::iterator it;
    it = std::remove(_childs.begin(), _childs.end(), child);

    if (it != _childs.end())
        _childs.erase(it);
}

void Object::move(const vec3& movement){
    _position = _position + movement;
    _local_transform.translate(_position);
    
    updateMatrix();
}

void Object::rotate(const vec3& rotation){
    _local_transform.translate(0, 0, 0);
    if (rotation.y)
        _local_transform.rotate(rotation.y, vec3(0, 1, 0));
    if (rotation.x)
        _local_transform.rotate(rotation.x, vec3(1, 0, 0));
    if (rotation.z)
        _local_transform.rotate(rotation.z, vec3(0, 0, 1));
    _local_transform.translate(_position);
    
    updateMatrix();
}

void Object::scale(const vec3& scale_amount){
    _scale.x *= scale_amount.x;
    _scale.y *= scale_amount.y;
    _scale.z *= scale_amount.z;
    _local_transform.scale(scale_amount);
    
    updateMatrix();
}
