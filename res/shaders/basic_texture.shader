#shader vertex
#version 330 core
layout(location=0) in vec4 position;
layout(location=1) in vec2 textCoord;
out vec2 v_TextCoord;
void main() {
	gl_Position = position;
	v_TextCoord = textCoord;
}

#shader fragment
#version 330 core
layout(location=0)out vec4 color;
in vec2 v_TextCoord;
uniform sampler2D u_Texture;
void main() {
	// color = vec4(0.5, 0.5, 1.0, 1.0);
	vec4 textColor = texture(u_Texture, v_TextCoord);
	color = textColor;
}