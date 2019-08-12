#version 330 core

layout(location = 0) in vec3 a_Position;

struct UBO {
	mat4 view;
	mat4 proj;
};

uniform UBO u_MVP;

out vec3 v_Position;

void main() {
	v_Position = a_Position;
	gl_Position = u_MVP.proj * u_MVP.view * vec4(a_Position, 1.0f);
}