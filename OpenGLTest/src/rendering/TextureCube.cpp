#include "TextureCube.h"

#include "stb_image/stb_image.h"

TextureCube::TextureCube(const std::vector<std::string>& paths)
	: m_RendererID(0), m_FilePaths(paths), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
	// stbi_set_flip_vertically_on_load(1);
	// m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_NEAREST);

	// glTexImage2D(GL_TEXTURE_CUBE_MAP, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer); // Send the picture to graphics card with OpenGL
	for (unsigned int i = 0; i < paths.size(); i++)
	{
		m_LocalBuffer = stbi_load(paths[i].c_str(), &m_Width, &m_Height, &m_BPP, 0);
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
			0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_LocalBuffer
		);
	}
	
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0); // Unbind after initialization

	if (m_LocalBuffer) // if the buffer contains data
		stbi_image_free; // free the buffer
}

TextureCube::~TextureCube()
{
	glDeleteTextures(1, &m_RendererID); // Delete from GPU
}

void TextureCube::Bind(unsigned int slot /*= 0 */) const
{
	glActiveTexture(GL_TEXTURE0 + slot); // Activate texture slot. The next binding statement will bind to the active slot
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);
}

void TextureCube::Unbind() const
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}