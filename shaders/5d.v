#version 330 core

layout(location = 0) in vec4 pos_group1;
layout(location = 1) in vec4 pos_group2;

// nxn matrix
uniform float rotationMat[25];
uniform float scale;

uniform mat4 view;
uniform mat4 projection;

out vec3 fragColor;
out vec3 fragPos;

void main() {
    // Extract position components and apply scale
    float position[5];
    position[0] = pos_group1.x;
    position[1] = pos_group1.y;
    position[2] = pos_group1.z;
    position[3] = pos_group1.w;
    position[4] = pos_group2.x;

	// manual mult
    float rotated5D[5];
    for (int i = 0; i < 5; i++) {
        rotated5D[i] = 0.0;
        for (int j = 0; j < 5; j++) {
            rotated5D[i] += rotationMat[i * 5 + j] * position[j];
        }
    }

    // 2. Project from 5D to 3D (Two-step projection: 5D->4D->3D)
    float distance4D = 3.0;  // Distance for 4D projection
    float distance5D = 3.0;  // Distance for 5D projection

    // First: 5D -> 4D projection (project out the 5th dimension V)
    float v = rotated5D[4];
    vec4 projected4D;
    projected4D.x = rotated5D[0] / (distance5D + v);
    projected4D.y = rotated5D[1] / (distance5D + v);
    projected4D.z = rotated5D[2] / (distance5D + v);
    projected4D.w = rotated5D[3] / (distance5D + v);

    // Second: 4D -> 3D projection (project out the W dimension)
    float w = projected4D.w;

    // Check for division by zero or clipping plane
    if (distance4D + w < 0.001) {
        gl_Position = vec4(0.0);
        fragColor = vec3(0.0);
        return;
    }

    // Perform 4D -> 3D Projection
    vec3 projected3D_World = projected4D.xyz / (distance4D + w) * scale;
	// color output will use worldspace coords
	fragPos = projected3D_World;
    // 3. Apply the 3D View (Camera) Transformation
    vec4 projected3D_View = view * vec4(projected3D_World, 1.0);

    // 4. Apply the final 3D Projection to screen space
    gl_Position = projection * projected3D_View;

    // Color based on the 5th dimension (v)
    fragColor = vec3(0.5 + 0.5 * v, 0.7, 0.5 - 0.5 * v);
}
