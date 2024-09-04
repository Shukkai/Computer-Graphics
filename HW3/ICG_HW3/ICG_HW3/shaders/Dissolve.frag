#version 330 core

in vec2 texCoord;
in vec3 normal;
in vec3 view_pos;
in vec4 worldPos;

uniform sampler2D deer_texture;
uniform float dissolve;

out vec4 FragColor;

void main()
{
    vec3 obj_color = vec3(texture(deer_texture, texCoord));
    float todissolve = -25.0 + dissolve;
    float nowat = worldPos.x;
    if (nowat < todissolve){
        discard;
    }
    else{
        FragColor = vec4 (obj_color, 1.0);   
    }
}
