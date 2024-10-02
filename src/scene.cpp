#include <humangl.hpp>

float delta_time = 0.0f;
float last_frame = 0.0f;

Camera camera(80, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1, 100.0f);

void drawTimeline(float& time, float time_min, float time_max, std::map<Object*, std::map<float,vec3>> _objects_keyframes);

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


            ImGui::Begin("Timeline");

            drawTimeline(time, 0, time_limit, anim.getObjectsKeyframes());

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


#include <set>
void drawTimeline(float& time, float time_min, float time_max, std::map<Object*, std::map<float,vec3>> _objects_keyframes) {



    // Get the ImGui window draw list for custom rendering
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    // Define the window size and timeline dimensions
    ImVec2 window_pos = ImGui::GetCursorScreenPos();  // Top-left corner of the window
    float line_height = 40.0f;  // Height allocated for each object's line
    float circle_radius = 5.0f; // Radius of the keyframe dots
    float timeline_length = 600.0f;  // Length of the timeline in pixels
    float name_offset = 120.0f; // Space on the left for object names
    float time_bar_x = window_pos.x + name_offset + (time - time_min) / (time_max - time_min) * timeline_length;

    // Iterate over each object and its keyframes
    int object_index = 0;
    std::set<float> timestamps;
    for (auto& [object, keyframes] : _objects_keyframes) {
        float y_top = window_pos.y + line_height * object_index;   // Top Y of the space allocated for the object
        float y_center = y_top + line_height / 2.0f;               // Y coordinate for drawing the timeline in the middle

        // Draw the object name
        ImGui::SetCursorScreenPos(ImVec2(window_pos.x, y_top + line_height / 4.0f));  // Slightly above the center
        int skeleton_offset = (object->getName().length() > 9)? 9 : 0; //Remove "Skeleton_" from the name
        ImGui::Text("%s", object->getName().c_str() + skeleton_offset);

        // Draw the timeline line for this object (centered vertically)
        draw_list->AddLine(ImVec2(window_pos.x + name_offset, y_center), ImVec2(window_pos.x + name_offset + timeline_length, y_center), IM_COL32(255, 255, 255, 255), 2.0f);

        // Draw the keyframe dots
        for (const auto& [keyframe_time, vec] : keyframes) {
            float x = window_pos.x + name_offset + (keyframe_time - time_min) / (time_max - time_min) * timeline_length;
            draw_list->AddCircleFilled(ImVec2(x, y_center), circle_radius, IM_COL32(255, 0, 0, 255));
            timestamps.insert(keyframe_time);
        }

        object_index++;
    }
    // Draw the time bar (vertical line indicating the current time)
    draw_list->AddLine(ImVec2(time_bar_x, window_pos.y), ImVec2(time_bar_x, window_pos.y + line_height * object_index), IM_COL32(0, 255, 0, 255), 2.0f);

    if (ImGui::Button("<")){
        auto it = timestamps.lower_bound(time);
        if (it != timestamps.begin()){
            it--;
            if (it != timestamps.begin() && *it == time)
                it--;
            time = *it;
        }
    }
    ImGui::SameLine();
    if (ImGui::Button(">")){
        auto it = timestamps.upper_bound(time);
        if (it != timestamps.end()){
            time = *it;
        }
    }

}