#version 330 core

// 2D position as vec4 (only xy used)
layout(location = 0) in vec4 pos_group1;

// 2x2 rotation matrix as 4 floats (row-major order)
uniform float rotationMat[4];
uniform float scale;

uniform mat4 view;
uniform mat4 projection;

out vec3 fragColor;
out vec3 fragPos;

void main() {
    // Extract position components and apply scale
    float position[2];
    position[0] = pos_group1.x;
    position[1] = pos_group1.y;

    // Apply 2D rotation - Manual matrix-vector multiplication
    float rotated2D[2];
    for (int i = 0; i < 2; i++) {
        rotated2D[i] = 0.0;
        for (int j = 0; j < 2; j++) {
            rotated2D[i] += rotationMat[i * 2 + j] * position[j];
        }
    }

    // Embed 2D in 3D space (z = 0)
    vec3 worldPos = vec3(rotated2D[0], rotated2D[1], 0.0) * scale;
    fragPos = worldPos;

    // Apply the 3D View (Camera) Transformation
    vec4 viewPos = view * vec4(worldPos, 1.0);

    // Apply the final 3D Projection to screen space
    gl_Position = projection * viewPos;

    // Simple color
    fragColor = vec3(0.8, 0.6, 0.7);
}
