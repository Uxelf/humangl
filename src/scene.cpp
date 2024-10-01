#include <humangl.hpp>

float delta_time = 0.0f;
float last_frame = 0.0f;

Camera camera(80, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1, 100.0f);

void loadScene(GLFWwindow* window){

    glClearColor(0.1, 0.1, 0.1, 1.0f);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    //* Shaders load

    Shader shader_lit("./shaders/lit/lit.vs", "./shaders/lit/lit.fs");


    //* Materials

    Material material_blue(shader_lit, vec3(0.286, 0.275, 0.592));
    Material material_teal(shader_lit, vec3(0.055, 0.682, 0.682));
    Material material_brown(shader_lit, vec3(0.663, 0.49, 0.392));
    Material material_red(shader_lit, vec3(1, 0.2, 0.2));


    //* Mesh

    Mesh cube_mesh;


    //* Objects load

    std::vector<Object*> scene_objects;


    Object chest_pivot;
    Object chest_visual(&material_teal, &cube_mesh);
    chest_visual.setParent(&chest_pivot);
    chest_visual.move(vec3(0, 1.5, 0));
    chest_visual.scale(vec3(2, 3, 1));
    scene_objects.push_back(&chest_pivot);
    scene_objects.push_back(&chest_visual);


    Object head_pivot;
    Object head_visual(&material_brown, &cube_mesh);
    head_pivot.setParent(&chest_pivot);
    head_visual.setParent(&head_pivot);
    head_pivot.move(vec3(0, 3, 0));
    head_visual.scale(vec3(2, 2, 2));
    head_visual.move(vec3(0, 1, 0));
    scene_objects.push_back(&head_pivot);
    scene_objects.push_back(&head_visual);


    //* Arms

    Object left_upper_arm_pivot;
    Object left_upper_arm_visual(&material_teal, &cube_mesh);
    left_upper_arm_pivot.setParent(&chest_pivot);
    left_upper_arm_visual.setParent(&left_upper_arm_pivot);
    left_upper_arm_pivot.move(vec3(-1.5, 2.75, 0));
    left_upper_arm_visual.scale(vec3(1, 1.6, 1));
    left_upper_arm_visual.move(vec3(0, -0.55, 0));
    left_upper_arm_visual.setParent(&left_upper_arm_pivot);
    scene_objects.push_back(&left_upper_arm_pivot);
    scene_objects.push_back(&left_upper_arm_visual);

    Object left_forearm_pivot;
    Object left_forearm_visual(&material_brown, &cube_mesh);
    left_forearm_pivot.setParent(&left_upper_arm_pivot);
    left_forearm_visual.setParent(&left_forearm_pivot);
    left_forearm_pivot.move(vec3(0, -1.35, 0));
    left_forearm_visual.scale(vec3(1, 1.6, 1));
    left_forearm_visual.move(vec3(0, -0.8, 0));
    scene_objects.push_back(&left_forearm_pivot);
    scene_objects.push_back(&left_forearm_visual);
        

    Object right_upper_arm_pivot;
    Object right_upper_arm_visual(&material_teal, &cube_mesh);
    right_upper_arm_pivot.setParent(&chest_pivot);
    right_upper_arm_visual.setParent(&right_upper_arm_pivot);
    right_upper_arm_pivot.move(vec3(1.5, 2.75, 0));
    right_upper_arm_visual.scale(vec3(1, 1.6, 1));
    right_upper_arm_visual.move(vec3(0, -0.55, 0));
    right_upper_arm_visual.setParent(&right_upper_arm_pivot);
    scene_objects.push_back(&right_upper_arm_pivot);
    scene_objects.push_back(&right_upper_arm_visual);

    Object right_forearm_pivot;
    Object right_forearm_visual(&material_brown, &cube_mesh);
    right_forearm_pivot.setParent(&right_upper_arm_pivot);
    right_forearm_visual.setParent(&right_forearm_pivot);
    right_forearm_pivot.move(vec3(0, -1.35, 0));
    right_forearm_visual.scale(vec3(1, 1.6, 1));
    right_forearm_visual.move(vec3(0, -0.8, 0));
    scene_objects.push_back(&right_forearm_pivot);
    scene_objects.push_back(&right_forearm_visual);
    

    //* Legs

    Object left_upper_leg_pivot;
    Object left_upper_leg_visual(&material_blue, &cube_mesh);
    left_upper_leg_pivot.setParent(&chest_pivot);
    left_upper_leg_visual.setParent(&left_upper_leg_pivot);
    left_upper_leg_pivot.move(vec3(-0.5, -0.25, 0));
    left_upper_leg_visual.scale(vec3(1, 1.5, 1));
    left_upper_leg_visual.move(vec3(0, -0.5, 0));
    left_upper_leg_visual.setParent(&left_upper_leg_pivot);
    scene_objects.push_back(&left_upper_leg_pivot);
    scene_objects.push_back(&left_upper_leg_visual);

    Object left_foreleg_pivot;
    Object left_foreleg_visual(&material_blue, &cube_mesh);
    left_foreleg_pivot.setParent(&left_upper_leg_pivot);
    left_foreleg_visual.setParent(&left_foreleg_pivot);
    left_foreleg_pivot.move(vec3(0, -1.25, 0));
    left_foreleg_visual.scale(vec3(1, 1.5, 1));
    left_foreleg_visual.move(vec3(0, -0.75, 0));
    scene_objects.push_back(&left_foreleg_pivot);
    scene_objects.push_back(&left_foreleg_visual);
        

    Object right_upper_leg_pivot;
    Object right_upper_leg_visual(&material_blue, &cube_mesh);
    right_upper_leg_pivot.setParent(&chest_pivot);
    right_upper_leg_visual.setParent(&right_upper_leg_pivot);
    right_upper_leg_pivot.move(vec3(0.5, -0.25, 0));
    right_upper_leg_visual.scale(vec3(1, 1.5, 1));
    right_upper_leg_visual.move(vec3(0, -0.5, 0));
    right_upper_leg_visual.setParent(&right_upper_leg_pivot);
    scene_objects.push_back(&right_upper_leg_pivot);
    scene_objects.push_back(&right_upper_leg_visual);

    Object right_foreleg_pivot;
    Object right_foreleg_visual(&material_blue, &cube_mesh);
    right_foreleg_pivot.setParent(&right_upper_leg_pivot);
    right_foreleg_visual.setParent(&right_foreleg_pivot);
    right_foreleg_pivot.move(vec3(0, -1.25, 0));
    right_foreleg_visual.scale(vec3(1, 1.5, 1));
    right_foreleg_visual.move(vec3(0, -0.75, 0));
    scene_objects.push_back(&right_foreleg_pivot);
    scene_objects.push_back(&right_foreleg_visual);
    



    //* Uniform buffers objects

    unsigned int UBO_matrices = createUBO(2 * MAT4_SIZE);

    GLuint matrices_binding_point = 0;

    glBindBufferBase(GL_UNIFORM_BUFFER, matrices_binding_point, UBO_matrices);
    uniformBlockBind(shader_lit.ID, "Matrices", matrices_binding_point);


    //* Render settigns

    glEnable(GL_DEPTH_TEST);
    // glPolygonMode(GL_FRONT_AND_BACK, [MODE]); // GL_LINE = Wireframe ; GL_FILL = Fill
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); //Vsync (not working in wsl)

    //* Render loop
    camera.move(vec3(0, 2, 4));

    //chest_pivot.rotate(vec3(0, 45, 0));

    while(!glfwWindowShouldClose(window)){
        
        float current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;  

        processInput(window, camera, delta_time);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        const mat4& projection = camera.getPerspectiveProjection();
        const mat4& view = camera.getViewMatrix();

        glBindBuffer(GL_UNIFORM_BUFFER, UBO_matrices);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, MAT4_SIZE, projection.value_ptr());
        glBufferSubData(GL_UNIFORM_BUFFER, MAT4_SIZE, MAT4_SIZE, view.value_ptr());
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        //chest_pivot.rotate(vec3(0, 0.2, 0));
        //left_upper_leg_pivot.setRotation(vec3(sin(current_frame) * 40, 0, 0));
        for (unsigned int i = 0; i < scene_objects.size(); i++){
            scene_objects[i]->render();
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}