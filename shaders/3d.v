#version 330 core

// 3D position as vec4 (only xyz used)
layout(location = 0) in vec4 pos_group1;

// 3x3 rotation matrix as 9 floats (row-major order)
uniform float rotationMat[9];
uniform float scale;

uniform mat4 view;
uniform mat4 projection;

out vec3 fragColor;
out vec3 fragPos;

void main() {
    // Extract position components and apply scale
    float position[3];
    position[0] = pos_group1.x;
    position[1] = pos_group1.y;
    position[2] = pos_group1.z;

    // Apply 3D rotation - Manual matrix-vector multiplication
    float rotated3D[3];
    for (int i = 0; i < 3; i++) {
        rotated3D[i] = 0.0;
        for (int j = 0; j < 3; j++) {
            rotated3D[i] += rotationMat[i * 3 + j] * position[j];
        }
    }

    // Already in 3D world space - no projection needed
    vec3 worldPos = vec3(rotated3D[0], rotated3D[1], rotated3D[2]) * scale;
    fragPos = worldPos;

    // Apply the 3D View (Camera) Transformation
    vec4 viewPos = view * vec4(worldPos, 1.0);

    // Apply the final 3D Projection to screen space
    gl_Position = projection * viewPos;

    // Simple color
    fragColor = vec3(0.7, 0.7, 0.8);
}
