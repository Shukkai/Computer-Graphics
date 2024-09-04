#version 330 core

// TODO:
// Implement Toon shading
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform vec3 camera;

out vec2 texCoord;
out vec4 worldPos;
out vec3 normal;
out vec3 view_pos;
void main()
{
	worldPos = M * vec4(aPos, 1.0);
	gl_Position = P * V * M * vec4(aPos, 1.0);
	texCoord = aTexCoord;
	view_pos = camera;
	normal = normalize((transpose(inverse(M)) * vec4(aNormal, 0.0)).xyz);
}