#include <Human.hpp>

Human::Human(Material* skin_material, Material* shirt_material, Material* trousers_material, Mesh* cube_mesh):
_chest(shirt_material, cube_mesh), _head(skin_material, cube_mesh),
_left_upper_arm(shirt_material, cube_mesh), _left_forearm(skin_material, cube_mesh),
_right_upper_arm(shirt_material, cube_mesh), _right_forearm(skin_material, cube_mesh),
_left_upper_leg(trousers_material, cube_mesh), _left_foreleg(trousers_material, cube_mesh),
_right_upper_leg(trousers_material, cube_mesh), _right_foreleg(trousers_material, cube_mesh)
{
    _skeleton.head.setParent(&_skeleton.chest);
    _skeleton.left_upper_arm.setParent(&_skeleton.chest);
    _skeleton.left_forearm.setParent(&_skeleton.left_upper_arm);
    _skeleton.right_upper_arm.setParent(&_skeleton.chest);
    _skeleton.right_forearm.setParent(&_skeleton.right_upper_arm);
    _skeleton.left_upper_leg.setParent(&_skeleton.chest);
    _skeleton.left_foreleg.setParent(&_skeleton.left_upper_leg);
    _skeleton.right_upper_leg.setParent(&_skeleton.chest);
    _skeleton.right_foreleg.setParent(&_skeleton.right_upper_leg);

    _head.setParent(&_skeleton.head);
    _left_upper_arm.setParent(&_skeleton.left_upper_arm);
    _left_forearm.setParent(&_skeleton.left_forearm);
    _right_upper_arm.setParent(&_skeleton.right_upper_arm);
    _right_forearm.setParent(&_skeleton.right_forearm);
    _left_upper_leg.setParent(&_skeleton.left_upper_leg);
    _left_foreleg.setParent(&_skeleton.left_foreleg);
    _right_upper_leg.setParent(&_skeleton.right_upper_leg);
    _right_foreleg.setParent(&_skeleton.right_foreleg);

    _skeleton.head.move(vec3(0, 3, 0));
    _skeleton.left_upper_arm.move(vec3(-1.5, 2.75, 0));
    _skeleton.left_forearm.move(vec3(0, -1.35, 0));
    _skeleton.right_upper_arm.move(vec3(1.5, 2.75, 0));
    _skeleton.right_forearm.move(vec3(0, -1.35, 0));
    _skeleton.left_upper_leg.move(vec3(-0.5, -0.25, 0));
    _skeleton.left_foreleg.move(vec3(0, -1.25, 0));
    _skeleton.right_upper_leg.move(vec3(0.5, -0.25, 0));
    _skeleton.right_foreleg.move(vec3(0, -1.25, 0));

    
    _chest.scale(vec3(2, 3, 1));
    _chest.move(vec3(0, 1.5, 0));
    _head.scale(vec3(2, 2, 2));
    _head.move(vec3(0, 1, 0));
    _left_upper_arm.scale(vec3(1, 1.6, 1));
    _left_upper_arm.move(vec3(0, -0.55, 0));
    _left_forearm.scale(vec3(1, 1.6, 1));
    _left_forearm.move(vec3(0, -0.8, 0));
    _right_upper_arm.scale(vec3(1, 1.6, 1));
    _right_upper_arm.move(vec3(0, -0.55, 0));
    _right_forearm.scale(vec3(1, 1.6, 1));
    _right_forearm.move(vec3(0, -0.8, 0));
    _left_upper_leg.scale(vec3(1, 1.5, 1));
    _left_upper_leg.move(vec3(0, -0.5, 0));
    _left_foreleg.scale(vec3(1, 1.5, 1));
    _left_foreleg.move(vec3(0, -0.75, 0));
    _right_upper_leg.scale(vec3(1, 1.5, 1));
    _right_upper_leg.move(vec3(0, -0.5, 0));
    _right_foreleg.scale(vec3(1, 1.5, 1));
    _right_foreleg.move(vec3(0, -0.75, 0));
}

Human::~Human(){
}

void Human::addObjectsToScene(std::vector<Object*>& scene_objects){
    scene_objects.push_back(&_skeleton.chest);
    scene_objects.push_back(&_skeleton.head);
    scene_objects.push_back(&_skeleton.left_upper_arm);
    scene_objects.push_back(&_skeleton.left_forearm);
    scene_objects.push_back(&_skeleton.right_upper_arm);
    scene_objects.push_back(&_skeleton.right_forearm);
    scene_objects.push_back(&_skeleton.left_upper_leg);
    scene_objects.push_back(&_skeleton.left_foreleg);
    scene_objects.push_back(&_skeleton.right_upper_leg);
    scene_objects.push_back(&_skeleton.right_foreleg);

    scene_objects.push_back(&_chest);
    scene_objects.push_back(&_head);
    scene_objects.push_back(&_left_upper_arm);
    scene_objects.push_back(&_left_forearm);
    scene_objects.push_back(&_right_upper_arm);
    scene_objects.push_back(&_right_forearm);
    scene_objects.push_back(&_left_upper_leg);
    scene_objects.push_back(&_left_foreleg);
    scene_objects.push_back(&_right_upper_leg);
    scene_objects.push_back(&_right_foreleg);
}