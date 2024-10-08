#ifndef HUMAN_HPP
#define HUMAN_HPP

#include <Object.hpp>
#include <vector>
#include <map>

enum BODY_PART { Chest, Head, 
                Left_Upper_Arm, Left_Forearm, Right_Upper_Arm, Right_Forearm, 
                Left_Upper_Leg, Left_Foreleg, Right_Upper_Leg, Right_Foreleg,
                Left_Wing, Right_Wing};

const std::string PARTS[] = {"Chest", "Head", 
                "Left_Upper_Arm", "Left_Forearm", "Right_Upper_Arm", "Right_Forearm", 
                "Left_Upper_Leg", "Left_Foreleg", "Right_Upper_Leg", "Right_Foreleg",
                "Left_Wing", "Right_Wing"};
    
const unsigned int PARTS_NUMBER = 12;

class Human
{
private:
    Object  _visual[12];
    Object  _skeleton[12];

    void setParentAndPosition(BODY_PART part, BODY_PART parent_part, const vec3& skeleton_pos, const vec3& visual_pos, const vec3& visual_scale);
    void initVisualParts(Material* shirt_material, Material* skin_material, Material* trousers_material, Mesh* cube_mesh);

public:
    Human(Material* skin_material, Material* shirt_material, Material* trousers_material, Mesh* cube_mesh);
    ~Human();

    void addObjectsToScene(std::vector<Object*>& scene_objects);
    void pose(const BODY_PART body_part, const vec3& postion, const vec3& rotation);
    Object* getBodyPart(const BODY_PART body_part);
    void toggleWings();
    void resetPose();
};
#endif