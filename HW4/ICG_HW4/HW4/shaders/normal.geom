#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 6) out;
//Input/Output part is important, so be sure to check how everything works

in VS_OUT {
	vec2 texCoord;
    mat4 V;
	mat4 P;
} gs_in[];

uniform float time;
uniform int way;
out vec2 texCoordGS;

//out vec3 color;

void main()
{
    vec3 v0 = gl_in[0].gl_Position.xyz;
    vec3 v1 = gl_in[1].gl_Position.xyz;
    vec3 v2 = gl_in[2].gl_Position.xyz;
    vec3 vx0 = normalize(cross(v0-v1,v0-v2));
    vec3 vx1 = normalize(cross(v1-v2,v1-v0));
    vec3 vx2 = normalize(cross(v2-v0,v2-v1));
    vec3 normal = (vx0+vx1+vx2) / 3;
    float scale = 10;
    for(int i=0; i<gl_in.length(); i++)
    {
      texCoordGS = gs_in[i].texCoord;
      vec4 added = vec4(normal * (time / 7)  * (time / 7) * scale, 0);
      gl_Position = (gl_in[i].gl_Position + added);
      EmitVertex();
    }
    EndPrimitive();
}