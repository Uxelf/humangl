#include <UI.hpp>

extern bool update_on_keyframe;

char file_name[200] = "";

std::vector<Object*> body_parts;
std::vector<vec3> positions;
std::vector<vec3> rotations;

void setUIHumanData(Human& human){
    for (unsigned int i = 0; i < PARTS_NUMBER; i++){
        body_parts.push_back(human.getBodyPart(static_cast<BODY_PART>(i)));
        positions.push_back(body_parts[i]->getPosition());
        rotations.push_back(body_parts[i]->getRotation());
    }
}

void drawUI(Animation_controller& anim, time_controllers& time_c, Human& human){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    drawMainInterface(anim, time_c, human);
    drawTimeline(time_c.time, 0, time_c.time_limit, anim.getObjectsKeyframes());
}

void drawMainInterface(Animation_controller& anim, time_controllers& time_c, Human& human){
    
    ImGui::Begin("Animation controller");

    ImGui::InputText("File", file_name, 200);
    if (ImGui::Button("Save"))
        anim.saveAnimation(file_name);
    ImGui::SameLine();
    if (ImGui::Button("Load"))
        anim.loadAnimation(file_name);

    ImGui::InputFloat("Time scale", &time_c.time_scale);
    ImGui::InputFloat("Time limit", &time_c.time_limit);
    if (ImGui::Button("Play"))
        time_c.play = true;
    ImGui::SameLine();
    if (ImGui::Button("Stop"))
        time_c.play = false;

    if (time_c.play){
        time_c.time += time_c.delta_time * time_c.time_scale;
        if (time_c.time > time_c.time_limit)
            time_c.time -= time_c.time_limit;
    }

    if (time_c.play || update_on_keyframe){
        anim.animate(time_c.time);
        for (unsigned int i = 0; i < PARTS_NUMBER; i++){
            positions[i] = body_parts[i]->getPosition();
            rotations[i] = body_parts[i]->getRotation();
        }
    }

    if (ImGui::SliderFloat("Time", &time_c.time, 0, time_c.time_limit)){
        anim.animate(time_c.time);
        for (unsigned int i = 0; i < PARTS_NUMBER; i++){
            positions[i] = body_parts[i]->getPosition();
            rotations[i] = body_parts[i]->getRotation();
        }
    }

    if (ImGui::CollapsingHeader("Body controllers")){
        for (unsigned int i = 0; i < PARTS_NUMBER; i++){
            std::string part_pos_str = PARTS[i] + " pos";
            std::string part_rot_str = PARTS[i] + " rot";
            ImGui::PushID(PARTS[i].c_str());
            ImGui::DragFloat3(part_pos_str.c_str(), positions[i].value_ptr());
            ImGui::DragFloat3(part_rot_str.c_str(), rotations[i].value_ptr());
            if (ImGui::Button(("O")))
                anim.addKeyframe(human.getBodyPart(static_cast<BODY_PART>(i)), time_c.time, positions[i], rotations[i]);
            ImGui::SameLine();
            if (ImGui::Button(("X")))
                anim.removeKeyframe(human.getBodyPart(static_cast<BODY_PART>(i)), time_c.time);
            ImGui::Spacing();
            ImGui::PopID();
        }
    }
    ImGui::End();

    if (!time_c.play){
            for (unsigned int i = 0; i < PARTS_NUMBER; i++)
                human.pose(static_cast<BODY_PART>(i), positions[i], rotations[i]);
    }
}

void drawTimeline(float& time, const float time_min, const float time_max, const std::map<Object*, std::map<float,properties>> _objects_keyframes) {

    ImGui::Begin("Timeline");

    // Get the ImGui window draw list for custom rendering
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    // Define the window size and timeline dimensions
    ImVec2 window_pos = ImGui::GetCursorScreenPos();  // Top-left corner of the window
    float line_height = 40.0f;  // Height allocated for each object's line
    float circle_radius = 5.0f; // Radius of the keyframe dots
    float timeline_length = 400.0f;  // Length of the timeline in pixels
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

    if (ImGui::ArrowButton("<", ImGuiDir_Left)){
        auto it = timestamps.lower_bound(time);
        if (it != timestamps.begin()){
            it--;
            if (it != timestamps.begin() && *it == time)
                it--;
            time = *it;
        }
    }
    ImGui::SameLine();
    if (ImGui::ArrowButton(">", ImGuiDir_Right)){
        auto it = timestamps.upper_bound(time);
        if (it != timestamps.end()){
            time = *it;
        }
    }
    ImGui::Spacing();
    ImGui::Text("Update");
    ImGui::SameLine();
    if (update_on_keyframe){
        if (ImGui::Button("Y"))
            update_on_keyframe = false;
    }
    else
        if (ImGui::Button("N"))
            update_on_keyframe = true;

    
    ImGui::End();

}