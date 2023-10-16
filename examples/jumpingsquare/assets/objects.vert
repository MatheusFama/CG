#version 300 es

layout(location = 0) in vec2 inPosition;

out vec4 fragColor;
uniform float translation;
void main() { 
    vec2 newPosition = vec2(inPosition.x,inPosition.y + translation);
    gl_Position = vec4(newPosition, 0, 1);
    fragColor = vec4(1); 
}