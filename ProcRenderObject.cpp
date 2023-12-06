#include "ProcRenderObject.hpp"
#include <random>
#include "basic_structures.hpp"
#include "CSCIx229.hpp"

void ProcRenderObject::Display()
{
    // Assuming 'objectTris' holds the list of triangles

    // Create and bind VAO
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow color for Gometry
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create and bind VBOs
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Get the total size of vertex data
    std::size_t vertexDataSize = objectTris.size() * 3 * sizeof(Vertex); // Assuming 3 vertices per triangle

    // Allocate and fill buffer with vertex data
    glBufferData(GL_ARRAY_BUFFER, vertexDataSize, objectTris.data(), GL_STATIC_DRAW);

    // Set vertex attribute pointers
    // Assuming the Vertex struct has consecutive position and normal data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, location)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, normal)));
    glEnableVertexAttribArray(1);

    // Unbind VAO and VBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Render using VAO
    glPushMatrix();
    glTranslated(Location.x, Location.y, Location.z);
    glRotated(Rotation.x, 1, 0, 0);
    glRotated(Rotation.y, 0, 1, 0);
    glRotated(Rotation.z, 0, 0, 1);
    glScaled(Scale.x, Scale.y, Scale.z);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, objectTris.size() * 3); // Assuming 3 vertices per triangle
    glBindVertexArray(0);

    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f); // Red color for normal lines
    for (const auto &tri : objectTris)
    {
        // Draw normal for each vertex
        drawNormalLine(tri.p1);
        drawNormalLine(tri.p2);
        drawNormalLine(tri.p3);
    }
    glEnd();
    glPopMatrix();

    // Clean up
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);


}

void ProcRenderObject::drawNormalLine(const Vertex &vertex)
{
    // Draw a line from the vertex position to the vertex position + normal
    glm::vec3 lineEnd = vertex.location + (0.1f * vertex.normal); // Scale the normal for visualization
    glVertex3f(vertex.location.x, vertex.location.y, vertex.location.z);
    glVertex3f(lineEnd.x, lineEnd.y, lineEnd.z);
}