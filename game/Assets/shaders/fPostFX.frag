#version 450
layout(location = 0) out vec4 FragColor;
layout(location = 0) in vec2 inUV; // the input variable from the vertex shader (same name and same type)  


layout(set = 2, binding = 0) uniform sampler2D postFXTexture;


void main()
{

    

    vec4 textureColor = texture(postFXTexture, inUV);


    

    FragColor = vec4(textureColor.r,textureColor.g,textureColor.b,1);
}