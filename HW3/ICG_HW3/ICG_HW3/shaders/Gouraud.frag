#version 330 core

// TODO:
// Implement Gouraud shading
in vec2 texCoord;
in vec3 normal;
in vec3 ambient;
in vec3 diffuse;
in vec3 specular;

uniform sampler2D deer_texture;

out vec4 FragColor;

void main()
{
	vec3 obj_color = vec3(texture(deer_texture, texCoord));
	vec3 a = ambient * obj_color;
	vec3 d = diffuse * obj_color;
	FragColor = vec4((a + d + specular), 1.0);
}