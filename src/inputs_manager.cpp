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



void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    return;
    static float lastX = SCR_WIDTH / 2;
    static float lastY = SCR_HEIGHT / 2;
    static bool firstMouse = true;
    
    static float pitch = 0; 
    static float yaw = 90;

    if (!window)
        return;
    if (firstMouse){
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    yaw += xoffset * CAMERA_SENSIBILITY;
    pitch += yoffset * CAMERA_SENSIBILITY;

    if (pitch > 89.0f)
        pitch = 89.0f;
    else if (pitch < -89.0f)
        pitch = -89.0f;

    vec3 direction;
    direction[0] = -cos(DEG_TO_RAD(yaw)) * cos(DEG_TO_RAD(pitch));
    direction[1] = sin(DEG_TO_RAD(pitch));
    direction[2] = -sin(DEG_TO_RAD(yaw)) * cos(DEG_TO_RAD(pitch));

    camera.setFront(direction.normalized());
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (!window)
        return;
    (void)xoffset;

    float fov = camera.getFov() - (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 120.0f)
        fov = 120.0f;

    camera.setFov(fov);
}