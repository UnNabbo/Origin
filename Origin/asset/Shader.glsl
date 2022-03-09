#Type vertex
#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

uniform mat4 u_ProjectionView;

uniform mat4 u_Model;

out vec2 v_TexCoord;


void main() {

	v_TexCoord = a_TexCoord;
	gl_Position =  u_ProjectionView * u_Model * vec4(a_Position,1.0f);
}

#Type pixel
#version 460 core

layout(location = 0) out vec4 color;


uniform sampler2D u_Texture;

in vec2 v_TexCoord;


void main() {
	color = vec4(1.0f,0.0f,0.0f,1.0f);
}