#version 330 core

layout(location = 0) in vec4 pos_group1;
layout(location = 1) in vec4 pos_group2;

// 8x8 matrix = 64 floats
uniform float rotationMat[64];
uniform float scale;

uniform mat4 view;
uniform mat4 projection;

out vec3 fragColor;
out vec3 fragPos;

void main() {
    // Extract position components
    float position[8];
    position[0] = pos_group1.x;
    position[1] = pos_group1.y;
    position[2] = pos_group1.z;
    position[3] = pos_group1.w;
    position[4] = pos_group2.x;
    position[5] = pos_group2.y;
    position[6] = pos_group2.z;
    position[7] = pos_group2.w;

	// manual mult
    float rotated8D[8];
    for (int i = 0; i < 8; i++) {
        rotated8D[i] = 0.0;
        for (int j = 0; j < 8; j++) {
            rotated8D[i] += rotationMat[i * 8 + j] * position[j];
        }
    }

    // Multi-step projection: 8D->7D->6D->5D->4D->3D
    float distance7D = 3.0;
    float distance6D = 3.0;
    float distance5D = 3.0;
    float distance4D = 3.0;

    // First: 8D -> 7D projection (project out the 8th dimension)
    float dim8 = rotated8D[7];
    float projected7D[7];
    for (int i = 0; i < 7; i++) {
        projected7D[i] = rotated8D[i] / (distance7D + dim8);
    }

    // Second: 7D -> 6D projection (project out the 7th dimension)
    float dim7 = projected7D[6];
    float projected6D[6];
    for (int i = 0; i < 6; i++) {
        projected6D[i] = projected7D[i] / (distance6D + dim7);
    }

    // Third: 6D -> 5D projection (project out the 6th dimension)
    float dim6 = projected6D[5];
    float projected5D[5];
    for (int i = 0; i < 5; i++) {
        projected5D[i] = projected6D[i] / (distance5D + dim6);
    }

    // Fourth: 5D -> 4D projection (project out the 5th dimension V)
    float v = projected5D[4];
    vec4 projected4D;
    projected4D.x = projected5D[0] / (distance5D + v);
    projected4D.y = projected5D[1] / (distance5D + v);
    projected4D.z = projected5D[2] / (distance5D + v);
    projected4D.w = projected5D[3] / (distance5D + v);

    // Fifth: 4D -> 3D projection (project out the W dimension)
    float w = projected4D.w;

    // Check for division by zero or clipping plane
    if (distance4D + w < 0.001) {
        gl_Position = vec4(0.0);
        fragColor = vec3(0.0);
        return;
    }

    // Perform 4D -> 3D Projection
	// apply scale in 3d worldspace to avoid distortion
    vec3 projected3D_World = projected4D.xyz / (distance4D + w) * scale;
	// color output will use worldspace coords
	fragPos = projected3D_World;
    // Apply the 3D View (Camera) Transformation
    vec4 projected3D_View = view * vec4(projected3D_World, 1.0);

    // Apply the final 3D Projection to screen space
    gl_Position = projection * projected3D_View;

    // Color based on the 8th dimension
    fragColor = vec3(0.5 + 0.25 * dim8, 0.55, 0.5 - 0.25 * dim8);
}
