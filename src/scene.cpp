#include <humangl.hpp>

float delta_time = 0.0f;
float last_frame = 0.0f;

Camera camera(80, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1, 100.0f);
Object central_pivot;
Object camera_pivot;

bool update_on_keyframe = false;
void loadScene(GLFWwindow* window){

    glClearColor(0.1, 0.1, 0.1, 1.0f);

    //* Shaders load

    Shader shader_lit("./shaders/lit/lit.vs", "./shaders/lit/lit.fs");


    //* Materials

    Material material_blue(shader_lit, vec3(0.286, 0.275, 0.592));
    Material material_teal(shader_lit, vec3(0.055, 0.682, 0.682));
    Material material_brown(shader_lit, vec3(0.663, 0.49, 0.392));


    //* Mesh

    Mesh cube_mesh;


    //* Objects load

    std::vector<Object*> scene_objects;

    Human human(&material_brown, &material_teal, &material_blue, &cube_mesh);
    human.addObjectsToScene(scene_objects);


    //* Uniform buffers objects

    unsigned int UBO_matrices = createUBO(2 * MAT4_SIZE);

    GLuint matrices_binding_point = 0;

    glBindBufferBase(GL_UNIFORM_BUFFER, matrices_binding_point, UBO_matrices);
    uniformBlockBind(shader_lit.ID, "Matrices", matrices_binding_point);


    //* Render settigns

    glEnable(GL_DEPTH_TEST);
    // glPolygonMode(GL_FRONT_AND_BACK, [MODE]); // GL_LINE = Wireframe ; GL_FILL = Fill
    glfwSwapInterval(1); //Vsync (not working in wsl)


    //* UI

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 400");
    ImGui::StyleColorsDark();

    /* std::vector<vec3> body_positions;
    std::vector<vec3> body_rotations; */

    time_controllers time_c;
    time_c.play = false;
    time_c.time = 0;
    time_c.time_limit = 10;
    time_c.time_scale = 1;
    time_c.delta_time = delta_time;

    Animation_controller anim;
    setUIHumanData(human);

    for (unsigned int i = 0; i < PARTS_NUMBER; i++){
        Object* part = human.getBodyPart(static_cast<BODY_PART>(i));
        anim.registerObject(part);
    }

    //* Render loop

    //!Camera thingis
    
    camera_pivot.setParent(&central_pivot);
    camera_pivot.move(vec3(0, 2, 10));
    scene_objects.push_back(&central_pivot);
    scene_objects.push_back(&camera_pivot);


    while(!glfwWindowShouldClose(window)){
        
        central_pivot.rotate(vec3(0, 0.2, 0));

        float current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;
        time_c.delta_time = delta_time;

        processInput(window, delta_time);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        drawUI(anim, time_c, human);

        const mat4& projection = camera.getPerspectiveProjection();
        const mat4& view = camera.getViewMatrix();

        glBindBuffer(GL_UNIFORM_BUFFER, UBO_matrices);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, MAT4_SIZE, projection.value_ptr());
        glBufferSubData(GL_UNIFORM_BUFFER, MAT4_SIZE, MAT4_SIZE, view.value_ptr());
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        for (unsigned int i = 0; i < scene_objects.size(); i++){
            scene_objects[i]->render();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

