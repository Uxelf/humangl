#include <humangl.hpp>


int main(){

    print_instructions();

    GLFWwindow* window = createWindow(SCR_WIDTH, SCR_HEIGHT, "OGL");
    if (window == NULL)
        return 1;
    
    loadScene(window);

    glfwTerminate();

    return 0;
}
