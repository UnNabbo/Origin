#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;

uniform mat4 u_ProjectionView;

uniform mat4 u_Model;


out vec4 Color;

void main() {
	Color = a_Color;
	gl_Position = u_ProjectionView * vec4(a_Position, 1.0f);
}