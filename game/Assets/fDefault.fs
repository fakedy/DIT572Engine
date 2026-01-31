#version 430 core
out vec4 FragColor;
  
in vec2 texCoord; // the input variable from the vertex shader (same name and same type)  


uniform sampler2D ourTexture;

void main()
{

    vec4 textureColor = texture(ourTexture, texCoord);

    if(textureColor.a < 0.01){
        discard;
    }

    FragColor = textureColor;
}