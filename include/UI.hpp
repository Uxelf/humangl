#ifndef UI_HPP
#define UI_HPP

#include <Animation_controller.hpp>
#include <Human.hpp>
#include <set>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void drawUI(Animation_controller& anim, time_controllers& time_c, Human& human, Object& ground);
void setUIHumanData(Human& human);
void drawMainInterface(Animation_controller& anim, time_controllers& time_c, Human& human, Object& ground);
void drawTimeline(float& time, const float time_min, const float time_max, std::map<Object*, std::map<float,properties>> _objects_keyframes);


#endif