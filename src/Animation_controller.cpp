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

static std::string prepareFileName(const std::string& file_name) {

    // Check if the file_name ends with ".anim"
    std::string extension = ".anim";
    if (file_name.size() < extension.size() || file_name.rfind(extension) != file_name.size() - extension.size()) {
        // If the file doesn't end with ".anim", append the extension
        return animations_folder + "/" + file_name + extension;
    }

    // If it already has ".anim", just return the full path
    return animations_folder + "/" + file_name;
}

void Animation_controller::saveAnimation(const std::string& file_name){
    if (file_name.size() == 0){
        std::cerr << "File name is empty" << std::endl;
        return;
    }
    if (!std::filesystem::exists(animations_folder)) {
        std::filesystem::create_directory(animations_folder);
    }

    std::string file_path = prepareFileName(file_name);
    std::ofstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Failed to open or create file: " << file_path << std::endl;
        return;
    }

    std::ostringstream data;

    for (auto& [object, keyframes] : _objects_keyframes){
        for (auto& [time, rotation] : keyframes){
            data << object->getName() << " " << time << " " << rotation.x << " " << rotation.y << " " << rotation.z << std::endl;
        }
    }

    file << data.str();
    file.close();
    std::cout << "File saved successfully to: " << file_path << std::endl;
}

void Animation_controller::loadAnimation(const std::string& file_name){
    if (file_name.size() == 0){
        std::cerr << "File name is empty" << std::endl;
        return;
    }
    if (!std::filesystem::exists(animations_folder)){
        std::cerr << "There is no animations folder" << std::endl;
        return;
    }

    std::string file_path = prepareFileName(file_name);
    std::ifstream file(file_path);
    if(!file.is_open()){
        std::cerr << "Failed to open file: " << file_path << std::endl;
        return;
    }

    _objects_keyframes.clear();
    std::string line;
    while (std::getline(file, line)){
        std::istringstream line_stream(line);

        vec3 rotation;
        float time;
        std::string object_name;

        line_stream >> object_name >> time >> rotation.x >> rotation.y >> rotation.z;
        for (unsigned int i = 0; i < _animated_objects.size(); i++){
            if (_animated_objects[i]->getName() == object_name){
                _objects_keyframes[_animated_objects[i]][time] = rotation;
                break;
            }
            if (i == _animated_objects.size()){
                std::cerr << "Unrecognized object: " << object_name << std::endl;
            }
        }
    }

    file.close();
    std::cout << "File loaded successfully" << std::endl;
}
