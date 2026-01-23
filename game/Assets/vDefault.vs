#version 430 core
layout (location = 0) in vec3 aPos; 
layout (location = 1) in vec2 atexCoord;


uniform mat4 model;
uniform mat4 proj;
out vec2 texCoord; 

void main()
{
    gl_Position = proj * model * vec4(aPos, 1.0); 
    texCoord = atexCoord;
}