#include "WorldObject.h"



WorldObject::WorldObject()
{

}

void WorldObject::ClearAll() const
{
	m_Renderer.Clear();
}

void WorldObject::Render() const
{
	m_Renderer.Draw(m_Va, m_Ib, m_Shader);
}