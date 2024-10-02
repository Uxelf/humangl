#ifndef ANIMATION_CONTROLLER_HPP
#define ANIMATION_CONTROLLER_HPP

#include <Object.hpp>
#include <vector>
#include <map>

class Animation_controller
{
private:
    std::vector<Object*> _animated_objects;
    std::map<Object*, std::map<float,vec3>> _objects_keyframes;
public:
    Animation_controller();
    ~Animation_controller();

    const std::map<Object*, std::map<float,vec3>> getObjectsKeyframes() const {return _objects_keyframes;}
    void registerObject(Object* object);
    void addKeyframe(Object* object, const float time, const vec3& rotation);
    void showKeys(Object* object);

    void animate(float time);
};


#endif