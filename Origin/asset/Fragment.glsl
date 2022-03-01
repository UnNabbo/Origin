#version 330 core

layout(location = 0) out vec4 color;


uniform sampler2D u_Texture;

in vec2 v_TexCoord;


void main() {
	color = texture(u_Texture, v_TexCoord);
}