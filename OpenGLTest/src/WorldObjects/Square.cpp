#include "Square.h"

Square::Square()
{
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

	for (int i = 0; i < 16; ++i)
		m_Positions[i] = positions[i];

	for (int i = 0; i < 5; ++i)
		m_Indices[i] = indices[i];

	m_Vb = VertexBuffer(m_Positions, 4 * 4 * sizeof(float)); // 4 floats per vertex * 4 vertex
	m_VbLayout.Push<float>(2);
	m_VbLayout.Push<float>(2);
	m_Va.AddBuffer(m_Vb, m_VbLayout);

	m_Ib = IndexBuffer(m_Indices, 6);

}

void Square::BindTexture() {

	m_Shader.SetPath("res/shaders/Basic.shader");
	m_Shader.Bind();
	// m_Shader.SetUniform4f("u_Color", 0.0f, 0.3f, 0.8f, 1.0f);

	Texture texture("res/textures/grass_fullres.png");
	texture.Bind(); // Binds texture to a texture slot
	m_Shader.SetUniform1i("u_Texture", 0); // Gets texture from texture slot 0

	m_Va.Unbind();
	m_Shader.Unbind();
	m_Vb.Unbind();
	m_Ib.Unbind();
}

void Square::SetTransformation(glm::vec3 transform, glm::mat4 view, glm::mat4 proj) {
	glm::mat4 model = glm::translate(glm::mat4(1.0f), transform);
	glm::mat4 mvp = proj * view * model;

	m_Shader.Bind();
	m_Shader.SetUniformMat4f("u_MVP", mvp);
	m_Shader.Unbind();
}


