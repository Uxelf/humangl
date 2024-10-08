#include <humangl.hpp>

extern Camera camera;
extern Object central_pivot;
extern Object camera_pivot;

void processInput(GLFWwindow* window, float delta_time){

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    static float yaw = 90;
    float xoffset = 0, zoffset = 0;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        xoffset += delta_time;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        xoffset += -delta_time;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        zoffset += -delta_time * CAMERA_SPEED;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        zoffset += delta_time * CAMERA_SPEED;
    
    camera_pivot.move(vec3(0, 0, zoffset));

    yaw += xoffset * CAMERA_SENSIBILITY * 20000;
    vec3 direction;
    direction[0] = -cos(DEG_TO_RAD(yaw));
    direction[1] = 0;
    direction[2] = -sin(DEG_TO_RAD(yaw));
    central_pivot.setRotation(vec3(0, -yaw + 90, 0));

    camera.setFront(direction.normalized());
    camera.moveTo(camera_pivot.getGlobalPosition());
}
