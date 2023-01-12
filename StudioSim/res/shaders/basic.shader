#shader vertex
#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

void main()
{
	gl_Position = vec4(position, 0, 1.0f);
	//When Quack Positions[] is at 1.0, set first number to 0.5
	v_TexCoord = 10 * gl_Position.xy + vec2(0.5);
	//v_TexCoord = texCoord;
};

#shader fragment
#version 330 core

uniform sampler2D u_Texture;
in vec2 v_TexCoord;

layout(location = 0) out vec4 color;

uniform vec4 u_Color;


void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	color = texColor;
}