#ifndef MESH_HPP
#define MESH_HPP

#include <glad/glad.h>

class Mesh
{
private:
    unsigned int    _VAO;
    unsigned int    _VBO;
    unsigned int    _elements_count;

public:
    Mesh();
    ~Mesh();

    void render() const;
};
#endif