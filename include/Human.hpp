#ifndef HUMAN_HPP
#define HUMAN_HPP

#include <Object.hpp>
#include <vector>
#include <map>


enum BODY_PART { Chest, Head, 
                Left_Upper_Arm, Left_Forearm, Right_Upper_Arm, Right_Forearm, 
                Left_Upper_Leg, Left_Foreleg, Right_Upper_Leg, Right_Foreleg};

class Human
{
private:
    Object _visual[10];
    Object _skeleton[10];
public:
    Human(Material* skin_material, Material* shirt_material, Material* trousers_material, Mesh* cube_mesh);
    ~Human();

    void addObjectsToScene(std::vector<Object*>& scene_objects);
    void pose(const BODY_PART body_part, const vec3& rotation);
    Object* getBodyPart(const BODY_PART body_part);
};
#endif