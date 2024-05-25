#include "World.h"

World::World() {

    for (float i = -3.0f; i < 9.0f; i = i + 1.0f)
    {
        for (float j = -3.0f; j < 9.0f; j = j + 1.0f)
        {
            Cube* c = new Cube();
            c->m_Position = glm::vec3(i, -1.0f, j);
            c->UpdateModel();
            m_cubeObjects.push_back(c);
        }
    }
}

void World::Draw(Camera& cam, Shader& shader, Renderer& renderer, glm::mat4& proj) {

    for (Cube* c : m_cubeObjects)
    {
        glm::mat4 model = c->model;
        glm::mat4 mvp = proj * cam.view * model;
        shader.SetUniformMat4f("u_MVP", mvp);
        c->m_TextureCube.Bind(); // Binds texture to a texture slot
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
        if (c->m_Position.x + boxSize >= x && x + playerSizeX >= c->m_Position.x
            && c->m_Position.y + boxSize >= y && y + playerSizeY >= c->m_Position.y
            && c->m_Position.z + boxSize >= z && z + playerSizeZ >= c->m_Position.z)
            cubeHit = c;
    }
    if (cubeHit) {
        // Work in progress. The idea is that, depending on the side of the cube touching the player, 
        // the player will not be able to move in that direction.
        if (cubeHit->m_Position.y + boxSize <= y && cubeHit->m_Position.z + boxSize <= z &&
        x <= cubeHit->m_Position.x + boxSize && cubeHit->m_Position.x <= x)
            return 1;
        if (cubeHit->m_Position.x + boxSize <= x && cubeHit->m_Position.z + boxSize <= z &&
            y <= cubeHit->m_Position.y + boxSize && cubeHit->m_Position.y <= y)
            return 2;
        if (cubeHit->m_Position.x + boxSize <= x && cubeHit->m_Position.y + boxSize <= y &&
            z <= cubeHit->m_Position.z + boxSize && cubeHit->m_Position.z <= z)
            return 3;
    }

    return 0;
}