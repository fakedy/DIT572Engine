#version 450
#extension GL_KHR_vulkan_glsl : enable

layout (location = 0) out vec2 outUV;


vec2 vertData[6] = vec2[](
vec2(0,0), vec2(1,0), vec2(0,1),
vec2(0,1), vec2(1,0), vec2(1,1)
);

void main()
{

    outUV = vertData[gl_VertexIndex];

    // flip the texture
    gl_Position = vec4(outUV.x * 2.0 - 1.0, (outUV.y * 2.0 - 1.0) * -1.0, 0.0, 1.0); 
}