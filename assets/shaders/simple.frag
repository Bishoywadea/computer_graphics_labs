#version 330 core

in vec3 frag_color; // Receiving interpolated color
out vec4 final_color;

void main() {
    final_color = vec4(frag_color, 1.0); // Apply color with full opacity
}