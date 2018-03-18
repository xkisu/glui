#version 330 core

varying vec4 v_color;

void main() {
    gl_FragColor = v_color;// vec4(color, 1.0);
}