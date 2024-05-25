#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "rendering/Renderer.h"

#include "rendering/VertexBuffer.h"
#include "rendering/IndexBuffer.h"
#include "rendering/VertexArray.h"
#include "rendering/Shader.h"
#include "rendering/Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Game/Cube.h"
#include "Game/SkyBox.h"
#include "rendering/TextureCube.h"
#include "rendering/Camera.h"

#include "Game/World.h"

float lastX = 400, lastY = 300;
bool firstMouse = true;
Camera cam;
float yaw = -90.0f;
float pitch = 0.0f;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cam.front = glm::normalize(direction);
}

// void processCollision(World world, Camera& cam, float cameraSpeed) {
// 
//     glm::vec3 move = world.PlayerTouchedCube(cam.pos.x, cam.pos.y, cam.pos.z);
//     
//     cam.pos += move * cameraSpeed;
// }

void processInput(GLFWwindow* window, Camera& cam, float deltaTime, World world)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    const float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
    const glm::vec3 previousCamPos = cam.pos;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cam.pos += cameraSpeed * cam.front;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam.pos -= cameraSpeed * cam.front;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam.pos -= glm::normalize(glm::cross(cam.front, cam.up)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cam.pos += glm::normalize(glm::cross(cam.front, cam.up)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cam.pos += cam.up * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cam.pos -= cam.up * cameraSpeed;

    const int hasCollided = world.PlayerTouchedCube(cam.pos.x, cam.pos.y, cam.pos.z);
    switch (hasCollided) {
        case 0:
            break;
        case 1:
            // Hit in the x direction
            cam.pos.x = previousCamPos.x;
            break;
        case 2:
            // Hit in the y direction
            cam.pos.y = previousCamPos.y;
            break;
        case 3:
            // Hit in the x direction
            cam.pos.z = previousCamPos.z;
            break;
    }

    // processCollision(world, cam, cameraSpeed);

    glfwSetCursorPosCallback(window, mouse_callback);
    
}

int main(void)
{
    GLFWwindow* window;

    // Create window
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int width = 1600;
    int heigth = 1200;

    window = glfwCreateWindow(width, heigth, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Link Graphic card functions to OpenGL API
    if (glewInit() != GLEW_OK) 
        std::cout << "Not ok!" << std::endl;

    // Print version
    std::cout << glGetString(GL_VERSION) << std::endl;

    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // CUBE
    Cube cube;
    std::vector<Cube*> cube_array;

    // Skybox
    SkyBox skybox;
    skybox.m_Position = glm::vec3(0.0f, 0.0f, 0.0f);

    World world;

    // MVP matrices
    // glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float) width / (float) heigth, 0.1f, 100.0f);
    // glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));

    Shader shader("res/shaders/Basic.shader");

    const std::vector<std::string> texture_paths_skybox = {
        "res/textures/skybox/right.jpg", // Right
        "res/textures/skybox/left.jpg", // Left
        "res/textures/skybox/top.jpg", // Top
        "res/textures/skybox/bottom.jpg", // Bottom
        "res/textures/skybox/front.jpg", // Front
        "res/textures/skybox/back.jpg", // Back
    };
    
    TextureCube texture_skybox(texture_paths_skybox);
    texture_skybox.Bind(1); // Binds texture to a texture slot

    Renderer renderer;

    glm::vec3 translationA(0.0f, 0.0f, -5.0f);
    float rotation_y = 0.0f;
    float rotation_x = 0.0f;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);

    glfwSwapInterval(1);

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // Keep track of time
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window, cam, deltaTime, world);

        renderer.Clear();

        { // skybox
            glm::mat4 model = skybox.model;
            model = glm::scale(model, glm::vec3(100.0f, 100.0f, 100.0f));
            glm::mat4 view = glm::mat4(glm::mat3(cam.view)); // Trick to remove the translation operation on view. This allows the skybox to stay centered.
            glm::mat4 mvp = proj * view * model;
            shader.SetUniformMat4f("u_MVP", mvp);
            shader.SetUniform1i("u_Texture", 1); // Gets texture from texture slot 0
            renderer.Draw(skybox.va, skybox.ib, shader);
        }

        { // cube
            glm::mat4 model = cube.model;
            model = glm::rotate(model, glm::radians(rotation_y), glm::vec3(0,1,0)); // where x, y, z is axis of rotation (e.g. 0 1 0)
            model = glm::rotate(model, glm::radians(rotation_x), glm::vec3(1,0,0)); // where x, y, z is axis of rotation (e.g. 0 1 0)
            glm::mat4 mvp = proj * cam.view * model;
            shader.SetUniformMat4f("u_MVP", mvp);
            cube.m_TextureCube.Bind(); // Binds texture to a texture slot
            shader.SetUniform1i("u_Texture", 0); // Gets texture from texture slot 0
            renderer.Draw(cube.va, cube.ib, shader);
        }

        world.Draw(cam, shader, renderer, proj);

        cam.UpdateView();

        // Swap Buffers
        glfwSwapBuffers(window); // As soon as the rendering commands are finished, the front and back buffers are swapped.

        glfwPollEvents(); // Checks if any events are triggered (like keyboard or mouse mouvement).
    }
    glfwTerminate();
    return 0;
}