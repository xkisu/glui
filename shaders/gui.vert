#version 330 core

in vec3 vPos;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

uniform vec4 color;

varying vec4 v_color;

void main () {
    gl_Position = proj * view * model * vec4(vPos, 1.0);
    v_color = color;
}