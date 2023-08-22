#shader vertex
#version 410 core
        
layout(location = 0) in vec3 position;

out vec3 TexCoords;

uniform mat4 u_MVP;
        
void main()
{
    gl_Position = u_MVP * vec4(position, 1.0);
    TexCoords = position;
};

#shader fragment
#version 410 core

in vec3 TexCoords;

out vec4 FragColor;

uniform samplerCube u_Texture;
        
void main()
{
    FragColor = texture(u_Texture, TexCoords);
};