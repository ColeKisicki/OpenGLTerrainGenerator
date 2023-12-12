#include "ProcRenderObject.hpp"
#include <random>
#include <iostream>
#include "basic_structures.hpp"
#include "CSCIx229.hpp"

void ProcRenderObject::Display()
{
    // Assuming 'objectTris' holds the list of triangles

    // Create and bind VAO
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create and bind VBOs for vertices
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Get the total size of vertex data
    std::size_t vertexDataSize = objectTris.size() * 3 * sizeof(Vertex); // Assuming 3 vertices per triangle

    // Allocate and fill buffer with vertex data
    glBufferData(GL_ARRAY_BUFFER, vertexDataSize, objectTris.data(), GL_STATIC_DRAW);

    // Set vertex attribute pointers
    // Assuming the Vertex struct has consecutive position and normal data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, location)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));
    glEnableVertexAttribArray(1);

    // Unbind VAO and VBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Generate indices for triangles
    std::vector<unsigned int> indices;
    for (size_t i = 0; i < objectTris.size(); ++i) {
        indices.push_back(i * 3);
        indices.push_back(i * 3 + 1);
        indices.push_back(i * 3 + 2);
    }

    // Create and bind index buffer
    GLuint indexBufferID;
    glGenBuffers(1, &indexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Render using indexed drawing
    glBindVertexArray(vao); // Rebind VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID); // Bind index buffer

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    // ... Draw normals

    // Clean up
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &indexBufferID);
}


void ProcRenderObject::drawNormalLine(const Vertex &vertex)
{
    // Draw a line from the vertex position to the vertex position + normal
    glm::vec3 lineEnd = vertex.location + (0.1f * vertex.normal); // Scale the normal for visualization
    glVertex3f(vertex.location.x, vertex.location.y, vertex.location.z);
    glVertex3f(lineEnd.x, lineEnd.y, lineEnd.z);
}