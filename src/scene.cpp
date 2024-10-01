#include <humangl.hpp>

float delta_time = 0.0f;
float last_frame = 0.0f;

Camera camera(80, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1, 100.0f);

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
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); //Vsync (not working in wsl)

    //* Render loop
    camera.move(vec3(0, 2, 10));

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

        for (unsigned int i = 0; i < scene_objects.size(); i++){
            scene_objects[i]->render();
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}