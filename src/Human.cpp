#include <Human.hpp>

/* Human::Human(Material* skin_material, Material* shirt_material, Material* trousers_material, Mesh* cube_mesh):
_chest(shirt_material, cube_mesh), _head(skin_material, cube_mesh),
_left_upper_arm(shirt_material, cube_mesh), _left_forearm(skin_material, cube_mesh),
_right_upper_arm(shirt_material, cube_mesh), _right_forearm(skin_material, cube_mesh),
_left_upper_leg(trousers_material, cube_mesh), _left_foreleg(trousers_material, cube_mesh),
_right_upper_leg(trousers_material, cube_mesh), _right_foreleg(trousers_material, cube_mesh) */
Human::Human(Material* skin_material, Material* shirt_material, Material* trousers_material, Mesh* cube_mesh):
_visual{ Object(shirt_material, cube_mesh), Object(skin_material, cube_mesh),
Object(shirt_material, cube_mesh), Object(skin_material, cube_mesh),
Object(shirt_material, cube_mesh), Object(skin_material, cube_mesh),
Object(trousers_material, cube_mesh), Object(trousers_material, cube_mesh),
Object(trousers_material, cube_mesh), Object(trousers_material, cube_mesh)
}
{
    _skeleton[Head].setParent(&_skeleton[Chest]);
    _skeleton[Left_Upper_Arm].setParent(&_skeleton[Chest]);
    _skeleton[Left_Forearm].setParent(&_skeleton[Left_Upper_Arm]);
    _skeleton[Right_Upper_Arm].setParent(&_skeleton[Chest]);
    _skeleton[Right_Forearm].setParent(&_skeleton[Right_Upper_Arm]);
    _skeleton[Left_Upper_Leg].setParent(&_skeleton[Chest]);
    _skeleton[Left_Foreleg].setParent(&_skeleton[Left_Upper_Leg]);
    _skeleton[Right_Upper_Leg].setParent(&_skeleton[Chest]);
    _skeleton[Right_Foreleg].setParent(&_skeleton[Right_Upper_Leg]);

    _visual[Chest].setParent(&_skeleton[Chest]);
    _visual[Head].setParent(&_skeleton[Head]);
    _visual[Left_Upper_Arm].setParent(&_skeleton[Left_Upper_Arm]);
    _visual[Left_Forearm].setParent(&_skeleton[Left_Forearm]);
    _visual[Right_Upper_Arm].setParent(&_skeleton[Right_Upper_Arm]);
    _visual[Right_Forearm].setParent(&_skeleton[Right_Forearm]);
    _visual[Left_Upper_Leg].setParent(&_skeleton[Left_Upper_Leg]);
    _visual[Left_Foreleg].setParent(&_skeleton[Left_Foreleg]);
    _visual[Right_Upper_Leg].setParent(&_skeleton[Right_Upper_Leg]);
    _visual[Right_Foreleg].setParent(&_skeleton[Right_Foreleg]);

    _skeleton[Head].move(vec3(0, 3, 0));
    _skeleton[Left_Upper_Arm].move(vec3(-1.5, 2.75, 0));
    _skeleton[Left_Forearm].move(vec3(0, -1.35, 0));
    _skeleton[Right_Upper_Arm].move(vec3(1.5, 2.75, 0));
    _skeleton[Right_Forearm].move(vec3(0, -1.35, 0));
    _skeleton[Left_Upper_Leg].move(vec3(-0.5, -0.25, 0));
    _skeleton[Left_Foreleg].move(vec3(0, -1.25, 0));
    _skeleton[Right_Upper_Leg].move(vec3(0.5, -0.25, 0));
    _skeleton[Right_Foreleg].move(vec3(0, -1.25, 0));

    _visual[Chest].scale(vec3(2, 3, 1));
    _visual[Chest].move(vec3(0, 1.5, 0));
    _visual[Head].scale(vec3(2, 2, 2));
    _visual[Head].move(vec3(0, 1, 0));
    _visual[Left_Upper_Arm].scale(vec3(1, 1.6, 1));
    _visual[Left_Upper_Arm].move(vec3(0, -0.55, 0));
    _visual[Left_Forearm].scale(vec3(1, 1.6, 1));
    _visual[Left_Forearm].move(vec3(0, -0.8, 0));
    _visual[Right_Upper_Arm].scale(vec3(1, 1.6, 1));
    _visual[Right_Upper_Arm].move(vec3(0, -0.55, 0));
    _visual[Right_Forearm].scale(vec3(1, 1.6, 1));
    _visual[Right_Forearm].move(vec3(0, -0.8, 0));
    _visual[Left_Upper_Leg].scale(vec3(1, 1.5, 1));
    _visual[Left_Upper_Leg].move(vec3(0, -0.5, 0));
    _visual[Left_Foreleg].scale(vec3(1, 1.5, 1));
    _visual[Left_Foreleg].move(vec3(0, -0.75, 0));
    _visual[Right_Upper_Leg].scale(vec3(1, 1.5, 1));
    _visual[Right_Upper_Leg].move(vec3(0, -0.5, 0));
    _visual[Right_Foreleg].scale(vec3(1, 1.5, 1));
    _visual[Right_Foreleg].move(vec3(0, -0.75, 0));

    _skeleton[Chest].setName("Skeleton_Chest");
    _skeleton[Head].setName("Skeleton_Head");
    _skeleton[Left_Upper_Arm].setName("Skeleton_Left_Upper_Arm");
    _skeleton[Left_Forearm].setName("Skeleton_Left_Forearm");
    _skeleton[Right_Upper_Arm].setName("Skeleton_Right_Upper_Arm");
    _skeleton[Right_Forearm].setName("Skeleton_Right_Forearm");
    _skeleton[Left_Upper_Leg].setName("Skeleton_Left_Upper_Leg");
    _skeleton[Left_Foreleg].setName("Skeleton_Left_Foreleg");
    _skeleton[Right_Upper_Leg].setName("Skeleton_Right_UpperLeg");
    _skeleton[Right_Foreleg].setName("Skeleton_Right_Foreleg");

    _visual[Head].setName("Head");
    _visual[Left_Upper_Arm].setName("Left_Upper_Arm");
    _visual[Left_Forearm].setName("Left_Forearm");
    _visual[Right_Upper_Arm].setName("Right_Upper_Arm");
    _visual[Right_Forearm].setName("Right_Forearm");
    _visual[Left_Upper_Leg].setName("Left_Upper_Leg");
    _visual[Left_Foreleg].setName("Left_Foreleg");
    _visual[Right_Upper_Leg].setName("Right_UpperLeg");
    _visual[Right_Foreleg].setName("Right_Foreleg");
}

