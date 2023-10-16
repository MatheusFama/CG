#version 300 es

layout(location = 0) in vec2 inPosition;
uniform float inTranslation;

out vec4 fragColor;
void main() { 
    vec2 newPosition = vec2(inPosition.x+ inTranslation ,inPosition.y );
    gl_Position = vec4(newPosition, 0, 1);
    fragColor = vec4(1); 
}