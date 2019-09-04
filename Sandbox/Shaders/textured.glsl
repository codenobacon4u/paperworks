#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

struct UBO {
	mat4 view;
	mat4 proj;
	mat4 modl;
};

uniform UBO u_MVP;

out vec2 v_TexCoord;

void main() {
	v_TexCoord = a_TexCoord;
	gl_Position = u_MVP.proj * u_MVP.view * u_MVP.modl * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main() {
	color = texture(u_Texture, v_TexCoord);
}