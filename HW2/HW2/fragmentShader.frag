#version 330 core

in vec2 texCoord;
in vec3 normal;

uniform sampler2D ourTexture;
//uniform float lighting;
uniform bool useGrayscale;
uniform bool rainbow;

uniform float hue;

out vec4 FragColor;
vec3 hsv2rgb(vec3 c) {
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main()
{
	// TODO: Implement Grayscale Effect
	//   1. Retrieve the color from the texture at texCoord.
	//   2. If useGrayscale is true,
	//        a. Calculate the grayscale value using the dot product with the luminance weights(0.299, 0.587, 0.114).
	//        b. Set FragColor to a grayscale version of the color.
	//   Note: Ensure FragColor is appropriately set for both grayscale and color cases.

	vec4 color = texture(ourTexture, texCoord);
	if (useGrayscale) {
		float grayscaleValue = dot(color.rgb, vec3(0.299, 0.587, 0.114));
		FragColor = vec4(grayscaleValue, grayscaleValue, grayscaleValue, color.a);
	} 
	else if(rainbow){
		vec3 rgb = hsv2rgb(vec3(mod(hue, 6.0), 1.0, 1.0));
		FragColor = vec4(rgb, 1.0);
	}
	else {
		FragColor = color;
	}
}