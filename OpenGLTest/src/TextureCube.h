#pragma once

#include "Renderer.h"

class TextureCube
{
private:
	unsigned int m_RendererID;
	const std::vector<std::string> m_FilePaths;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;

public:
	TextureCube(const std::vector<std::string>& paths);
	~TextureCube();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
};