#include "World.h"

World::World() {

    for (float i = -3.0f; i < 9.0f; i = i + 1.0f)
    {
        for (float j = -3.0f; j < 9.0f; j = j + 1.0f)
        {
            Cube* c = new Cube();
            c->position = glm::vec3(i, -1.0f, j);
            c->UpdateModel();
            m_cubeObjects.push_back(c);
        }
    }
}

void World::Draw(Camera& cam, Shader& shader, Renderer& renderer, TextureCube& texture, glm::mat4& proj) {

    for (Cube* c : m_cubeObjects)
    {
        glm::mat4 model = c->model;
        glm::mat4 mvp = proj * cam.view * model;
        shader.SetUniformMat4f("u_MVP", mvp);
        texture.Bind(); // Binds texture to a texture slot
        shader.SetUniform1i("u_Texture", 0); // Gets texture from texture slot 0
        renderer.Draw(c->va, c->ib, shader);
    }
}

int World::PlayerTouchedCube(float x, float y, float z) {

    float boxSize = 1.0f;
    float playerSizeX = 1.0f;
    float playerSizeY = 3.0f;
    float playerSizeZ = 1.0f;

    Cube* cubeHit = nullptr;

    for (Cube* c : m_cubeObjects)
    {
        if (c->position.x + boxSize >= x && x + playerSizeX >= c->position.x
            && c->position.y + boxSize >= y && y + playerSizeY >= c->position.y
            && c->position.z + boxSize >= z && z + playerSizeZ >= c->position.z)
            cubeHit = c;
    }
    if (cubeHit) {
        // Work in progress. The idea is that, depending on the side of the cube touching the player, 
        // the player will not be able to move in that direction.
        if (cubeHit->position.y + boxSize <= y && cubeHit->position.z + boxSize <= z &&
        x <= cubeHit->position.x + boxSize && cubeHit->position.x <= x)
            return 1;
        if (cubeHit->position.x + boxSize <= x && cubeHit->position.z + boxSize <= z &&
            y <= cubeHit->position.y + boxSize && cubeHit->position.y <= y)
            return 2;
        if (cubeHit->position.x + boxSize <= x && cubeHit->position.y + boxSize <= y &&
            z <= cubeHit->position.z + boxSize && cubeHit->position.z <= z)
            return 3;
    }

    return 0;
}