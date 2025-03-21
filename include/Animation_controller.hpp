#ifndef ANIMATION_CONTROLLER_HPP
#define ANIMATION_CONTROLLER_HPP

#include <Object.hpp>
#include <vector>
#include <map>
#include <filesystem>
#include <ostream>

const std::string animations_folder = "animations";

struct properties{
    vec3 position;
    vec3 rotation;
    vec3 size;
};

struct time_controllers{
    float time;
    float time_scale;
    float time_limit;
    float delta_time;
    bool play;
};

class Animation_controller
{
private:
    std::vector<Object*> _animated_objects;
    std::map<Object*, std::map<float,properties>> _objects_keyframes;
public:
    Animation_controller();
    ~Animation_controller();

    std::map<Object*, std::map<float,properties>> getObjectsKeyframes() const {return _objects_keyframes;}
    void registerObject(Object* object);
    void addKeyframe(Object* object, const float time, const vec3& position, const vec3& rotation, const vec3& size);
    void removeKeyframe(Object* object, const float time);

    void animate(float time);

    void saveAnimation(const std::string& file_name);
    void loadAnimation(const std::string& file_name);
};


#endif