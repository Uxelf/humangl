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

void Animation_controller::addKeyframe(Object* object, const float time, const vec3& position, const vec3& rotation, const vec3& size){
    registerObject(object);
    _objects_keyframes[object][time].position = position;
    _objects_keyframes[object][time].rotation = rotation;
    _objects_keyframes[object][time].size = size;
}

void Animation_controller::removeKeyframe(Object* object, const float time){
    _objects_keyframes[object].erase(time);
    if (_objects_keyframes[object].size() == 0)
        _objects_keyframes.erase(object);
}

void Animation_controller::animate(float time){
    for (auto& [object, keyframes] : _objects_keyframes){

        auto lower = keyframes.lower_bound(time);
        auto upper = keyframes.upper_bound(time);

        if (lower->first != time && lower != keyframes.begin()){
            lower--;
        }

        vec3 average_position;
        vec3 average_rotation;
        vec3 average_size;

        if (lower == upper || upper == keyframes.end()){
            average_position = lower->second.position;
            average_rotation = lower->second.rotation;
            average_size = lower->second.size;
        }
        else{
            float percentaje = (time - lower->first) / (upper->first - lower->first);
            average_position = lower->second.position * (1.0f - percentaje) + upper->second.position * percentaje;
            average_rotation = lower->second.rotation * (1.0f - percentaje) + upper->second.rotation * percentaje;
            average_size = lower->second.size * (1.0f - percentaje) + upper->second.size * percentaje;
        }
        object->setPosition(average_position);
        object->setRotation(average_rotation);
        object->setScale(average_size);
    }
}

static std::string prepareFileName(const std::string& file_name) {

    // Check if the file_name ends with ".anim"
    std::string extension = ".anim";
    if (file_name.size() < extension.size() || file_name.rfind(extension) != file_name.size() - extension.size()) {
        return animations_folder + "/" + file_name + extension;
    }

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
        for (auto& [time, properties] : keyframes){
            data << object->getName() << " " << time << " " 
            << properties.position.x << " " << properties.position.y << " " << properties.position.z << " "
            << properties.rotation.x << " " << properties.rotation.y << " " << properties.rotation.z << " " 
            << properties.size.x << " " << properties.size.y << " " << properties.size.z << " " 
            << std::endl;
        }
    }

    file << data.str();
    file.close();
    std::cout << "File " << file_path << " saved successfully to: " << file_path << std::endl;
}

static bool CheckLineParams(const std::string& line){
    std::stringstream ss(line);
    std::vector<std::string> params;
    std::string item;

    while (std::getline(ss, item, ' ')){
        params.push_back(item);
    }


    if (params.size() != 11)
        return false;
    
    try{
        for (int i = 1; i < 11; i++){
            std::stof(params[i]);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }

    return true;
    
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

    std::map<Object*, std::map<float,properties>> temp_keyframes;
    std::string line;
    int j = 0;
    while (std::getline(file, line)){
        j++;
        if (!CheckLineParams(line)){
            std::cout << "File " << file_path << " wrong params at line " << j << std::endl;
            file.close();
            return;
        }
        std::istringstream line_stream(line);

        vec3 rotation;
        vec3 position;
        vec3 size;
        float time;
        std::string object_name;

        line_stream >> object_name >> time >> position.x >> position.y >> position.z >> rotation.x >> rotation.y >> rotation.z  >>
        size.x >> size.y >> size.z;
        for (unsigned int i = 0; i < _animated_objects.size(); i++){
            if (_animated_objects[i]->getName() == object_name){
                temp_keyframes[_animated_objects[i]][time].position = position;
                temp_keyframes[_animated_objects[i]][time].rotation = rotation;
                temp_keyframes[_animated_objects[i]][time].size = size;
                break;
            }
            if (i == _animated_objects.size()){
                std::cerr << "Unrecognized object: " << object_name << std::endl;
            }
        }
    }

    _objects_keyframes.clear();
    _objects_keyframes.merge(temp_keyframes);
    file.close();
    std::cout << "File " << file_path << " loaded successfully" << std::endl;
}
