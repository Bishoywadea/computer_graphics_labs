#version 330 core

void main() {
    vec3 positions[3] = vec3[3](
        vec3(-0.5, -0.5, 0.0),
        vec3(0.5, -0.5, 0.0),
        vec3(0.0, 0.5, 0.0)
    );

    gl_Position = vec4(positions[gl_VertexID], 1.0);
}