#version 450
#extension GL_KHR_vulkan_glsl : enable
layout(location = 0) out vec4 FragColor;
layout(location = 0) in vec2 texCoord; // the input variable from the vertex shader (same name and same type)  


layout(set = 2, binding = 0) uniform sampler2DArray ourTexture;

layout(set = 3, binding = 0) uniform UniformBlock {
    uint layerIndex;
} ubo;


void main()
{


    vec4 textureColor = texture(ourTexture, vec3(texCoord.x, texCoord.y, float(ubo.layerIndex)));

    if(textureColor.a < 0.01){
        discard;
    }
    
    FragColor = textureColor;
}