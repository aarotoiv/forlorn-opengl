#version 330

layout(location = 0) in vec3 pos;
out vec4 vCol;

uniform mat4 model; 
uniform mat4 projection;
uniform mat4 view;
uniform vec3 uColor;
uniform float uAlpha;

void main() {
    gl_Position = projection * model * vec4(pos, 1.0);
    vCol = vec4(uColor, uAlpha);
}

