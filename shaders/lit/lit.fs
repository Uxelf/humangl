#version 330 core
out vec4 FragColor;

in vec3 Normal;

uniform vec3 objectColor;


void main()
{
    float diffuse = ((dot(Normal, vec3(0.2, 0.4, 1)) + 1) / 2) * 0.8 + 0.2;
    vec3 result = objectColor * diffuse;
    FragColor = vec4(result, 1.0); 
}