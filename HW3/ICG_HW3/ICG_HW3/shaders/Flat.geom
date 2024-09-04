#version 330 core 
// TODO: 
// Implement Flat shading 
layout(triangles) in; 
layout(triangle_strip, max_vertices = 3) out; 
in VS_OUT { 
	vec3 normal; 
	vec2 texCoord; 
	vec4 worldPos; 
} gs_in[]; 
	out vec3 trinormal; 
	out vec2 texCoord; 
void main(void) { 
	trinormal = normalize(gs_in[0].normal + gs_in[1].normal +gs_in[2].normal); 
	for (int i = 0; i < 3; ++i) { 
	gl_Position = gl_in[i].gl_Position; 
	texCoord = gs_in[i].texCoord; 	
	EmitVertex(); 
	} 
	EndPrimitive(); 
}
