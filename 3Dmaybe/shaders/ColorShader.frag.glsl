#version 130

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

uniform sampler2D tex;

void main()
{
	vec4 textureColor = texture(tex, fragmentUV);
	color = textureColor * fragmentColor;
}