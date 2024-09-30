#include <humangl.hpp>

float delta_time = 0.0f;
float last_frame = 0.0f;

Camera camera(45, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1, 100.0f);

void loadScene(GLFWwindow* window){

    glClearColor(0.1, 0.1, 0.1, 1.0f);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    //* Shaders load

    Shader shader_lit("./shaders/lit/lit.vs", "./shaders/lit/lit.fs");


    //* Materials

    Material material_blue(shader_lit, vec3(0.4, 0.7, 1));
    Material material_red(shader_lit, vec3(1, 0.2, 0.2));


    //* Mesh

    Mesh cube_mesh;


    //* Objects load

    std::vector<Object*> scene_objects;


    Object center(material_blue, &cube_mesh);
    Object left_arm_pivot(material_red, NULL);
    Object left_arm_visual(material_red, &cube_mesh);

    left_arm_pivot.move(vec3(0.5, 0, 0));
    left_arm_pivot.setParent(&center);
    left_arm_visual.move(vec3(0.5, 0, 0));
    left_arm_visual.setParent(&left_arm_pivot);

    scene_objects.push_back(&center);
    scene_objects.push_back(&left_arm_pivot);
    scene_objects.push_back(&left_arm_visual);


    //* Uniform buffers objects

    unsigned int UBO_matrices = createUBO(2 * MAT4_SIZE);

    GLuint matrices_binding_point = 0;

    glBindBufferBase(GL_UNIFORM_BUFFER, matrices_binding_point, UBO_matrices);
    uniformBlockBind(shader_lit.ID, "Matrices", matrices_binding_point);


    //* Render settigns

    glEnable(GL_DEPTH_TEST);
    // glPolygonMode(GL_FRONT_AND_BACK, [MODE]); // GL_LINE = Wireframe ; GL_FILL = Fill
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); //Vsync (not working in wsl)

    //* Render loop
    camera.move(vec3(0, 0, 4));

    while(!glfwWindowShouldClose(window)){
        
        float current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;  

        processInput(window, camera, delta_time);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        const mat4& projection = camera.getPerspectiveProjection();
        const mat4& view = camera.getViewMatrix();

        glBindBuffer(GL_UNIFORM_BUFFER, UBO_matrices);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, MAT4_SIZE, projection.value_ptr());
        glBufferSubData(GL_UNIFORM_BUFFER, MAT4_SIZE, MAT4_SIZE, view.value_ptr());
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        center.rotate(vec3(0, 0.2, 0));
        left_arm_pivot.setRotation(vec3(0, 0, sin(current_frame) * 40));
        for (unsigned int i = 0; i < scene_objects.size(); i++){
            scene_objects[i]->render();
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}