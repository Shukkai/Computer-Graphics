#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform vec3 camera;

out vec2 texCoord;
out vec3 normal;
out vec3 view_pos;
out vec4 worldPos;

void main()
{

	texCoord = aTexCoord;
	gl_Position = P * V * M * vec4(aPos, 1.0);	
	worldPos = vec4(aPos, 1.0);
	normal = normalize((transpose(inverse(M))* vec4(aNormal, 0.0)).xyz);
	view_pos = camera;


}