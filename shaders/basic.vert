#version 330 core

in vec3 vPos;
uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main () {
    gl_Position = proj * view * model * vec4(vPos, 1.0);
}