#include "Cube.h"

Cube::Cube()
    : ib(
        new unsigned int[] {
                0, 2, 1,
                0, 3, 2,

                4, 2, 1,
                4, 5, 2,

                7, 5, 4,
                7, 6, 4,

                3, 7, 6,
                3, 6, 0,

                5, 7, 3,
                5, 2, 3,

                4, 1, 0,
                4, 6, 0 

        }, 3 * 2 * 6),
    position(
        glm::vec3(0.0f, 0.0f, 0.0f)
    ),
    model(glm::translate(glm::mat4(1.0f), position))
{

    float data[] = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // 3 float for position, 2 float for texture "mapping"
     0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,

     0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // 3 float for position, 2 float for texture "mapping"
     0.5f,  0.5f,  0.5f, 0.0f, 1.0f,

    -0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f,  0.5f, 0.5f, 1.0f, 1.0f
    };

	// init data
    VertexBuffer vb(data, 5 * 8 * sizeof(float)); // 5 floats per vertex * 8 vertex
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    // Unbind after initialization
    va.Unbind();
    vb.Unbind();
    ib.Unbind();
}

void Cube::UpdateModel()
{
    model = glm::translate(glm::mat4(1.0f), position);
}

Cube::~Cube()
{

}