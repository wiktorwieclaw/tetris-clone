#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform vec3 spriteColor;
uniform vec3 secondColor;
uniform float mixture;

void main()
{
    vec4 texColor = texture(image, TexCoords);
    if(texColor.a < 0.1)
        discard;
    color = mix(vec4(spriteColor, 1.0), vec4(secondColor, 1.0f), mixture) * texColor;
}