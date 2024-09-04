#version 330 core

uniform sampler2D ourTexture;

//in vec3 fragposGS;
//in vec3 normalGS;
in vec2 texCoordGS;

//in vec3 color;

out vec4 FragColor;

void main()
{
    vec3 obj_color = vec3(texture(ourTexture, texCoordGS));
    FragColor = vec4(obj_color, 1.0);
}