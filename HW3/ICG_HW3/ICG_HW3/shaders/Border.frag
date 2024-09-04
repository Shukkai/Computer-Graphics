#version 330 core

in vec2 texCoord;
in vec3 normal;
in vec3 view_pos;

uniform sampler2D deer_texture;

out vec4 FragColor;

void main()
{
    // Sample texture color
    vec3 obj_color = vec3(texture(deer_texture, texCoord));

    // Calculate the normalized vectors
    vec3 normalizedNormal = normalize(normal);
    vec3 normalizedView = normalize(view_pos);

    // Calculate the dot product between the normalized normal and view vectors
    float dotProduct = abs(dot(normalizedNormal, normalizedView));
    dotProduct += 0.25;
    vec3 white = vec3(1.0,1.0,1.0);
    vec3 finalColor = obj_color * dotProduct + white * (1 - dotProduct);
    FragColor = vec4(finalColor, 1.0);
}
