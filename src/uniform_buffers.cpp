#include <humangl.hpp>

unsigned int createUBO(unsigned int size){
    unsigned int UBO;
    glGenBuffers(1, &UBO);
    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    return UBO;
}

void uniformBlockBind(int shader_ID, const std::string& name, GLuint binding_point){
    unsigned int uniform_block_index = glGetUniformBlockIndex(shader_ID, name.c_str());
    glUniformBlockBinding(shader_ID, uniform_block_index, binding_point);
}