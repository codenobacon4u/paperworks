#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;

struct UBO {
	mat4 view;
	mat4 proj;
	mat4 modl;
};

uniform UBO u_MVP;

out vec3 v_Position;
out vec4 v_Color;

void main() {
	v_Position = a_Position;
	v_Color = a_Color;
	gl_Position = u_MVP.proj * u_MVP.view * u_MVP.modl * vec4(a_Position, 1.0f);
}