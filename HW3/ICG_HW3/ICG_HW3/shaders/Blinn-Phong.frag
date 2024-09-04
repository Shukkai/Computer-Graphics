#version 330 core

in vec2 texCoord;
in vec4 worldPos;
in vec3 normal;
in vec3 view_pos;

uniform sampler2D deer_texture;

out vec4 FragColor;

void main()
{
    vec3 Ka = vec3(1.0, 1.0, 1.0);
    vec3 Kd = vec3(1.0, 1.0, 1.0);
    vec3 Ks = vec3(0.7, 0.7, 0.7);
    float shininess = 10.5;
    vec3 La = vec3(0.2, 0.2, 0.2);
    vec3 Ld = vec3(0.8, 0.8, 0.8);
    vec3 Ls = vec3(0.5, 0.5, 0.5);
    vec3 lightPos = vec3(10, 10, 10);

    vec3 obj_color = vec3(texture(deer_texture, texCoord));

    // Ambient
    vec3 ambient = La * Ka * obj_color;

    // Diffuse
    vec3 n_normal = normalize(normal);
    vec3 light = normalize(vec4(lightPos, 1.0) - worldPos).xyz;
    vec3 diffuse = Ld * Kd * obj_color * max(0.0, dot(light, n_normal));

    // Specular (Blinn-Phong)
    vec3 view_dir = normalize(view_pos - vec3(worldPos));
    vec3 halfway_dir = normalize(light + view_dir);
    vec3 specular = Ls * Ks * pow(max(0.0, dot(n_normal, halfway_dir)), shininess);

    FragColor = vec4((ambient + diffuse + specular), 1.0);
}
