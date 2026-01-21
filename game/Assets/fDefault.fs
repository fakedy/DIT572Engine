#version 430 core
out vec4 FragColor;
  
in vec2 texCoord; // the input variable from the vertex shader (same name and same type)  

void main()
{
    FragColor = vec4(0.302, 1.0, 0.0, 1.0);
}