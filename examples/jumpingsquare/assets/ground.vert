#version 300 es

layout(location = 0) in vec2 inPosition;

out vec4 fragColor;

void main() { 
    gl_Position = vec4(inPosition, 0, 1);
    fragColor = vec4(1); 
}