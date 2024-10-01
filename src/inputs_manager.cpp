#include <humangl.hpp>

extern Camera camera;

void processInput(GLFWwindow* window, Camera& camera, float delta_time){

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    vec3 fp_direction = camera.front();
    fp_direction.y = 0;
    fp_direction = fp_direction.normalized();
    vec3 movement;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        movement = movement + fp_direction * CAMERA_SPEED * delta_time;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        movement = movement - fp_direction * CAMERA_SPEED * delta_time;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        movement = movement - camera.right() * CAMERA_SPEED * delta_time;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        movement = movement + camera.right() * CAMERA_SPEED * delta_time;

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        movement = movement + vec3(0, 1, 0) * CAMERA_SPEED * delta_time;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        movement = movement - vec3(0, 1, 0) * CAMERA_SPEED * delta_time ;

    
    static float pitch = 0; 
    static float yaw = 90;
    float xoffset = 0, yoffset = 0;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        xoffset += -delta_time;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        xoffset += delta_time;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        yoffset += delta_time;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        yoffset += -delta_time;
    
    
    yaw += xoffset * CAMERA_SENSIBILITY * 20000;
    pitch += yoffset * CAMERA_SENSIBILITY * 20000;
    if (pitch > 89.0f)
        pitch = 89.0f;
    else if (pitch < -89.0f)
        pitch = -89.0f;
    vec3 direction;
    direction[0] = -cos(DEG_TO_RAD(yaw)) * cos(DEG_TO_RAD(pitch));
    direction[1] = sin(DEG_TO_RAD(pitch));
    direction[2] = -sin(DEG_TO_RAD(yaw)) * cos(DEG_TO_RAD(pitch));
    camera.setFront(direction.normalized());
    
    camera.move(movement);
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