#version 140

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

attribute vec3 inPosition;
attribute vec2 inTexCoord;
attribute vec3 inNormal;

varying vec2 fragTexCoord;
varying vec3 fragNormal;
varying mat4 fragView;

void main() {
    gl_Position = proj * view * model * vec4(inPosition, 1.0);
    fragTexCoord = inTexCoord;
    fragNormal = inNormal;
   	fragView = model;
}