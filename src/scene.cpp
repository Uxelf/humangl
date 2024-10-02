#include <humangl.hpp>

float delta_time = 0.0f;
float last_frame = 0.0f;

Camera camera(80, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1, 100.0f);

void saludar(){
    std::cout << "Geloo" << std::endl;
}

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

    vec3 body_vector[10];

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    std::string parts[] = {"Chest", "Head", "Left_Upper_Arm", "Left_Forearm", "Right_Upper_Arm", "Right_Forearm", "Left_Upper_Leg", "Left_Foreleg", "Right_Upper_Leg", "Right_Foreleg"};
    float time = 0;
    float time_limit = 10;
    Animation_controller anim;
    bool play = false;

    //* Render loop
    camera.move(vec3(0, 2, 10));

    while(!glfwWindowShouldClose(window)){
        
        float current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;  

        processInput(window, camera, delta_time);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            ImGui::Begin("Animation controller");
            ImGui::InputFloat("Time limit", &time_limit);
            if (ImGui::Button("Play"))
                play = true;
            ImGui::SameLine();
            if (ImGui::Button("Stop"))
                play = false;

            if (play)
                time += delta_time;
            if (time > time_limit)
                time -= time_limit;
            if (time < 0)
                time = 0;
            if (play){
                anim.animate(time);
                for (int i = 0; i < 10; i++){
                    body_vector[i] = human.getBodyPart(static_cast<BODY_PART>(i))->getRotation();
                }
            }
            if (ImGui::SliderFloat("Time", &time, 0, time_limit)){
                anim.animate(time);
                for (int i = 0; i < 10; i++){
                    body_vector[i] = human.getBodyPart(static_cast<BODY_PART>(i))->getRotation();
                }
            }
            for (int i = 0; i < 10; i++){
                std::string part_str = parts[i];
                ImGui::DragFloat3(part_str.c_str(), body_vector[i].value_ptr());
                if (ImGui::Button(("Save pose " + part_str).c_str()))
                    anim.addKeyframe(human.getBodyPart(static_cast<BODY_PART>(i)), time, body_vector[i]);
            }


            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        for (int i = 0; i < 10; i++)
            human.pose(static_cast<BODY_PART>(i), body_vector[i]);

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