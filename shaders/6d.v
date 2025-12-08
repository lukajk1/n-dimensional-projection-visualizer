#version 330 core

layout(location = 0) in vec4 pos_group1;
layout(location = 1) in vec4 pos_group2;

// 6x6 matrix = 36 floats
uniform float rotationMat[36];
uniform float scale;

uniform mat4 view;
uniform mat4 projection;

out vec3 fragColor;
out vec3 fragPos;

void main() {
    // Extract position components and apply scale
    float position[6];
    position[0] = pos_group1.x * scale;
    position[1] = pos_group1.y * scale;
    position[2] = pos_group1.z * scale;
    position[3] = pos_group1.w * scale;
    position[4] = pos_group2.x * scale;
    position[5] = pos_group2.y * scale;

	// manual mult
    float rotated6D[6];
    for (int i = 0; i < 6; i++) {
        rotated6D[i] = 0.0;
        for (int j = 0; j < 6; j++) {
            rotated6D[i] += rotationMat[i * 6 + j] * position[j];
        }
    }

    // Multi-step projection: 6D->5D->4D->3D
    float distance5D = 3.0;
    float distance4D = 3.0;

    // First: 6D -> 5D projection (project out the 6th dimension)
    float dim6 = rotated6D[5];
    float projected5D[5];
    for (int i = 0; i < 5; i++) {
        projected5D[i] = rotated6D[i] / (distance5D + dim6);
    }

    // Second: 5D -> 4D projection (project out the 5th dimension V)
    float v = projected5D[4];
    vec4 projected4D;
    projected4D.x = projected5D[0] / (distance5D + v);
    projected4D.y = projected5D[1] / (distance5D + v);
    projected4D.z = projected5D[2] / (distance5D + v);
    projected4D.w = projected5D[3] / (distance5D + v);

    // Third: 4D -> 3D projection (project out the W dimension)
    float w = projected4D.w;

    // Check for division by zero or clipping plane
    if (distance4D + w < 0.001) {
        gl_Position = vec4(0.0);
        fragColor = vec3(0.0);
        return;
    }

    // Perform 4D -> 3D Projection
    vec3 projected3D_World = projected4D.xyz / (distance4D + w);
	// color output will use worldspace coords
	fragPos = projected3D_World;
    // Apply the 3D View (Camera) Transformation
    vec4 projected3D_View = view * vec4(projected3D_World, 1.0);

    // Apply the final 3D Projection to screen space
    gl_Position = projection * projected3D_View;

    // Color based on the 6th dimension
    fragColor = vec3(0.5 + 0.4 * dim6, 0.65, 0.5 - 0.4 * dim6);
}