Human::~Human(){
}

void Human::addObjectsToScene(std::vector<Object*>& scene_objects){
    scene_objects.push_back(&_skeleton[Chest]);
    scene_objects.push_back(&_skeleton[Head]);
    scene_objects.push_back(&_skeleton[Left_Upper_Arm]);
    scene_objects.push_back(&_skeleton[Left_Forearm]);
    scene_objects.push_back(&_skeleton[Right_Upper_Arm]);
    scene_objects.push_back(&_skeleton[Right_Forearm]);
    scene_objects.push_back(&_skeleton[Left_Upper_Leg]);
    scene_objects.push_back(&_skeleton[Left_Foreleg]);
    scene_objects.push_back(&_skeleton[Right_Upper_Leg]);
    scene_objects.push_back(&_skeleton[Right_Foreleg]);

    scene_objects.push_back(&_visual[Chest]);
    scene_objects.push_back(&_visual[Head]);
    scene_objects.push_back(&_visual[Left_Upper_Arm]);
    scene_objects.push_back(&_visual[Left_Forearm]);
    scene_objects.push_back(&_visual[Right_Upper_Arm]);
    scene_objects.push_back(&_visual[Right_Forearm]);
    scene_objects.push_back(&_visual[Left_Upper_Leg]);
    scene_objects.push_back(&_visual[Left_Foreleg]);
    scene_objects.push_back(&_visual[Right_Upper_Leg]);
    scene_objects.push_back(&_visual[Right_Foreleg]);

}

void Human::pose(const BODY_PART body_part, const vec3& position, const vec3& rotation){
    _skeleton[body_part].setPosition(position);
    _skeleton[body_part].setRotation(rotation);
}

Object* Human::getBodyPart(const BODY_PART body_part){
    return &(_skeleton[body_part]);
}