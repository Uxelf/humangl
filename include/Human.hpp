#ifndef HUMAN_HPP
#define HUMAN_HPP

#include <Object.hpp>
#include <vector>

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

class Human
{
private:
    Object  _chest;
    Object  _head;
    Object  _left_upper_arm;
    Object  _left_forearm;
    Object  _right_upper_arm;
    Object  _right_forearm;
    Object  _left_upper_leg;
    Object  _left_foreleg;
    Object  _right_upper_leg;
    Object  _right_foreleg;
    Skeleton _skeleton;
public:
    Human(Material* skin_material, Material* shirt_material, Material* trousers_material, Mesh* cube_mesh);
    ~Human();

    void addObjectsToScene(std::vector<Object*>& scene_objects);
};
#endif