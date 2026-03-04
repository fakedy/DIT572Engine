#version 450
layout(location = 0) out vec4 FragColor;
layout(location = 0) in vec2 inUV; // the input variable from the vertex shader (same name and same type)  


layout(set = 2, binding = 0) uniform sampler2D postFXTexture;


void main()
{

    ivec2 size = textureSize(postFXTexture, 0);
    vec2 resolution = vec2(size);

    vec4 textureColor = texture(postFXTexture, inUV);

    float scanline = sin(inUV.y * resolution.y * 3.14159);


    scanline = (scanline * 0.5 + 0.5) * 0.2;

    FragColor = vec4(textureColor.rgb - scanline,1);
}