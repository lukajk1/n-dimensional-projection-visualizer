#version 330 core

// 4D position as vec4
layout(location = 0) in vec4 pos_group1;
layout(location = 1) in vec4 pos_group2;

// 4x4 rotation matrix as 16 floats (row-major order)
uniform float rotationMat[16];
uniform float scale;

uniform mat4 view;
uniform mat4 projection;

out vec3 fragColor;
out vec3 fragPos;

void main() {
    // Extract position components and apply scale
    float position[4];
    position[0] = pos_group1.x * scale;
    position[1] = pos_group1.y * scale;
    position[2] = pos_group1.z * scale;
    position[3] = pos_group1.w * scale;

    // 1. Apply 4D rotation - Manual matrix-vector multiplication
    float rotated4D[4];
    for (int i = 0; i < 4; i++) {
        rotated4D[i] = 0.0;
        for (int j = 0; j < 4; j++) {
            // rotationMat is stored in row-major order: rotationMat[row * 4 + col]
            rotated4D[i] += rotationMat[i * 4 + j] * position[j];
        }
    }

    // 2. Project from 4D to 3D (Perspective/W-Clipping)
    float distance = 3.0;
    float w = rotated4D[3];

    // Check for division by zero or clipping plane (optional guard)
    if (distance + w < 0.001) {
        gl_Position = vec4(0.0); // Clip if too close/behind the 4D camera
        fragColor = vec3(0.0);
        return;
    }

    // Perform 4D -> 3D Projection
    vec3 projected3D_World = vec3(rotated4D[0], rotated4D[1], rotated4D[2]) / (distance + w);
	// color output will use worldspace coords
	fragPos = projected3D_World;
    // 3. Apply the 3D View (Camera) Transformation
    vec4 projected3D_View = view * vec4(projected3D_World, 1.0);

    // 4. Apply the final 3D Projection to screen space
    gl_Position = projection * projected3D_View;

    // Color based on the 4th dimension (w)
    fragColor = vec3(0.5 + 0.5 * w);
}
