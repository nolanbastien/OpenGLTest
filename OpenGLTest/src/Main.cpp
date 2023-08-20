#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

// #include "cube.h"

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
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

    window = glfwCreateWindow(1600, 1200, "Hello World", NULL, NULL);
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

    // DATA
    // init data

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

    // init indices

    unsigned int indices[] = {
        1,2,0,
        2,0,3,

        1,2,4,
        2,4,5,

        4,5,7,
        4,6,7,

        6,7,3,
        6,0,3,

        3,7,5,
        3,2,5,

        0,1,4,
        0,6,4
    };


    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // CUBE
    VertexArray va;
    VertexBuffer vb(data, 5 * 8 * sizeof(float)); // 5 floats per vertex * 8 vertex
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);
    IndexBuffer ib(indices, 3 * 2 * 6); // 3 vertices * 2 triangles * 2 sides

    // MVP matrices
    glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

    Shader shader("res/shaders/Basic.shader");
    shader.Bind();
    shader.SetUniform4f("u_Color", 0.0f, 0.3f, 0.8f, 1.0f);

    Texture texture("res/textures/grass_fullres.png");
    texture.Bind(); // Binds texture to a texture slot
    shader.SetUniform1i("u_Texture", 0); // Gets texture from texture slot 0

    va.Unbind();
    shader.Unbind();
    vb.Unbind();
    ib.Unbind();

    Renderer renderer;

    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();

    glm::vec3 translationA(0.0f, 0.0f, 0.0f);
    float rotation_y = 0.0f;
    float rotation_x = 0.0f;
    glEnable(GL_DEPTH_TEST);

    glfwSwapInterval(1);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        
        renderer.Clear();

        ImGui_ImplGlfwGL3_NewFrame();

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
            model = glm::rotate(model, glm::radians(rotation_y), glm::vec3(0,1,0)); // where x, y, z is axis of rotation (e.g. 0 1 0)
            model = glm::rotate(model, glm::radians(rotation_x), glm::vec3(1,0,0)); // where x, y, z is axis of rotation (e.g. 0 1 0)
            glm::mat4 mvp = proj * view * model;
            shader.SetUniformMat4f("u_MVP", mvp);

            renderer.Draw(va, ib, shader);
            // renderer.Draw(cube.va, cube.ib, shader);
        }

        {
            ImGui::SliderFloat3("Translation A", &translationA.x, -2.0f, 2.0f);
            ImGui::SliderFloat("Rotation Y", &rotation_y, 0, 360);
            ImGui::SliderFloat("Rotation X", &rotation_x, 0, 360);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }
        if (rotation_y > 360.0f) rotation_y = 0.0f;
        rotation_y++;
        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap Buffers
        glfwSwapBuffers(window); // As soon as the rendering commands are finished, the front and back buffers are swapped.

        glfwPollEvents(); // Checks if any events are triggered (like keyboard or mouse mouvement).
    }
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}