#version 330 core

layout (location = 0) in vec3 position; // Not used but necessary for compatibility
out vec3 frag_color; // Output to Fragment Shader

void main() {
    vec3 positions[3] = vec3[3](
        vec3(-0.5, -0.5, 0.0),
        vec3(0.5, -0.5, 0.0),
        vec3(0.0, 0.5, 0.0)
    );

    vec3 colors[3] = vec3[3](
        vec3(1.0, 0.0, 0.0), // Red
        vec3(0.0, 1.0, 0.0), // Green
        vec3(0.0, 0.0, 1.0)  // Blue
    );

    gl_Position = vec4(positions[gl_VertexID], 1.0);
    frag_color = colors[gl_VertexID]; // Pass color to fragment shader
}