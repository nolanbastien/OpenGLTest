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

    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
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
    float positions[] = {
        -0.5f, -0.5f, 0.0f, 0.0f, // 2 float for position, 2 float for texture "mapping"
         0.5f, -0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f
    };

    unsigned int indices[] = {
        0,1,2,
        2,3,0
    };

    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // TRIANGLE / SQUARE

    VertexArray va;
    VertexBuffer vb(positions, 4 * 4 * sizeof(float)); // 4 floats per vertex * 4 vertex
    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    /// INTRO TO IBO

    IndexBuffer ib(indices, 6);

    // The projection matrix takes a vertex from the specified boundaries "space" then transforms it to a -1.0 to 1.0 space for OpenGL to render.
    glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f); // This sets the boundaries of our screen. This is a 4:3 aspect ratio
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

    glm::vec3 translation(0.0f, 0.0f, 0.0f);

    float r = 0.0f;
    float increment = 0.05f;

    glfwSwapInterval(1);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        
        renderer.Clear();

        ImGui_ImplGlfwGL3_NewFrame();

        glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);

        glm::mat4 mvp = proj * view * model;

        // Rendering commands here
        shader.Bind();
        shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f); // Set data in shader (Remember: Uniforms are per draw, don't edit uniforms in between drawings)
        shader.SetUniformMat4f("u_MVP", mvp);

        renderer.Draw(va, ib, shader);
        
        if (r > 1.0f)
            increment = -0.05f;
        else if (r < 0.0f)
            increment = 0.05f;

        r += increment;

        {
            ImGui::SliderFloat3("Translation", &translation.x, -2.0f, 2.0f);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }

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