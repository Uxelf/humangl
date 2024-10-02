#include <Animation_controller.hpp>

Animation_controller::Animation_controller()
{
}

Animation_controller::~Animation_controller()
{
}

void Animation_controller::registerObject(Object* object){
    auto it = std::find(_animated_objects.begin(), _animated_objects.end(), object);
    if (it == _animated_objects.end())
        _animated_objects.push_back(object);
}

void Animation_controller::addKeyframe(Object* object, const float time, const vec3& rotation){
    registerObject(object);

    std::map<float,vec3> keyframes = _objects_keyframes[object];
    keyframes[time] = rotation;
    _objects_keyframes[object] = keyframes;
}

void Animation_controller::animate(float time){
    for (auto& [object, keyframes] : _objects_keyframes){

        auto lower = keyframes.lower_bound(time);
        auto upper = keyframes.upper_bound(time);

        if (lower->first != time && lower != keyframes.begin()){
            lower--;
        }

        vec3 average;
        if (lower == upper || upper == keyframes.end()){
            average = lower->second;
        }
        else{
            float percentaje = (time - lower->first) / (upper->first - lower->first);
            average.x = lower->second.x * (1.0f - percentaje) + upper->second.x * percentaje;
            average.y = lower->second.y * (1.0f - percentaje) + upper->second.y * percentaje;
            average.z = lower->second.z * (1.0f - percentaje) + upper->second.z * percentaje;
        }
        object->setRotation(average);
    }
}