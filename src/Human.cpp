#include <Human.hpp>

Human::Human(Material* skin_material, Material* shirt_material, Material* trousers_material, Mesh* cube_mesh)
{
    initVisualParts(shirt_material, skin_material, trousers_material, cube_mesh);
    
    setParentAndPosition(Head, Chest, vec3(0, 3, 0), vec3(0, 1, 0), vec3(2, 2, 2));
    setParentAndPosition(Left_Upper_Arm, Chest, vec3(-1.5, 2.75, 0), vec3(0, -0.55, 0), vec3(1, 1.6, 1));
    setParentAndPosition(Left_Forearm, Left_Upper_Arm, vec3(0, -1.35, 0), vec3(0, -0.8, 0), vec3(1, 1.6, 1));
    setParentAndPosition(Right_Upper_Arm, Chest, vec3(1.5, 2.75, 0), vec3(0, -0.55, 0), vec3(1, 1.6, 1));
    setParentAndPosition(Right_Forearm, Right_Upper_Arm, vec3(0, -1.35, 0), vec3(0, -0.8, 0), vec3(1, 1.6, 1));
    setParentAndPosition(Left_Upper_Leg, Chest, vec3(-0.5, -0.25, 0), vec3(0, -0.5, 0), vec3(1, 1.5, 1));
    setParentAndPosition(Left_Foreleg, Left_Upper_Leg, vec3(0, -1.25, 0), vec3(0, -0.75, 0), vec3(1, 1.5, 1));
    setParentAndPosition(Right_Upper_Leg, Chest, vec3(0.5, -0.25, 0), vec3(0, -0.5, 0), vec3(1, 1.5, 1));
    setParentAndPosition(Right_Foreleg, Right_Upper_Leg, vec3(0, -1.25, 0), vec3(0, -0.75, 0), vec3(1, 1.5, 1));
    setParentAndPosition(Left_Wing, Chest, vec3(-0.4, 1.9, -0.5), vec3(0, 0, -2), vec3(0.2, 3, 3));
    setParentAndPosition(Right_Wing, Chest, vec3(0.4, 1.9, -0.5), vec3(0, 0, -2), vec3(0.2, 3, 3));

    _visual[Chest].setParent(&_skeleton[Chest]);
    _visual[Chest].scale(vec3(2, 3, 1));
    _visual[Chest].move(vec3(0, 1.5, 0));
    _visual[Left_Wing].rotate(vec3(55, 0, 5));
    _visual[Right_Wing].rotate(vec3(55, 0, -5));

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
    _skeleton[Left_Wing].setName("Skeleton_Lelft_Wing");
    _skeleton[Right_Wing].setName("Skeleton_Right_Wing");

    _visual[Head].setName("Head");
    _visual[Left_Upper_Arm].setName("Left_Upper_Arm");
    _visual[Left_Forearm].setName("Left_Forearm");
    _visual[Right_Upper_Arm].setName("Right_Upper_Arm");
    _visual[Right_Forearm].setName("Right_Forearm");
    _visual[Left_Upper_Leg].setName("Left_Upper_Leg");
    _visual[Left_Foreleg].setName("Left_Foreleg");
    _visual[Right_Upper_Leg].setName("Right_UpperLeg");
    _visual[Right_Foreleg].setName("Right_Foreleg");
    _visual[Left_Wing].setName("Left_Wing");
    _visual[Right_Wing].setName("Right_Wing");

    _visual[Left_Wing].toggleVisibility();
    _visual[Right_Wing].toggleVisibility();
}

Human::~Human(){
}

void Human::setParentAndPosition(BODY_PART part, BODY_PART parent_part, const vec3& skeleton_pos, const vec3& visual_pos, const vec3& visual_scale) {
    _skeleton[part].setParent(&_skeleton[parent_part]);
    _skeleton[part].move(skeleton_pos);

    _visual[part].setParent(&_skeleton[part]);
    _visual[part].scale(visual_scale);
    _visual[part].move(visual_pos);
}

void Human::initVisualParts(Material* shirt_material, Material* skin_material, Material* trousers_material, Mesh* cube_mesh) {
        Material* materials[PARTS_NUMBER] = {
            shirt_material, skin_material, // Chest and Head
            shirt_material, skin_material, // Left Arm
            shirt_material, skin_material, // Right Arm
            trousers_material, trousers_material, // Left Leg
            trousers_material, trousers_material, // Right Leg
            skin_material, skin_material // Wings
        };

        // Initialize _visual objects
        for (unsigned int i = 0; i < PARTS_NUMBER; ++i) {
            _visual[i] = Object(materials[i], cube_mesh);
        }
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
    scene_objects.push_back(&_skeleton[Left_Wing]);
    scene_objects.push_back(&_skeleton[Right_Wing]);

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
    scene_objects.push_back(&_visual[Left_Wing]);
    scene_objects.push_back(&_visual[Right_Wing]);

}

void Human::pose(const BODY_PART body_part, const vec3& position, const vec3& rotation){
    _skeleton[body_part].setPosition(position);
    _skeleton[body_part].setRotation(rotation);
}

Object* Human::getBodyPart(const BODY_PART body_part){
    return &(_skeleton[body_part]);
}

void Human::toggleWings(){
    _visual[Left_Wing].toggleVisibility();
    _visual[Right_Wing].toggleVisibility();
}