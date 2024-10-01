#ifndef HUMAN_HPP
#define HUMAN_HPP

#include <Object.hpp>
#include <vector>
#include <map>

struct Skeleton{
    Object chest;
    Object head;
    Object left_upper_arm;
    Object left_forearm;
    Object right_upper_arm;
    Object right_forearm;
    Object left_upper_leg;
    Object left_foreleg;
    Object right_upper_leg;
    Object right_foreleg;
};

struct Keyframe{
    vec3    rotation_value;
    Object* obj;
};

enum BODY_PART { Chest, Head, 
                Left_Upper_Arm, Left_Forearm, Right_Upper_Arm, Right_Forearm, 
                Left_Upper_Leg, Left_Foreleg, Right_Upper_Leg, Right_Foreleg};

class Human
{
private:
    Object _visual[10];
    Object _skeleton[10];
    std::map<float, std::vector<Keyframe>> _keyframes;
public:
    Human(Material* skin_material, Material* shirt_material, Material* trousers_material, Mesh* cube_mesh);
    ~Human();

    void addObjectsToScene(std::vector<Object*>& scene_objects);
    void addKeyFrame(const BODY_PART body_part, const vec3& rotation, const float time);
    void removeKeyFrame(const BODY_PART body_part, const float time);
    void pose(const BODY_PART body_part, const vec3& rotation);

    void animate(const float time);
};
#endif