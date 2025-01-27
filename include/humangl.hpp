#ifndef HUMANGL_HPP
#define HUMANGL_HPP

#include <Material.hpp>
#include <Matrix4x4.hpp>
#include <Vector3.hpp>
#include <Vector4.hpp>
#include <Camera.hpp>
#include <Object.hpp>
#include <Human.hpp>
#include <Shader.hpp>
#include <Animation_controller.hpp>
#include <UI.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include <vector>

const unsigned int SCR_WIDTH = 1800;
const unsigned int SCR_HEIGHT = 1024;

const float CAMERA_SPEED = 4.5f;
const float CAMERA_SENSIBILITY = 0.004f;

void            print_instructions();
GLFWwindow*     createWindow(int width, int height, const std::string& name);
void            loadScene(GLFWwindow* window);
unsigned int    createUBO(unsigned int size);
void            uniformBlockBind(int shader_ID, const std::string& name, GLuint binding_point);
void            processInput(GLFWwindow* window, float delta_time);

#endif