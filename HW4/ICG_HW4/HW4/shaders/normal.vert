#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

out VS_OUT {
	//vec3 fragpos;
	vec2 texCoord;
	mat4 V;
	mat4 P;
} vs_out;

vec4 worldPos;

void main()
{
	worldPos = M * vec4(aPos, 1.0);

	gl_Position = P * V * worldPos;
	//vs_out.fragpos = vec3(worldPos);
	vs_out.texCoord = aTexCoord;
	vs_out.V = V;
	vs_out.P = P;
}

