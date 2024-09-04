#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

uniform float squeezeFactor;
uniform float offest;

out vec2 texCoord;
out vec3 normal;

vec4 worldPos;

uniform bool squeezing;

void main()
{
	// TODO: Implement squeeze effect and update normal transformation
	//   1. Adjust the vertex position to create a squeeze effect based on squeezeFactor.
	//   2. Update worldPos using the model matrix (M).
	//   3. Calculate the final gl_Position using the perspective (P), view (V), and updated worldPos.
	//   4. Update the normal transformation for lighting calculations.
	// Note: Ensure to handle the squeeze effect for both y and z coordinates.
	
    vec3 originalPos = aPos;
    vec3 squeezedPos;
    float newY = aPos.y + aPos.z * sin(radians(squeezeFactor)) / 2.0;
    float newZ = aPos.z + aPos.y * sin(radians(squeezeFactor)) / 2.0;
    squeezedPos = vec3(aPos.x, newY, newZ);
    vec4 worldPos = M * vec4(squeezedPos, 1.0);
    gl_Position = P * V * worldPos;

    mat3 normalMatrix = transpose(inverse(mat3(M)));
    normal = normalize(normalMatrix * aNormal);

    // Pass the texture coordinates to the fragment shader
    texCoord = aTexCoord;
}