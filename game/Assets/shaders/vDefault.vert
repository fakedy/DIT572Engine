#version 450
layout (location = 0) in vec3 aPos; 
layout (location = 1) in vec2 atexCoord;


layout(set = 1, binding = 0) uniform UniformBlock {
    mat4 model;
    mat4 proj;
    vec2 uvScale;
} ubo;


layout(location = 0) out vec2 texCoord;

void main()
{
    gl_Position = ubo.proj * ubo.model * vec4(aPos, 1.0); 
    texCoord = ubo.uvScale * atexCoord;
}