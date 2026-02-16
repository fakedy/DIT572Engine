#version 450
layout(location = 0) out vec4 FragColor;
layout(location = 0) in vec2 texCoord; // the input variable from the vertex shader (same name and same type)  


layout(set = 2, binding = 0) uniform sampler2D ourTexture;

void main()
{


    vec4 textureColor = texture(ourTexture, texCoord);

    if(textureColor.a < 0.01){
        discard;
    }
    
    FragColor = textureColor;
    //FragColor = vec4(vec3(gl_FragCoord.z), 1.0);
}